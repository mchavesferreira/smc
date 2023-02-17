//------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.					//	
//-------------------------------------------------------------------------	//
//========================================================================	//
//			SENSOR DE LUZ EMPREGANDO UM LDR									//
//========================================================================	//

#define F_CPU 16000000UL
#include <avr/io.h> 			//defini��es do componente especificado
#include <avr/interrupt.h>		//define macros para o tratamento de interrup.

#define	set_bit(Y,bit_x) (Y|=(1<<bit_x))	//ativa bit
#define	clr_bit(Y,bit_x) (Y&=~(1<<bit_x))	//limpa bit 
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))  	//testa bit

#define LED PB0

//---------------------------------------------------------------------------
int main()
{
    DDRB  = 0x01;			//pino do LED como sa�da
    DDRD  = 0x00;			//porta do comparador como entrada
	PORTD = 0xFF;			//habilita pull-ups
	PORTB = 0xFE;			//apaga LED e habilita pull-ups

	DIDR1 = 0b00000011;		//desabilita as entradas digitais nos pinos AIN0 e AIN1
	ACSR = 1<<ACIE;			//habilita interrup. por mudan�a de estado na sa�da do comparador
    sei();					//habilita a chave geral de interrup��es		

	while(1);
}
//---------------------------------------------------------------------------
//Interrup��o do Comparador Anal�gico
//---------------------------------------------------------------------------
ISR(ANALOG_COMP_vect)		//O LED ficar� ligado quando houver pouca luz (tens�o maior no terminal positivo do comparador)
{			    
   	if(tst_bit(ACSR,ACO))	//verifica qual mudan�a ocorreu na sa�da do comparador
		set_bit(PORTB,LED);
	else
		clr_bit(PORTB,LED);	
}
//===========================================================================
