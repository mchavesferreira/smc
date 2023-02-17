//----------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //
//=============================================================================	//
//       TC2 COM CRISTAL EXTERNO DE 32,768 kHz    								//
//       Rotina para implementar um relógio e piscar um LED   					//
//=============================================================================	//

#define F_CPU 1000000UL						//frequência de operação de 1 MHz
#include <avr/io.h>
#include <avr/interrupt.h>

#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))	//complementa bit 
#define LED PB5

/*variáveis com os valores para o relógio precisam ser tratadas
em um código adequado. Variáveis globais que são utilizadas 
dentro de interrupções e lidas fora delas devem ser declaradas
como volatile. Isto é uma exigência para o compilador. 
Respostas imprevisíveis correrão se o comando volatile não for empregado.*/	

volatile unsigned char segundos, minutos, horas;

//-----------------------------------------------------------------------------
ISR(TIMER2_OVF_vect)		//entrada aqui a cada 1 segundo
{							//rotina para contagem das horas, minutos e segundos
	cpl_bit(PORTB,LED);		//pisca LED

	segundos++;				

	if(segundos == 60) 
	{
		segundos = 0;
		minutos++;

		if (minutos == 60)
		{  
			minutos = 0;
					 horas++;

			if (horas == 24)
				horas = 0;
		} 
	}
}
//-----------------------------------------------------------------------------
int main()
{
	DDRB = 0b00100000;				//cristal ext., não importa a config. os pinos TOSC1 e TOSC2
	PORTB= 0b11011111;				//pull-ups habilitados nos pinos não utilizados

	ASSR  = 1<<AS2;					//habilita o cristal externo para o contador de tempo real
	TCCR2B = (1<<CS22)|(1<<CS20);	/*prescaler = 128, freq. p/ o contador -> 32.768/128 = 256 Hz.
									Como o contador é de 8 bits, ele conta 256 vezes, 
									resultando em um estouro preciso a cada 1 segundo*/
	TIMSK2 = 1<<TOIE2;  			//habilita interrupção do TC2

	sei();	 		  				//habilita interrupção global

	while(1)
	{}								//código principal (display, ajuste de hora, minutos, etc..)
}
//==============================================================================
