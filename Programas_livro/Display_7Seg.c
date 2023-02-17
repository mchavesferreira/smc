//--------------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.							//	
//--------------------------------------------------------------------------------- //
//================================================================================	//
//    		ESCREVENDO EM UM DISPLAY DE 7 SEGMENTOS ANODO COMUM						//
//================================================================================	//
#define F_CPU 16000000UL	//define a frequ�ncia do microcontrolador em 16MHz

#include <avr/io.h> 	 	//defini��es do componente especificado
#include <util/delay.h>		//biblioteca para o uso das rotinas de _delay_
#include <avr/pgmspace.h>	//biblioteca para poder gravar dados na mem�ria flash 

//Defini��es de macros - para o trabalho com os bits de uma vari�vel
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) //testa o bit x da vari�vel Y (retorna 0 ou 1)

#define DISPLAY	 PORTD		//define um nome auxiliar para o display  
#define BOTAO 	 PB0 		//define PB0 com o nome de BOTAO

//vari�vel gravada na mem�ria flash
const unsigned char Tabela[] PROGMEM = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};
//-----------------------------------------------------------------------------------

int main()
{
	unsigned char valor = 0;	//declara vari�vel local
	
	DDRB = 0b11111110;			//PB0 como pino de entrada, os demais pinos como sa�da
	PORTB= 0x01;				//habilita o pull-up do PB0		 
	DDRD = 0xFF;				//PORTD como sa�da (display)
	PORTD= 0xFF;				//desliga o display
	UCSR0B = 0x00;				//PD0 e PD1 como I/O gen�rico, para uso no Arduino

	while(1) 					//la�o infinito
	{
		if(!tst_bit(PINB,BOTAO))//se o bot�o for pressionado executa  
		{ 
			if(valor==0x0F)		//se o valor for igual a 0xF, zera o valor, 
				valor=0;
			else 				//se n�o o incrementa
				valor++;

			//decodifica o valor e mostra no display, busca o valor na Tabela.
			DISPLAY = pgm_read_byte(&Tabela[valor]); 
			
			_delay_ms(200);		//atraso para incremento autom�tico do nr. no display
			
		}//if bot�o

	}//la�o infinito
}
//===================================================================================

