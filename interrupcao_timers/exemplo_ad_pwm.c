/*
 * exemplo leitura ad canal 0 ajustando pwm timer 0
 *
 * Created: 08/11/2018 
 * Author : Marcos Chaves
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>		//biblioteca para o uso das rotinas de _delay_
#include <avr/interrupt.h>
#include "LCD.h"
#include "def_principais.h"			//inclusão do arquivo com as principais definições
#include "USART.h"

void configura_AD(){
	// configura canal 0
	ADMUX = (1<<REFS0) | (1<<MUX2) | (1<<MUX0);			//Tensão interna de ref (+5V), canal ADC5
	ADCSRA = (1<<ADEN) | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//habilita o AD e define um prescaler de 128 (clk_AD = F_CPU/128), 125 kHz
}

signed int le_temp()
{
	set_bit(ADCSRA, ADSC);								//inicia a conversão
	while(tst_bit(ADCSRA,ADSC));						//espera a conversão ser finalizada	
	return (ADC);
}

void set_pwm_pb2(unsigned int valor)   // configura pwm pino PB2 timer 1
{	
	ICR1 = 1023; // estabelece o valor TOP para o PWM em 1023 = 10bit
	TCCR1A |= (1<<COM1B1);
	TCCR1B = (1<< WGM13)|(1<< CS11); //T=20ms //T=20ms prescaler 64
	TCCR1C = 0;
	OCR1B  = valor; //inicializa PWM para saida em tensão = 0 Vcc
	sei();
}



int main()
{
	DDRB  = 0b00111111;					//somente pino do LED como saída
	PORTB = 0b00000000;					//apaga LED 	
	DDRD  = 0b00100000;						//somente pino do LED como saída
	UCSR0B = 0x00;				//PD0 e PD1 como I/O genérico, para uso no Arduino
    DDRC= 0b00000000;  // entrada
	unsigned char digitos[tam_vetor];	//declaração da variável para armazenagem dos digitos
	unsigned int valorbinario;

	USART_Inic(MYUBRR);
    inic_LCD_4bits();
    configura_AD();
	set_pwm_pb2(0);
	
	//inicializa o LCD
	cmd_LCD(0x80,0);
	escreve_LCD("IFSP CATANDUVA");	//string armazenada na RAM
	
	while(1)
	{     
		valorbinario=le_temp();  // le o valor binario de 10 bits
		
		// imprime valor binario
		ident_num(valorbinario,digitos);
		cmd_LCD(0xCC,0);			//desloca o cursor
		cmd_LCD(digitos[3],1);
		cmd_LCD(digitos[2],1);
		cmd_LCD(digitos[1],1);
		cmd_LCD(digitos[0],1);
		OCR1B=valorbinario;
		ident_num(valorbinario,digitos);  // separa casas do numero
		USART_Transmite(digitos[3]);
		USART_Transmite(digitos[2]);
		USART_Transmite(digitos[1]);
		USART_Transmite(digitos[0]);
    	USART_Transmite('\n');	
		
		
		_delay_ms(100);					 
	}
}
//==============================================================================

