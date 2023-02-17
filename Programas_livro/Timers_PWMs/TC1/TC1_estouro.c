//----------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //
//=============================================================================	//
//      HABILITANDO A INTERRUP��O POR ESTOURO DO TC1							//
//=============================================================================	//

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define cpl_bit(y,bit) 	(y^=(1<<bit))	//troca o estado l�gico do bit x da vari�vel Y
#define LED		PB5

//-----------------------------------------------------------------------------
ISR(TIMER1_OVF_vect)					//interrup��o do TC1
{
	cpl_bit(PORTB,LED);
}
//-----------------------------------------------------------------------------
int main()
{
	DDRB  = 0b00100000;					//somente pino do LED como sa�da
	PORTB = 0b11011111;					//apaga LED e habilita pull-ups nos pinos n�o utilizados
	
	TCCR1B = (1<<CS12) | (1<<CS10);		//TC1 com prescaler de 1024, a 16 MHz gera uma interrup��o a cada 4,19 s
	TIMSK1 = 1<<TOIE1;					//habilita a interrup��o do TC1
	sei();								//habilita interrup��es globais

	while(1)
	{
		//Aqui vai o c�digo, a cada estouro do TC1 o programa desvia para ISR(TIMER1_OVF_vect)
	}
}
//==============================================================================
