//------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								//	
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
//    LIGANDO E DESLIGANDO UM LED QUANDO UM BOTÃO É PRESSIONADO							//
//===================================================================================== //
#define F_CPU 16000000UL	/*define a frequência do microcontrolador 16MHz (necessário
							para usar as rotinas de atraso)*/
#include <avr/io.h> 	    //definições do componente especificado
#include <util/delay.h>		//biblioteca para as rotinas de _delay_ms() e delay_us()

//Definições de macros - para o trabalho com os bits de uma variável

#define set_bit(Y,bit_x)(Y|=(1<<bit_x))		//ativa o bit x da variável Y (coloca em 1)
#define clr_bit(Y,bit_x)(Y&=~(1<<bit_x))	//limpa o bit x da variável Y (coloca em 0) 
#define cpl_bit(Y,bit_x)(Y^=(1<<bit_x))		//troca o estado do bit x da variável Y 
#define tst_bit(Y,bit_x)(Y&(1<<bit_x))  	//testa o bit x da variável Y (retorna 0 ou 1)

#define LED   PD2   //LED é o substituto de PD2 na programação 
#define BOTAO PD7   //BOTAO é o substituto de PD7 na programação     	
//-------------------------------------------------------------------------------------
int main()
{
	DDRD = 0b00000100;	//configura o PORTD, PD2 saída, os demais pinos entradas
	PORTD= 0b11111111;	/*habilita o pull-up para o botão e apaga o LED (todas as 
						entradas com pull-ups habilitados)*/
	
	while(1)								//laço infinito
	{
		if(!tst_bit(PIND,BOTAO))			//se o botão for pressionado executa o if
		{					
			while(!tst_bit(PIND,BOTAO));	//fica preso até soltar o botão

			_delay_ms(10);					//atraso de 10 ms para eliminar o ruído do botão

			if(tst_bit(PORTD,LED))			//se o LED estiver apagado, liga o LED
				clr_bit(PORTD,LED);			
			else							//se não apaga o LED
				set_bit(PORTD,LED);	

			//o comando cpl_bit(PORTD,LED) pode substituir este laço if-else
		
		}//if do botão pressionado
	
	}//laço infinito
}
//=====================================================================================
