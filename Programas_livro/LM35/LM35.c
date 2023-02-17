//------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.					//	
//-------------------------------------------------------------------------	//
//========================================================================	//
//			Sensor de temperatura LM35 - envio de dados para o PC			//
//			Resolução de 1 grau Centigrado									//
//========================================================================	//

#include "def_principais.h"
#include "USART.h"

const char msg[] PROGMEM = "Sensor de Temperatura LM35\n\0";

unsigned int temp;
unsigned char digitos[tam_vetor];
//--------------------------------------------------------------------------
int main()
{	
	DDRC = 0x00;
	PORTC = 0xFE;
	
	USART_Inic(MYUBRR);
	
	//configura ADC
	ADMUX  = 0b11000000;	//Tensão interna de ref (1.1V), canal 0 
	ADCSRA = 0b11101111;	//habilita o AD, habilita interrupção, modo de conversão contínua, prescaler = 128 
	ADCSRB = 0x00;			//modo de conversão contínua
	set_bit(DIDR0,0);		//desabilita pino PC0 como I/0, entrada do ADC0
		
	sei();
	
	escreve_USART_Flash(msg);
	
	while(1)
    {
        ident_num(temp,digitos);
		USART_Transmite(digitos[3]);
		USART_Transmite(digitos[2]);
		USART_Transmite(digitos[1]);
		USART_Transmite(',');
		USART_Transmite(digitos[0]);
		USART_Transmite(176);//simbolo 'o'
		USART_Transmite('C');
		USART_Transmite('\n');
		_delay_ms(1000);
    }
}
//--------------------------------------------------------------------------
ISR(ADC_vect)	
{
	temp = ADC + (ADC*19)/256;

	/* O LM35 apresenta uma saída de 10mV/oC
	O valor de leitura do AD é dado por ADC = Vin*1024/Vref,
	como Vref = 1,1V, para converter o valor do AD para graus Celsius, é
	necessário multiplicar o valor ADC por 1100/1024 
	(considerando um digito decimal antes da vírgula)
	Utilizando a simplificação matemática e mantendo a variável temp com 16
	bits, resulta: 1100/1024 = 1 + 19/256 */

}
//--------------------------------------------------------------------------