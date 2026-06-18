/*
 * Código AVR ATmega328P comunicando com OLED SSD1306 e STM32F411 via I2C.
 * O ATmega328P atua como mestre I2C.
 * O STM32F411 atua como escravo I2C e envia uma leitura ADC.
 * O valor ADC recebido é mostrado no OLED como inteiro e como tensão.
 * Endereço I2C do STM32: 0x30.
 * ADC considerado: 12 bits, faixa de 0 a 4095.
 * Referência de tensão considerada: 3,3 V.
 * Adaptação: Marcos Chaves - jun/2026.
 */

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