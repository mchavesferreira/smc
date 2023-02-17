//----------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //
//=============================================================================	//
//      HABILITANDO A INTERRUPÇÃO POR CAPTURA									//
//=============================================================================	//
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define cpl_bit(y,bit) 	(y^=(1<<bit))	//troca o estado lógico do bit x da variável Y
#define LED		PB5

//--------------------------------------------------------------------------
/*interrupção do TC1, toda vez que ocorrer um evento no pino ICP1 (PB0) 
ICR1 terá o valor de contagem do TCNT1*/
//--------------------------------------------------------------------------
ISR(TIMER1_CAPT_vect)	
{
	cpl_bit(PORTB,LED);			//troca estado do pino PB5
}
//--------------------------------------------------------------------------
int main()
{
	DDRB  = 0b00100000;			//somente pino do LED como saída, botão no PB0
	PORTB = 0b11011111;			//apaga LED e habilita pull-ups nos outros pinos
	
	TCCR1B = 1<<CS10;			//TC1 com prescaler = 1
	TIMSK1 = 1<<ICIE1;			//habilita a interrupção por captura
	sei();						//habilita interrupções globais

	while(1)
	{
		//Aqui vai o código, a cada evento no pino ICP1 o programa desvia para ISR(TIMER1_CAPT_vect)
	}
}
//===========================================================================