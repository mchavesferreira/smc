//----------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //

#define F_CPU 16000000UL
#include <avr/io.h>

int main(void)
{
    DDRB  = 0b00000110;			//pinos OC1B e OC1A (PB2 e PB1) como saída
	PORTB = 0b11111001;			//zera saídas e habilita pull-ups nos pinos não utilizados	
	
	//MODO CTC - TOP = ICR1
	TCCR1A = 0b01010000;		//habilita OC1A e OC1B para trocar de estado na igualdade de comparação
	TCCR1B = 0b00011011;		//liga TC1 com prescaler = 64.
	ICR1 = 10000;				//valor máximo de contagem

	while(1) 
    {
								//o programa principal vai aqui 
    }
}

/*	OUTROS MODOS

	//fast PWM, TOP = ICR1, OC1A e OC1B habilitados
	TCCR1A = 0b10100010;		//PWM não invertido nos pinos OC1A e OC1B
	TCCR1B = 0b00011001;		//liga TC1, prescaler = 1
	ICR1 = 35000;				//valor máximo para contagem
	OCR1A = 2000;				//controle do ciclo ativo do PWM 0C1A
	OCR1B = 100;				//controle do ciclo ativo do PWM OC1B
		
	//phase and frequency correct PWM, TOP = OCR1A
	TCCR1A = 0b00100011;		// OC1B habilitado, modo não invertido
	TCCR1B = 0b00011001;		//liga TC1, prescaler = 1 e habilita 
	OCR1A = 300;				//máximo valor para contagem
	OCR0B = 100;				//controle do ciclo ativo do PWM OC1B
	
*/
