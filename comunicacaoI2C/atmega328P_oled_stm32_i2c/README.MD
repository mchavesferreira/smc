# Exemplo: ATmega328P + OLED SSD1306 + STM32F411 via I2C

## Objetivo

Este exemplo tem como objetivo demonstrar o uso do **barramento I2C** para comunicação entre diferentes dispositivos embarcados.

Neste projeto, o **ATmega328P** atua como **mestre I2C**, comunicando-se com dois dispositivos no mesmo barramento:

- um **display OLED SSD1306 0,96"**, usado para exibir os dados;
- um **STM32F411**, configurado como **escravo I2C**, código disponível neste <a href=https://github.com/mchavesferreira/smc/blob/main/comunicacaoI2C/stm32_esp32_i2c.md>link</a> responsável por realizar uma leitura analógica usando o ADC.

O valor lido pelo ADC do STM32F411 é enviado ao ATmega328P via I2C. Em seguida, o ATmega328P mostra esse valor no display OLED em duas formas:

- valor inteiro do ADC;
- valor convertido para tensão.

<img src=uno_stm32.png>
---

## Endereços I2C dos dispositivos

No barramento I2C, vários dispositivos podem compartilhar as mesmas linhas **SDA** e **SCL**. Para que o mestre consiga se comunicar com cada dispositivo separadamente, cada escravo deve possuir um **endereço I2C diferente**.

Neste exemplo, o **ATmega328P** atua como mestre e acessa dois dispositivos escravos no mesmo barramento:

| Dispositivo | Função | Endereço I2C de 7 bits |
|---|---|---|
| Display OLED SSD1306 | Exibição dos dados | `0x3C` |
| STM32F411 | Escravo que envia o valor ADC | `0x30` |

Assim, mesmo que o OLED e o STM32 estejam conectados às mesmas linhas **SDA** e **SCL**, o ATmega328P sabe com qual dispositivo está falando pelo endereço enviado no início da comunicação.


## Arquivo do exemplo

O projeto completo para experimentação encontra-se no arquivo: <a href=avrgcc_i2c_oled_stm32.rar>avrgcc_i2c_oled_stm32.rar</a>


```java

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>        // Necessária para dtostrf(), que converte float para string.

#include "i2c.h"           // Funções básicas do barramento I2C/TWI.
#include "oled_ssd1306.h"  // Funções para controle do display OLED SSD1306.
#include "i2c_stm.h"       // Funções para leitura do STM32F411 via I2C.

char buffer[20];           // Armazena o valor float convertido em texto.
uint16_t adc_stm = 0;      // Recebe o valor ADC enviado pelo STM32.
float tensao = 0.0;        // Armazena o valor ADC convertido para tensão.

int main(void)
{
	DDRB |= (1 << PB5);     // Configura PB5 como saída. No Arduino Uno, PB5 é o LED interno.

	oled_init();            // Inicializa o display OLED e a comunicação I2C usada por ele.

	while (1)
	{
		oled_font_size(0);  // Define o tamanho da fonte no display.

		oled_gotoxy(0, 0);  // Posiciona o cursor na coluna 0 e linha 0.
		oled_write("*IFSP Catanduva**");  // Escreve texto fixo ou texto formatado no OLED.

		if (stm_i2c_read_adc(&adc_stm) == STM32_I2C_OK)  // Lê o ADC enviado pelo STM32.
		{
			tensao = (adc_stm * 3.3) / 4095.0;  // Converte o ADC de 12 bits para tensão.

			oled_gotoxy(0, 2);
			oled_write("ADC STM32");

			oled_gotoxy(0, 4);
			oled_write("ADC: %4i", adc_stm);

			oled_gotoxy(0, 6);
			oled_write("V: ");

			dtostrf(tensao, 4, 2, buffer);  // Converte float em string: largura 4, 2 casas decimais.
			oled_write_str(buffer);         // Escreve no OLED uma string armazenada em variável.
			oled_write(" V");
		}

		_delay_ms(300);     // Aguarda 300 ms antes da próxima leitura.
	}
}
