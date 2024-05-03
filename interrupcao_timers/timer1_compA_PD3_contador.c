//----------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //
//=============================================================================	//
//          TC1 estouro na igualdade de comparação	- sinal externo 			//
//                       Pisca LED a cada 1 segundo     						//   
//=============================================================================	//

#include <avr/io.h>
#include <avr/interrupt.h>

#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))
#define LED		PB5

//----------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)		//sub-rotina de interrupção por igualdade de comparação
{
	cpl_bit(PORTB,PB5);		//troca o estado do LED do pino PB5
}
//----------------------------------------------------------------------------
int main()
{
	DDRD = 0x00;			//PORTD será a entrada do sinal de clock para o TC1 (PD3)
	DDRB  = 1<<PB5;			//pino PB5 é a saída para o LED	de sinalização
		
	TIMSK1 = (1<<OCIE1A);	//habilita a interrupção do TC1 por igualdade de comparação
	TCCR1B = (1<<WGM12)|(1<<CS12) | (1<<CS11) |(1<<CS10);//clock externo  contagem na borda de subida - modo CTC
	OCR1A = 10;							/*valor para a contagem máxima do TC1 (conta 60 vezes) – VALOR DE COMPARAÇÃO. 
										Como o sinal de clock externo é de 60 Hz, é gerada uma interrupção a cada 1 s*/
	sei();								//liga a interrupção
	
    while(1){}
}
//============================================================================
