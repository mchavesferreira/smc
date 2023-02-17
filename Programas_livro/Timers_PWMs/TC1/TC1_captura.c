//----------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //
//=============================================================================	//
//      HABILITANDO A INTERRUP��O POR CAPTURA									//
//=============================================================================	//
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define cpl_bit(y,bit) 	(y^=(1<<bit))	//troca o estado l�gico do bit x da vari�vel Y
#define LED		PB5

//--------------------------------------------------------------------------
/*interrup��o do TC1, toda vez que ocorrer um evento no pino ICP1 (PB0) 
ICR1 ter� o valor de contagem do TCNT1*/
//--------------------------------------------------------------------------
ISR(TIMER1_CAPT_vect)	
{
	cpl_bit(PORTB,LED);			//troca estado do pino PB5
}
//--------------------------------------------------------------------------
int main()
{
	DDRB  = 0b00100000;			//somente pino do LED como sa�da, bot�o no PB0
	PORTB = 0b11011111;			//apaga LED e habilita pull-ups nos outros pinos
	
	TCCR1B = 1<<CS10;			//TC1 com prescaler = 1
	TIMSK1 = 1<<ICIE1;			//habilita a interrup��o por captura
	sei();						//habilita interrup��es globais

	while(1)
	{
		//Aqui vai o c�digo, a cada evento no pino ICP1 o programa desvia para ISR(TIMER1_CAPT_vect)
	}
}
//===========================================================================