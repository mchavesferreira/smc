//----------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //

#define F_CPU 16000000UL
#include <avr/io.h>

int main(void)
{
    DDRD  = 0b01100000;				//pinos OC0B e OC0A (PD5 e PD6) como saída
	PORTD = 0b10011111;				//zera saídas e habilita pull-ups nos pinos não utilizados	
	
	//MODO CTC
	TCCR0A = 0b01010010;			//habilita OC0A e OC0B para trocar de estado na igualdade de comparação
	TCCR0B = 0b00000001;			//liga TC0 com prescaler = 1.
	OCR0A = 200;					//maximo valor de contagem
	OCR0B = 100;					//deslocamento de OC0B em relação a OC0A
	
	while(1) 
    {
        //O programa principal vai aqui 
    }
}
//------------------------------------------------------------------------------

/*	OUTROS MODOS

	//fast PWM, TOP = 0xFF, OC0A e OC0B habilitados
	TCCR0A = 0b10100011;			//PWM não invertido nos pinos OC0A e OC0B
	TCCR0B = 0b00000011;			//liga TC0, prescaler = 64
	OCR0A = 200;					//controle do ciclo ativo do PWM 0C0A
	OCR0B = 50;						//controle do ciclo ativo do PWM OC0B
		
	//fast PWM, TOP = OCR0A com OC0A gerando uma onda quadrada e OC0B um sinal PWM não-invertido
	TCCR0A = 0b01100011;			//OC0A e OC0B habilitados
	TCCR0B = 0b00001001;			//liga TC0, prescaler = 1 e ajusta modo para comparação com OCR0A
	OCR0A = 100;					//controle da periodo do sinal no pino OC0A
	OCR0B = 30;						//controle do ciclo ativo do PWM 0C0B

	//phase correct PWM, TOP = 0xFF
	TCCR0A = 0b10100001;			//OC0A e OC0B habilitados
	TCCR0B = 0b00000001;			//liga TC0, prescaler = 1
	OCR0A = 100;					//controle da periodo do sinal no pino OC0A
	OCR0B = 50;						//controle do ciclo ativo do PWM 0B
	
	//phase correct PWM, TOP = OCR0A
	TCCR0A = 0b01100011;			//OC0A e OC0B habilitado
	TCCR0B = 0b00001001;			//liga TC0, prescaler = 1 e habilita o pino OC0A para gerar um onda quadrada
	OCR0A = 200;					//controle do perodo do sinal no pino OC0A
	OCR0B = 10;						//controle do ciclo ativo do PWM OC0B
	
*/
