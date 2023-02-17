//----------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //
//=============================================================================	//
//       TC2 COM CRISTAL EXTERNO DE 32,768 kHz    								//
//       Rotina para implementar um rel�gio e piscar um LED   					//
//=============================================================================	//

#define F_CPU 1000000UL						//frequ�ncia de opera��o de 1 MHz
#include <avr/io.h>
#include <avr/interrupt.h>

#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))	//complementa bit 
#define LED PB5

/*vari�veis com os valores para o rel�gio precisam ser tratadas
em um c�digo adequado. Vari�veis globais que s�o utilizadas 
dentro de interrup��es e lidas fora delas devem ser declaradas
como volatile. Isto � uma exig�ncia para o compilador. 
Respostas imprevis�veis correr�o se o comando volatile n�o for empregado.*/	

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
	DDRB = 0b00100000;				//cristal ext., n�o importa a config. os pinos TOSC1 e TOSC2
	PORTB= 0b11011111;				//pull-ups habilitados nos pinos n�o utilizados

	ASSR  = 1<<AS2;					//habilita o cristal externo para o contador de tempo real
	TCCR2B = (1<<CS22)|(1<<CS20);	/*prescaler = 128, freq. p/ o contador -> 32.768/128 = 256 Hz.
									Como o contador � de 8 bits, ele conta 256 vezes, 
									resultando em um estouro preciso a cada 1 segundo*/
	TIMSK2 = 1<<TOIE2;  			//habilita interrup��o do TC2

	sei();	 		  				//habilita interrup��o global

	while(1)
	{}								//c�digo principal (display, ajuste de hora, minutos, etc..)
}
//==============================================================================
