# Leitura AD

## 1. Teoria: Conversor Analógico-Digital no STM32F411

Em sistemas embarcados, muitos dispositivos, como sensores, potenciômetros e transdutores, geram sinais analógicos que precisam ser convertidos em valores digitais para serem processados pelo microcontrolador. Essa função é realizada pelo ADC, ou Conversor Analógico-Digital.

O STM32F411 possui um ADC do tipo SAR (*Successive Approximation Register*) com resolução de 12 bits, permitindo representar a tensão medida por valores de 0 a 4095. Considerando uma referência de 3,3 V, uma entrada de 0 V resulta em valor próximo de 0, enquanto uma entrada próxima de 3,3 V resulta em valor próximo de 4095.

O ADC pode ler diferentes canais analógicos por meio de uma seleção interna semelhante a um multiplexador. As conversões podem ocorrer em modo simples, contínuo ou em sequência de canais (*scan mode*). Também é possível iniciar conversões por software ou por eventos gerados por temporizadores.

Quando associado ao DMA, o ADC transfere os dados convertidos diretamente para a memória, reduzindo a carga da CPU. Assim, o ADC do STM32F411 permite medir grandezas físicas e utilizá-las em aplicações de monitoramento, controle e aquisição de dados.

<img src=../imagens/sar.png>

A figura apresenta a estrutura básica de um conversor ADC do tipo SAR, usado para transformar uma tensão analógica em um valor digital.
O sinal de entrada passa primeiro pelo bloco SHA (*Sample-and-Hold*), responsável por amostrar a tensão e mantê-la estável durante o tempo necessário para a conversão.
Em seguida, o comparador verifica a diferença entre a tensão amostrada e a tensão gerada internamente pelo DAC. A lógica SAR ajusta esse valor passo a passo, por aproximações sucessivas, até encontrar o número digital que melhor representa a tensão de entrada.
A temporização controla os instantes de amostragem, comparação e atualização dos blocos internos, garantindo que a conversão ocorra de forma ordenada e precisa.

Para uma descrição completa de todos os modos disponíveis, recomenda-se consultar a nota de aplicação <a href=https://www.st.com/content/ccc/resource/technical/document/application_note/c4/63/a9/f4/ae/f2/48/5d/CD00258017.pdf/files/CD00258017.pdf/jcr:content/translations/en.CD00258017.pdf>AN3116 da STMicroelectronics</a>.


### Características do ADC

Conjunto de parâmetros que define como o conversor analógico-digital mede, converte e representa uma tensão analógica em valor digital.

### Resolução

Quantidade de bits usada na conversão, determinando quantos níveis digitais o ADC consegue representar.

### Taxa de amostragem

Quantidade de leituras ou conversões que o ADC consegue realizar por segundo, geralmente expressa em amostras por segundo.

### Tensão de referência

Tensão máxima usada como base de comparação para converter a entrada analógica em valor digital.

### Resolução de tensão

Menor variação de tensão que o ADC consegue distinguir entre dois níveis digitais consecutivos.

Segue revisado, com uma linha para cada conceito:

## Polling, Interrupção e DMA

Ao trabalhar com leituras ADC, podem ser escolhidos três métodos principais para obter o resultado da conversão:

### Polling

O microcontrolador inicia a conversão ADC e fica aguardando até que o resultado esteja disponível.

### Interrupção

O microcontrolador inicia a conversão ADC e continua executando outras tarefas, sendo avisado por uma interrupção quando a leitura termina.

### DMA

O ADC transfere automaticamente os dados convertidos para a memória, sem exigir intervenção constante da CPU.

## Descrição dos Blocos funcionais

A figura a seguir, mostra a arquitetura interna de um bloco ADC do STM32F411. A ideia geral continua sendo: um sinal analógico entra por um pino, passa por um multiplexador, é convertido para número digital e o resultado vai para registradores. Porém, no STM32 há alguns blocos extras importantes que não aparecem nos ADCs mais simples.

<a href=blocosad_stm32f411.png><img src=blocosad_stm32f411.png width=400 height=400 border=0></a>

O bloco Regular channels representa o grupo principal de conversões do ADC.Esse é o modo mais usado. Quando você faz uma leitura simples com HAL, normalmente está usando o grupo regular.

O bloco Injected channels é um recurso mais avançado.Ele permite criar um grupo especial de conversões com prioridade maior. A ideia é que uma conversão “injetada” possa interromper ou ser encaixada no fluxo das conversões regulares.

DMA request. O ADC pode pedir ao DMA para transferir automaticamente os resultados das conversões para uma área da memória RAM, sem a CPU precisar copiar valor por valor.

Flags são bits de status. Elas indicam que algum evento aconteceu.: OVR, EOC, JEOC e AWD

Bits de habilitação de interrupção: OVRIE, EOCIE, JEOCIE, AWDIE

ADC Interrupt to NVIC- Quando o ADC gera uma interrupção, o pedido vai para o NVIC. O NVIC decide se a CPU deve parar o que está fazendo e executar a rotina de interrupção do ADC. O NVIC é o controlador de interrupções do Cortex-M.

Analog watchdog: é um comparador digital interno associado ao ADC.

EXTSEL - Seleciona qual evento externo vai disparar o ADC, enquanto EXTEN define em qual borda o disparo acontece.

JEXTSEL e JEXTEN — gatilho externo do grupo injetado. São equivalentes aos blocos EXTSEL e EXTEN, mas para o grupo injetado.

# 2.Prática com códigos

## funções HALL genéricas

```java
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);
void HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc);
```

## 2.1 Método Polling

Altere a frequência de clock com o cristal externo em 48MHZ

Configure AD para o canal :  Analog > ADC selecione "IN7", mantenha as configurações padrões

Hailibite o TIM3 e configure para gerar uma interrução a cada um segundo, utilizando preescalaer em 48000-1 e contador em 1000-1

<img src=../imagens/tim3.png>
<BR><BR>
<img src=../imagens/in7.png>


### codigo para leitura AD com temporizador tim3

```java
#include <stdio.h>
#include <string.h>
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"

ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim3;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM3_Init(void);

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();

  ssd1306_Init();

  char buff[64];
  volatile uint32_t leitura_ad = 0;

  HAL_TIM_Base_Start(&htim3);

  while (1)
  {
    if (__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE))
    {
      __HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);

      HAL_ADC_Start(&hadc1);
      HAL_ADC_PollForConversion(&hadc1, 100);
      leitura_ad = HAL_ADC_GetValue(&hadc1);
      HAL_ADC_Stop(&hadc1);

      ssd1306_Fill(Black);
      ssd1306_SetCursor(4, 22);
      ssd1306_WriteString("Leitura AD", Font_16x15, White);

      ssd1306_SetCursor(4, 44);
      sprintf(buff, "%lu ", (unsigned long)leitura_ad);

      ssd1306_WriteString(buff, Font_11x18, White);
      ssd1306_UpdateScreen();
    }
  }
}

```


## 2.2 Método ADC por interrução

Considere as configurações realizadas no método polling, habilitando o método interrupção. Vá em ANALOG> ADC > NVIC Setting e habilite a interrupção

Como de costume, precisamos definir a rotina de serviço de interrupção (ISR) conectada à interrupção do ADC, atribuir a prioridade de interrupção desejada e habilitar a IRQ correspondente. Como todos os outros periféricos da HAL, precisamos chamar a função HAL_ADC_IRQHandler() da ISR do ADC e implementar a rotina de retorno de chamada HAL_ADC_ConvCpltCallback(), que é chamada automaticamente pela HAL quando uma conversão termina. Finalmente, todas as interrupções relacionadas ao ADC são habilitadas iniciando o ADC usando a função HAL_ADC_Start_IT().


```java
#include <stdio.h>
#include <string.h>
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"

ADC_HandleTypeDef hadc1;
I2C_HandleTypeDef hi2c1;
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart1;
uint8_t adc_Flag;
volatile uint32_t leitura_ad;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART1_UART_Init(void);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
   leitura_ad = HAL_ADC_GetValue(&hadc1);
   adc_Flag = 1;

   char msg[50];
   sprintf(msg, "%lu\r\n", (unsigned long)leitura_ad);
   HAL_UART_Transmit(&huart1, (uint8_t *)msg, strlen(msg), 1000);
}

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();

  ssd1306_Init();
  char buff[64];
  adc_Flag = 0;
  HAL_TIM_Base_Start(&htim3);
  HAL_ADC_Start_IT(&hadc1);

  while (1)
  {
    if (adc_Flag == 1)
    {
      adc_Flag = 0;

      ssd1306_Fill(Black);
      ssd1306_SetCursor(4, 22);
      ssd1306_WriteString("Leitura AD", Font_16x15, White);

      ssd1306_SetCursor(4, 44);
      sprintf(buff, "%lu ", (unsigned long)leitura_ad);

      ssd1306_WriteString(buff, Font_11x18, White);
      ssd1306_UpdateScreen();

      HAL_Delay(200);

      HAL_ADC_Start_IT(&hadc1);
    }
  }
}

```


## 2.3 Método Conversão AD em modo DMA

No **STM32F411**, a conversão do **ADC em modo DMA** funciona assim: o ADC faz as leituras analógicas e o **DMA copia automaticamente os valores convertidos para um vetor na RAM**, sem a CPU precisar buscar cada amostra manualmente.

Esse modo é muito útil quando você quer:

```text
ler continuamente um canal analógico
ler vários canais ADC em sequência
usar um timer para amostrar em frequência fixa
reduzir o uso da CPU
```

### Ideia principal

Em vez de fazer:

```c
HAL_ADC_Start(&hadc1);
HAL_ADC_PollForConversion(&hadc1, timeout);
valor = HAL_ADC_GetValue(&hadc1);
```

você usa:

```c
HAL_ADC_Start_DMA(&hadc1, buffer_adc, tamanho);
```

A partir daí, o ADC converte e o DMA grava os resultados no vetor:

```c
uint32_t buffer_adc[4];
```

Por exemplo, se você estiver lendo 4 canais, o DMA pode preencher:

```text
buffer_adc[0] -> canal 1
buffer_adc[1] -> canal 2
buffer_adc[2] -> canal 3
buffer_adc[3] -> canal 4
```

### Passos para usar ADC com DMA no STM32F411

Primeiro você configura o **ADC1** no CubeMX. No STM32F411, normalmente usa-se o **ADC1**, porque ele é o conversor ADC principal disponível nessa família.

Depois, configure o ADC conforme o tipo de leitura:

```text
Scan Conversion Mode: Enabled, se usar vários canais
Continuous Conversion Mode: Enabled, se quiser conversão contínua
DMA Continuous Requests: Enabled
Data Alignment: Right
Resolution: 12 bits
```


Clica em Analog > ADC DMA Settings, seleciona "ADC"  e e clique em "ADD"

<img src=../imagens/configura_dma1.png>

Adiciona o novo canal DMA,  configura em modo "normal" e habilita "memory"

<img src=../imagens/configura_dma2.png?

Volte em "Parameter Setting" e altere Conversao em modo continuo habilitado (Enable) e as requisições DMA

Gere os codigos

Em core/src/main.c  adicione as biblioecas 

```java
#include "stdio.h"
#include "string.h"
```

Crei um array para armazenar a leitura do ADC
```java
uint16t adc_data[1];
```

Adicione a função callback que será chamada quando DMA completar a transferência de dados


Depois você configura o **DMA** associado ao ADC1. No STM32F411, o ADC1 usa normalmente:

```text
DMA2
Stream 0
Channel 0
```

O DMA pode ser configurado como:

```text
Mode: Circular
Peripheral to Memory
Peripheral increment: Disabled
Memory increment: Enabled
Data width: Half Word ou Word
```

O modo **Circular** é importante quando você quer que o ADC fique convertendo continuamente e preenchendo o mesmo buffer em ciclo.

### O exemplo a seguir, faz a leitura de dois canais diretamente com DMA


### Ligação entre ADC e DMA

No código HAL, o DMA precisa ser ligado ao ADC com a macro:

```c
__HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);
```

Quando você usa CubeMX/CubeIDE, isso geralmente é gerado automaticamente dentro da função:

```c
HAL_ADC_MspInit()
```

### Iniciando a conversão

Depois da inicialização do sistema, GPIO, DMA e ADC, você inicia assim:

```c
uint32_t adc_buffer[1];

HAL_ADC_Start_DMA(&hadc1, adc_buffer, 1);
```

Para vários canais:

```c
uint32_t adc_buffer[3];

HAL_ADC_Start_DMA(&hadc1, adc_buffer, 3);
```

Nesse caso, o tamanho passado deve corresponder ao número de conversões da sequência ADC.

### Callback de fim de conversão

Quando o DMA termina de preencher o buffer, a HAL pode chamar:

```c
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
        // dados novos disponíveis em adc_buffer
    }
}
```

Se o DMA estiver em modo circular, essa função será chamada repetidamente a cada ciclo completo do buffer.

### Resumo prático para STM32F411

Para usar ADC com DMA no STM32F411:

```text
1. Configure o ADC1.
2. Ative DMA Continuous Requests.
3. Configure o DMA2 Stream 0 Channel 0 para ADC1.
4. Use modo Circular se quiser leitura contínua.
5. Inicie com HAL_ADC_Start_DMA().
6. Leia os valores no vetor preenchido pelo DMA.
7. Use HAL_ADC_ConvCpltCallback() se quiser tratar o fim da conversão.
```



```c
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

uint8_t adc_Flag = 0;
uint16_t pot1 = 0;
uint16_t pot2 = 0;

volatile uint32_t readValue[2];

char buffer[50];
char buff[64];

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART1_UART_Init(void);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1)
  {
    pot1 = (uint16_t)readValue[0];
    pot2 = (uint16_t)readValue[1];
    adc_Flag = 1;
  }
}

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();

  ssd1306_Init();

  HAL_TIM_Base_Start(&htim3);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)readValue, 2);

  while (1)
  {
    if (adc_Flag == 1)
    {
      adc_Flag = 0;

      snprintf(buffer, sizeof(buffer), "Pot1: %d, Pot2: %d\r\n", pot1, pot2);
      HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), 100);

      ssd1306_Fill(Black);

      ssd1306_SetCursor(4, 15);
      ssd1306_WriteString("Leitura AD", Font_16x15, White);

      ssd1306_SetCursor(4, 30);
      snprintf(buff, sizeof(buff), "Pot1: %d", pot1);
      ssd1306_WriteString(buff, Font_16x15, White);

      ssd1306_SetCursor(4, 45);
      snprintf(buff, sizeof(buff), "Pot2: %d", pot2);
      ssd1306_WriteString(buff, Font_16x15, White);

      ssd1306_UpdateScreen();

      HAL_Delay(200);
    }
  }
}

```


# Referências
<a href=https://www.st.com/resource/en/reference_manual/rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf> Reference Manual STM32F411<a/>

<a href=https://www.st.com/resource/en/application_note/cd00211314.pdf>How to optimize the ADC accuracy </a>


https://community.st.com/t5/stm32cubeide-mcus/hal-adc-convcpltcallback-only-called-once/td-p/637221

https://sourcevu.sysprogs.com/stm32/HAL/symbols/HAL_ADCEx_MultiModeStart_DMA

https://deepbluembedded.com/stm32-adc-read-example-dma-interrupt-polling/


