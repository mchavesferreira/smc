/*
 * Medição de corrente com ADS1115.c
 *
 * Created: 24/09/2020 23:07:07
 * Author : JMM
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "def_principais.h"
#include "USART.h"
#include "i2cmaster.h"
#include "ads1115.h"
#include "LCD.h"

unsigned char digitos[4];
unsigned char TEMP[tam_vetor]; // vetor para separacao de caracteres int tempo = 0;

void imprime_usart(float valor);

const float fator = 100; // le 100A
const float multiplicador = 0.125; // ads.setGain(GAIN_ONE); 1x gain   +/- 4.096V  1bit =  0.125mV

int main(void)
{
    DDRB = 0b11111111;
	PORTB = 0b00000000;
	DDRD = 0xFF;
	PORTD = 0xFF;
	UCSR0B = 0x00;
	DDRC = (1<<4) | (1<<5);
	PORTC = 0b11111111;
	
	USART_Inic(MYUBRR);        //inicializa comunicação USART
	inic_LCD_4bits();          //inicializa LCD
	i2c_init();                //inicializa ADS 
		
	double tensao;
	double corrente, correnteirms;
	double sum =0.0;
	int cont = 0;
		
    while (1) 
    {
		tensao = ads1115_readADC_Diff_A0_1 (ADS1115_ADDR_GND, ADS1115_DR_475SPS, ADS1115_PGA_4_096 );
		corrente = tensao*fator*multiplicador;
		corrente /= 1000.0;
		sum+= corrente*corrente;
		cont++;
		
		if(cont>=50){
			correnteirms = (sqrt(sum/cont))/(sqrt(2));			
			sum = 0.0;
			cont=0;
			
			unsigned int Irms2 = correnteirms*100; //100 depende da magnitude da leitura
			
			cmd_LCD(0x80,0);
			escreve_LCD("Irms(A)=");
			
			ident_num(Irms2, digitos); //Irms deve ser unsigned >INT<, digitos deve ser unsigned CHAR
			cmd_LCD(digitos[3],1); // precisao depende do tamanho do vetor digitos > [4]
			cmd_LCD(digitos[2],1);
			escreve_LCD(".");
			cmd_LCD(digitos[1],1);
			cmd_LCD(digitos[0],1);
			
			imprime_usart(Irms2);
			
			_delay_ms(1000);
		}
		
    }
}


void imprime_usart(float valor) {
	ident_num(valor, TEMP); // rotina separa caracteres
	//USART_Transmite(TEMP[4]);
	USART_Transmite(TEMP[3]);
	USART_Transmite(TEMP[2]);
	escreve_USART (".");
	USART_Transmite(TEMP[1]);
	USART_Transmite(TEMP[0]);
	escreve_USART("\n " );
}