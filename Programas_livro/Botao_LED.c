//------------------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.								//	
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
//    LIGANDO E DESLIGANDO UM LED QUANDO UM BOT�O � PRESSIONADO							//
//===================================================================================== //
#define F_CPU 16000000UL	/*define a frequ�ncia do microcontrolador 16MHz (necess�rio
							para usar as rotinas de atraso)*/
#include <avr/io.h> 	    //defini��es do componente especificado
#include <util/delay.h>		//biblioteca para as rotinas de _delay_ms() e delay_us()

//Defini��es de macros - para o trabalho com os bits de uma vari�vel

#define set_bit(Y,bit_x)(Y|=(1<<bit_x))		//ativa o bit x da vari�vel Y (coloca em 1)
#define clr_bit(Y,bit_x)(Y&=~(1<<bit_x))	//limpa o bit x da vari�vel Y (coloca em 0) 
#define cpl_bit(Y,bit_x)(Y^=(1<<bit_x))		//troca o estado do bit x da vari�vel Y 
#define tst_bit(Y,bit_x)(Y&(1<<bit_x))  	//testa o bit x da vari�vel Y (retorna 0 ou 1)

#define LED   PD2   //LED � o substituto de PD2 na programa��o 
#define BOTAO PD7   //BOTAO � o substituto de PD7 na programa��o     	
//-------------------------------------------------------------------------------------
int main()
{
	DDRD = 0b00000100;	//configura o PORTD, PD2 sa�da, os demais pinos entradas
	PORTD= 0b11111111;	/*habilita o pull-up para o bot�o e apaga o LED (todas as 
						entradas com pull-ups habilitados)*/
	
	while(1)								//la�o infinito
	{
		if(!tst_bit(PIND,BOTAO))			//se o bot�o for pressionado executa o if
		{					
			while(!tst_bit(PIND,BOTAO));	//fica preso at� soltar o bot�o

			_delay_ms(10);					//atraso de 10 ms para eliminar o ru�do do bot�o

			if(tst_bit(PORTD,LED))			//se o LED estiver apagado, liga o LED
				clr_bit(PORTD,LED);			
			else							//se n�o apaga o LED
				set_bit(PORTD,LED);	

			//o comando cpl_bit(PORTD,LED) pode substituir este la�o if-else
		
		}//if do bot�o pressionado
	
	}//la�o infinito
}
//=====================================================================================
