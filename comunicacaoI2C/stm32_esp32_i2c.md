
<img src=esp32_stm_oled.png>


1. **STM32F411 Slave**: lê uma entrada analógica `PA0 / ADC1_IN0` e fica disponível no barramento I2C.
2. **ESP32  Master**: solicita ao slave o valor ADC via I2C e envia o resultado pela UART.

Sinais de comunicação entre ESP32 S3 e STM32F411

### STM32F411 habilitado com i2c em modo slave  no endereço 0x30 retornando a leitura de AD

<img width="1137" height="264" alt="image" src="https://github.com/user-attachments/assets/f0b67923-26e1-4499-86d6-6eb1bb0af2a6" />

## Configuração STM32f411





Adicione resistores de pull-up em **SDA** e **SCL**, por exemplo **4,7 kΩ para 3,3 V**.

Para o ADC no slave:

| Sinal | Pino |
|---|---|
| Entrada analógica | PA0 / ADC1_IN0 |
| Tensão máxima | 3,3 V |
| GND do sinal | GND da placa slave |

---

# Configuração no STM32CubeMX / STM32CubeIDE

## Projeto 1 — Slave

Configure:

```text
ADC1
- IN0 em PA0
- Resolution: 12 bits
- Data Alignment: Right
- Continuous Conversion Mode: Disable
- External Trigger: Software Start

I2C1
- Mode: I2C
- I2C Speed: 100 kHz
- Own Address 1: 0x30
- Addressing Mode: 7-bit

GPIO
- PB8: I2C1_SCL
- PB9: I2C1_SDA

NVIC
- Habilite I2C1 event interrupt
- Habilite I2C1 error interrupt
```

<img width="1566" height="678" alt="image" src="https://github.com/user-attachments/assets/4e97c235-eb6a-44e6-928b-3126970ba7a5" />

<img width="985" height="203" alt="image" src="https://github.com/user-attachments/assets/ac6a066a-4f50-4abf-ac7f-c552d29ec86d" />

<img width="990" height="748" alt="image" src="https://github.com/user-attachments/assets/cb31e6b7-2993-46c0-9374-9fbbb6e61247" />


---

# Código 1 — STM32F411 Slave: ADC + I2C

Coloque este código no `main.c`, mantendo as funções geradas pelo CubeMX. O ponto principal é preencher as áreas `USER CODE`.

```c
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

#define I2C_SLAVE_ADDR_7BIT  0x30

volatile uint16_t adc_value = 0;

/*
   Pacote enviado ao master:

   tx_buffer[0] = byte alto do ADC
   tx_buffer[1] = byte baixo do ADC
   tx_buffer[2] = checksum simples
   tx_buffer[3] = marcador fixo 0xA5

   O ADC é de 12 bits, logo varia de 0 a 4095.
*/
uint8_t tx_buffer[4];

/* USER CODE END PV */
```

No `main()`:

```c
int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();

  /* USER CODE BEGIN 2 */

  /*
     Habilita o modo de escuta do I2C slave.
     Quando o master chamar o endereço 0x30, uma callback será acionada.
  */
  HAL_I2C_EnableListen_IT(&hi2c1);

  /* USER CODE END 2 */

  while (1)
  {
    /* USER CODE BEGIN WHILE */

    /*
       O slave fica atualizando continuamente o valor ADC.
       Quando o master pedir os dados via I2C, será enviado o último valor lido.
    */

    HAL_ADC_Start(&hadc1);

    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
      adc_value = HAL_ADC_GetValue(&hadc1);
    }

    HAL_ADC_Stop(&hadc1);

    HAL_Delay(50);

    /* USER CODE END WHILE */
  }
}
```

Agora adicione as callbacks no final do arquivo `main.c`:

```c
/* USER CODE BEGIN 4 */

/*
   Esta callback é chamada quando o master acessa o endereço I2C do slave.

   TransferDirection indica o sentido da comunicação:

   I2C_DIRECTION_TRANSMIT:
   O master quer escrever dados no slave.

   I2C_DIRECTION_RECEIVE:
   O master quer ler dados do slave.
*/
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c,
                          uint8_t TransferDirection,
                          uint16_t AddrMatchCode)
{
  if (hi2c->Instance == I2C1)
  {
    if (TransferDirection == I2C_DIRECTION_RECEIVE)
    {
      /*
         O master quer ler o slave.
         Preparamos o pacote com o valor ADC atual.
      */

      uint16_t valor = adc_value;

      tx_buffer[0] = (uint8_t)(valor >> 8);
      tx_buffer[1] = (uint8_t)(valor & 0xFF);
      tx_buffer[2] = tx_buffer[0] ^ tx_buffer[1];
      tx_buffer[3] = 0xA5;

      HAL_I2C_Slave_Seq_Transmit_IT(hi2c,
                                    tx_buffer,
                                    sizeof(tx_buffer),
                                    I2C_LAST_FRAME);
    }
    else
    {
      /*
         Neste exemplo o slave não recebe comandos do master.
         Caso deseje, aqui poderia ser implementado o recebimento de comandos.
      */
    }
  }
}

/*
   Quando a escuta termina, habilitamos novamente o modo listen.
   Isso permite que o slave responda às próximas leituras do master.
*/
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
  if (hi2c->Instance == I2C1)
  {
    HAL_I2C_EnableListen_IT(hi2c);
  }
}

/*
   Callback de erro do I2C.
   Em caso de erro, tentamos reativar a escuta.
*/
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
  if (hi2c->Instance == I2C1)
  {
    HAL_I2C_EnableListen_IT(hi2c);
  }
}

/* USER CODE END 4 */
```

A função `MX_I2C1_Init()` gerada pelo CubeMX deve ficar semelhante a esta:

```c
static void MX_I2C1_Init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;

  /*
     Endereço próprio do slave.
     No HAL, normalmente se usa o endereço deslocado 1 bit à esquerda.
     O endereço real no barramento é 0x30.
  */
  hi2c1.Init.OwnAddress1 = I2C_SLAVE_ADDR_7BIT << 1;

  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
}
```

---



# Observações importantes

Use sempre **GND comum** entre as duas placas. Sem isso, o I2C pode falhar.

O barramento I2C precisa de **pull-up** em SDA e SCL. Em bancada, valores comuns são **4,7 kΩ** para 3,3 V.


## Codigo ESP32 S3 Master

### 
```java


// altere os pinos para ESP32 S3 i2c GPIO 8 (SDA) GPIO 9 (SCL)
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define STM32_SLAVE_ADDR 0x30

// porta ic2 1
#define I2C_A_SDA 8 // GPIO8
#define I2C_A_SCL 9 // GPIO9

// porta ic2 2
#define I2C_B_SDA 17 // GPIO17
#define I2C_B_SCL 18 // GPIO18

// Define display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool lerADC_STM32(uint16_t &adc, float &tensao)
{
  uint8_t rx[4];
  /*
     Solicita 4 bytes do STM32F411 slave.
     O STM32 deve estar configurado como slave no endereço 0x30.
  */
  Wire1.requestFrom(STM32_SLAVE_ADDR, 4);

  if (Wire1.available() != 4)
  {
    return false;
  }

  for (int i = 0; i < 4; i++)
  {
    rx[i] = Wire1.read();
  }

  /*
     Verificação simples para evitar mostrar lixo no display.
  */
  uint8_t checksum = rx[0] ^ rx[1];

  if (checksum != rx[2])
  {
    return false;
  }

  if (rx[3] != 0xA5)
  {
    return false;
  }

  /*
     Reconstrói o valor ADC de 16 bits.
     Como o ADC é de 12 bits, o valor útil estará entre 0 e 4095.
  */
  adc = ((uint16_t)rx[0] << 8) | rx[1];

  /*
     Converte para tensão considerando referência de 3,3 V.
  */
  tensao = (adc * 3.3f) / 4095.0f;

  return true;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_A_SDA, I2C_A_SCL);
   Wire1.begin(I2C_B_SDA, I2C_B_SCL);

  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 10);
  // Display static text
  display.println("IFSP CATANDUVA");
  display.display(); 

  // fim setup
    Serial.print("fim setup ");
}

void loop() {
  
  uint16_t adc = 0;
  float tensao = 0.0f;

  if (lerADC_STM32(adc, tensao))
  {
    Serial.print("ADC STM32: ");
    Serial.print(adc);
    Serial.print(" | Tensao: ");
    Serial.print(tensao, 3);
    Serial.println(" V");
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 10);
  display.println("IFSP CATANDUVA");
  display.setCursor(20, 30);
  display.println(adc);
  display.display(); 
  delay(1000);
}
```

## Comunicação com a mesma porta I2C utilizada pelo display mude

```java
 Wire.requestFrom(STM32_SLAVE_ADDR, 4);

  if (Wire.available() != 4)
  {
    return false;
  }

  for (int i = 0; i < 4; i++)
  {
    rx[i] = Wire.read();
```
