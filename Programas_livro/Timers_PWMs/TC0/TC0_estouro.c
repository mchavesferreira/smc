//----------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //
//=============================================================================	//
//       HABILITANDO A INTERRUPÇÃO POR ESTOURO DO TC0							//
//=============================================================================	//
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define cpl_bit(y,bit) 	(y^=(1<<bit))	//troca o estado lógico do bit x da variável Y
#define LED		PB5

//------------------------------------------------------------------------------
ISR(TIMER0_OVF_vect)					//interrupção do TC0
{
	cpl_bit(PORTB,LED);
}
//------------------------------------------------------------------------------
int main()
{
	DDRB  = 0b00100000;					//somente pino do LED como saída
	PORTB = 0b11011111;					//apaga LED e habilita pull-ups nos pinos não utilizados
	
	TCCR0B = (1<<CS02) | (1<<CS00);		//TC0 com prescaler de 1024, a 16 MHz gera uma interrupção a cada 16,384 ms
	TIMSK0 = 1<<TOIE0;					//habilita a interrupção do TC0
	sei();								//habilita interrupções globais

	while(1)
	{
		//Aqui vai o código, a cada estouro do TC0 o programa desvia para ISR(TIMER0_OVF_vect)
	}
}
//==============================================================================
