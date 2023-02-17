//------------------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.								//	
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
// HABILITANDO AS INTERRUP��ES INT0 e INT1 POR TRANSI��O E N�VEL, RESPECTIVAMENTE		//
//=====================================================================================	//
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Defini��es de macros - empregadas para o trabalho com bits
#define	set_bit(Y,bit_x) (Y|=(1<<bit_x))	//ativa o bit x da vari�vel
#define	clr_bit(Y,bit_x) (Y&=~(1<<bit_x))	//limpa o bit x da vari�vel 
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))  	//testa o bit x da vari�vel
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))	//troca o estado do bit x 

#define LED PB5		//LED est� no pino PB5

ISR(INT0_vect);
ISR(INT1_vect);

//-------------------------------------------------------------------------------------
int main()
{
    DDRD  = 0x00; 			//porta D entrada
	PORTD = 0xFF; 			//pull-ups habilitados na porta D
	DDRB  = 0b00100000; 	//somente pino do LED como sa�da
	PORTB = 0b11011111;		//desliga LED e habilita pull-ups 
	
	UCSR0B = 0x00;			//necessario desabilitar RX e TX para trabalho com os pinos do PORTD no Arduino	

	EICRA = 1<<ISC01;      	//interrup��es externas: INT0 na borda de descida, INT1 no n�vel zero.
	EIMSK = (1<<INT1) | (1<<INT0);//habilita as duas interrup��es
	sei();					//habilita interrup��es globais, ativando o bit I do SREG
	
	while(1){}
}
//-------------------------------------------------------------------------------------
ISR(INT0_vect)				//interrup��o externa 0, quando o bot�o � pressionado o LED troca de estado
{
  	cpl_bit(PORTB,LED);
}
//-------------------------------------------------------------------------------------
ISR(INT1_vect)				//interrup��o externa 1, mantendo o bot�o pressionado o LED pisca
{
	cpl_bit(PORTB,LED);	
	_delay_ms(200);			//tempo para piscar o LED	
}
//====================================================================================
