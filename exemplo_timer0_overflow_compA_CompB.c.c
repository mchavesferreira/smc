/*
 * exemplo_timer0_overflow_compA_CompB.c
 *
 * versao: 10/12/2020 10:44:08
 * Author/Adaptação : Marcos Chaves
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>		//biblioteca para o uso das rotinas de _delay_
#include <avr/interrupt.h>

#include "def_principais.h"			//inclusão do arquivo com as principais definições

volatile unsigned char segundos, minutos, horas;
volatile  unsigned char conta;

// esta interrupção é executada quando TCNT0=OCR0A
ISR(TIMER0_COMPA_vect)					//interrupção do comparação OCRA Timer 0
{
	cpl_bit(PORTB,0);
}

// esta interrupção é executada quando TCNT0=OCR0B
ISR(TIMER0_COMPB_vect)					//interrupção do  comparação OCRB Timer 0
{
	 cpl_bit(PORTB,1);
}

//** tempo de estouro= 62,5ns * (255-100+1) * 1024 = 9,98ms
ISR(TIMER0_OVF_vect)					//interrupção do TC0
{   conta++;
	TCNT0=100; // 156 contagens equivalem a 10ms em 16mhz
	if(conta==100) // 100* 10ms = 1 seg
	{   
		segundos++;
		cpl_bit(PORTD,2); // inverte led segundos
    	conta=0;
	}
}


int main()
{
	DDRB  = 0b00111111;					//somente pino do LED como saída
	PORTB = 0b00000000;					//apaga LED 
	
	DDRD  = 0b11111111;					//somente pino do LED como saída
	
	UCSR0B = 0x00;				//PD0 e PD1 como I/O genérico, para uso no Arduino
    DDRC= 0b00000000;  // entrada
    PORTC= 0b11111111;
	
////////////////////  ROTINAS LED ////////////////////////////	

TCCR0A = 0b01010000;

	/* TCCR0A  Registrador de controle A do TC0
	COM0A1 COM0A0 COM0B1 COM0B0  -     -     WGM01 WGM00
	 7        6     5      4     3     2       1     0

	 COM0A1 COM0A0 controlam o comportamento do pino 0C0A pino D6 (modos normal, CTC, pwm rapido)
	   0      0  - pino 0C0A desconectado
	   0      1  - mudanca de estado na igualdade
	   1      0  - aterrado na igualdade
	   1      1  - Ativo  na igualdade

	   COM0B1 COM0B0  controlam o comportamento do pino 0C0B  pino D5
	   0      0  - pino 0C0B desconectado
	   0      1  - mudanca de estado na igualdade
	   1      0  - aterrado na igualdade
	   1      1  - Ativo  na igualdade

	   WGM02 WGM01 WGM00 bits do modo de controle, fonte do valor maximo e forma de onda
	   0     0     0  - normal     TOP em FF
	   0     0     1  - pwm fase corrigida top em FF
	   0     1     0  - CTC        TOP em 0CR0A
	   0     1     1  - pwm rapido  TOP em FF
	   1     0     0  - 
	   1     0     1  - pwm fase corrigida top em 0CR0A
	   1     1     0   -
	   1     1     1  - pwm rapido TOP em 0CR0A
	*/
	
	TCCR0B = (1<<CS02) | (1<<CS00);		//TC0 com prescaler de 1024, a 16 MHz gera uma interrupção a cada 16,384 ms
	/* TCCR0B  Registrador de controle B do TC0
	F0C0A  FOC0B   -    -   WGM02  CS02  CS01  CS00
	7        6     5    4     3      2    1      0

	CS02  CS01  CS00  bits de selecao do prescaler
	   0     0     0  - sem fonte de clock tc0 parado
	   0     0     1  - prescaler =1
	   0     1     0  - prescaler = 8
	   0     1     1  - prescaler = 64
	   1     0     0  - prescaler = 256
	   1     0     1  - prescaler = 1024
	   1     1     0  - clock externo pino T0 (pd4) contagem borda descida
	   1     1     1  - clock externo pino T0 (pd4) contagem borda subida     
	*/

	TIMSK0 = 1<< OCIE0B | 1<< OCIE0A  |  1<<TOIE0  ;			//		//habilita a interrupção do TC0
	/* TIMSK0 Interruptor de mascara do contador TC0
	- - - - - OCIE0B OCIE0A TOIE0
	7 6 5 4 3   2      1      0
	0CIE0B ativa a interrupção na igualdade de comparação 0CR0B
	0CIE0A ativa a interrupção na igualdade de comparação 0CR0A
	TOIE0  ativa a interrupção de estouro em TOP=FF

	*/
  TCNT0=100;  // contagem iniciando em 100
	
	sei();								//habilita interrupções globais

  OCR0A=250;   // Valor de comparação
  OCR0B=105;

	while(1)
	{
		
			cpl_bit(PORTB,3);
			_delay_ms(1000);
			                    
							 
	}
}
//==============================================================================

