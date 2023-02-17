//-------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								 //	
//-------------------------------------------------------------------------------------- //
//-------------------------------------------------------------------------------------- //
//		DS1307 - RTC com LCD 16 x 2 utilizando I2C										 //
//-------------------------------------------------------------------------------------- //

#include "def_principais.h"
#include "LCD.h"
#include "DS1307.h"

extern unsigned char flag_pontos, cont;

int main()
{
	DDRB = 0xFF;		//LCD
	DDRD = 0x00;		//botoes
	PORTD = 0x03;		//pull-ups habilitados
	
	//TWI
	DDRC = (1<<4)|(1<<5);

	inic_TWI();
	sei();
	
	inic_LCD_4bits();	
	
	escreve_DS1307(0x00, 0x00);	
	escreve_DS1307(0x07,0b00010000);//habilita 1Hz no pino SOUT do DS1307
	
	//-------------------------------------------------------------------------------------
	while(1)
	{
		ler_convert_tudo(0x00);		//gasta um bom tempo para ler o RTC! Mais lento na simulação quando entra aqui
		mostra_tempo();
    	mostra_pontos(flag_pontos);	//flag indica se deve ligar os pontos e tracos
		_delay_ms(200);
		
		if(!tst_bit(PIND,SELECAO))
   		{   
       		flag_pontos = 0;		//avisa para nao imprimir mais os pontos e tracos
       		cont++;					//conta o nr. de vezes que o botao SELEÇAO foi pressionado
       
       		if (cont>7)
       		{ 	cont = 0;
         		flag_pontos = 1;	//habilita novamente os pontos e tracos
        	}
         	alerta_display(cont);	//coloca a seta no local para ajuste do tempo
       		while(!tst_bit(PIND,SELECAO));//aguarda soltar SETAR - nao atualiza display
   		}
		//----------------------------------------------------------------------------
		if (flag_pontos==0)
   		{   
     		if(!tst_bit(PIND,AJUSTE))
            	ajusta_tempo2(cont);//ajusta RTC ou ajusta alarme
   		}//if !flag
		//----------------------------------------------------------------------------			

	}//while forever
	//--------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------