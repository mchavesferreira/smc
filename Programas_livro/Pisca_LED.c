//------------------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.								//	
//------------------------------------------------------------------------------------- //

#define F_CPU 16000000UL	//define a frequ�ncia do microcontrolador 16MHz (necess�rio para usar as rotinas de atraso)
#include <avr/io.h> 	    //defini��es do componente especificado
#include <util/delay.h>		//biblioteca para o uso das rotinas de _delay_ms() e _delay_us()

//Defini��es de macros - empregadas para o trabalho com os bits de uma vari�vel ou registrador

#define	set_bit(Y,bit_x) (Y|=(1<<bit_x))	//ativa o bit x da vari�vel Y (coloca em 1)
#define	clr_bit(Y,bit_x) (Y&=~(1<<bit_x))	//limpa o bit x da vari�vel Y (coloca em 0) 
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))  	//testa o bit x da vari�vel Y (retorna 0 ou 1)
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))	//troca o estado do bit x da vari�vel Y (complementa)

#define LED PB5				//LED � o substituto de PB5 na programa��o     	

//--------------------------------------------------------------------------------------
int main( )
{
    DDRB = 0xFF;			//configura todos os pinos do PORTB como sa�das
	
	while(1)				//la�o infinito
    {
        set_bit(PORTB,LED);	//liga LED
		_delay_ms(200);		//atraso de 200 ms
		clr_bit(PORTB,LED);	//desliga LED
		_delay_ms(200);		//atraso de 200 ms
    }
}
//--------------------------------------------------------------------------------------