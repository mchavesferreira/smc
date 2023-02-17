//----------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //
//=============================================================================	//
//          TC1 estouro na igualdade de compara��o	- sinal externo 			//
//                       Pisca LED a cada 1 segundo     						//   
//=============================================================================	//

#include <avr/io.h>
#include <avr/interrupt.h>

#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))
#define LED		PB5

//----------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)		//sub-rotina de interrup��o por igualdade de compara��o
{
	cpl_bit(PORTB,PB5);		//troca o estado do LED do pino PB5
}
//----------------------------------------------------------------------------
int main()
{
	DDRD = 0x00;			//PORTD ser� a entrada do sinal de clock para o TC1 (PD3)
	DDRB  = 1<<PB5;			//pino PB5 � a sa�da para o LED	de sinaliza��o
		
	TIMSK1 = (1<<OCIE1A)|(1<<TOIE1);	//habilita a interrup��o do TC1 por igualdade de compara��o
	TCCR1B = (1<<WGM12)|(1<<CS12) | (1<<CS11) |(1<<CS10);//clock externo  contagem na borda de subida - modo CTC
	OCR1A = 59;							/*valor para a contagem m�xima do TC1 (conta 60 vezes) � VALOR DE COMPARA��O. 
										Como o sinal de clock externo � de 60 Hz, � gerada uma interrup��o a cada 1 s*/
	sei();								//liga a interrup��o
	
    while(1){}
}
//============================================================================
