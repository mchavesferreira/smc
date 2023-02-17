//------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								//	
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
// HABILITANDO AS INTERRUPÇÕES INT0 e INT1 POR TRANSIÇÃO E NÍVEL, RESPECTIVAMENTE		//
//=====================================================================================	//
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Definições de macros - empregadas para o trabalho com bits
#define	set_bit(Y,bit_x) (Y|=(1<<bit_x))	//ativa o bit x da variável
#define	clr_bit(Y,bit_x) (Y&=~(1<<bit_x))	//limpa o bit x da variável 
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))  	//testa o bit x da variável
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))	//troca o estado do bit x 

#define LED PB5		//LED está no pino PB5

ISR(INT0_vect);
ISR(INT1_vect);

//-------------------------------------------------------------------------------------
int main()
{
    DDRD  = 0x00; 			//porta D entrada
	PORTD = 0xFF; 			//pull-ups habilitados na porta D
	DDRB  = 0b00100000; 	//somente pino do LED como saída
	PORTB = 0b11011111;		//desliga LED e habilita pull-ups 
	
	UCSR0B = 0x00;			//necessario desabilitar RX e TX para trabalho com os pinos do PORTD no Arduino	

	EICRA = 1<<ISC01;      	//interrupções externas: INT0 na borda de descida, INT1 no nível zero.
	EIMSK = (1<<INT1) | (1<<INT0);//habilita as duas interrupções
	sei();					//habilita interrupções globais, ativando o bit I do SREG
	
	while(1){}
}
//-------------------------------------------------------------------------------------
ISR(INT0_vect)				//interrupção externa 0, quando o botão é pressionado o LED troca de estado
{
  	cpl_bit(PORTB,LED);
}
//-------------------------------------------------------------------------------------
ISR(INT1_vect)				//interrupção externa 1, mantendo o botão pressionado o LED pisca
{
	cpl_bit(PORTB,LED);	
	_delay_ms(200);			//tempo para piscar o LED	
}
//====================================================================================
