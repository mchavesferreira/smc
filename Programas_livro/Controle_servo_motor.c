//--------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							//	
//---------------------------------------------------------------------------------	//
/*-----------------------------------------------------------------------------------
	EXEMPLO DO CONTROLE DE DOIS MOTORES SERVO COM SINAIS PWM
	Uso do TC1 no modo PWM rápido, não invertido, pinos OC1A e OC1B
	Valor TOP de contagem em ICR1
------------------------------------------------------------------------------------*/

#define F_CPU 16000000UL
#include <avr/io.h> 

//Definições de macros
#define	set_bit(adress,bit)	(adress|=(1<<bit))	
#define	clr_bit(adress,bit)	(adress&=~(1<<bit))	

#define TOP 39999					//valor para a máxima contagem

int main()
{	
	DDRB  = 0b00000110;				//habilita os pinos OC1A e OC1B (PB1 e PB2) como saídas
	PORTB = 0b11111001;

									//TOP = (F_CPU/(N*F_PWM))-1, com N = 8 e F_PWM = 50 Hz
	ICR1 = TOP; 					//configura o período do PWM (20 ms)

	// Configura o TC1 para o modo PWM rápido via ICR1, prescaler = 8
	TCCR1A = (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1<<WGM12) | (1 << CS11);

	set_bit(TCCR1A,COM1A1);			//ativa o PWM no OC1B, modo de comparação não-invertido
									//para desabilitar empregar clr_bit(TCCR1A, COM1A1)
	set_bit(TCCR1A,COM1B1);			//ativa o PWM no OC1A, modo de comparação não-invertido
									//para desabilitar empregar clr_bit(TCCR1A, COM1B1)
	//Pulso de 2 ms em OC1A
	OCR1A = 4000; 	//regra de três para determinar este valor: ICR1(TOP) = 20 ms, OCR1A (4000) = 2 ms) 
		
	//Pulso de 1 ms em OC1B
	OCR1B = 2000; 	//regra de três para determinar este valor: ICR1(TOP) = 20 ms, OCR1B (2000) = 1 ms)
	 
	while(1)
	{}				//programa principal
}
//-----------------------------------------------------------------------------------
