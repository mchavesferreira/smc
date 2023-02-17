//------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								//	
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
//		ACIONANDO UM DISPLAY DE CRISTAL LIQUIDO DE 16x2									//
//		Uso da função ident_num(...)													//
//=====================================================================================	//

#include "def_principais.h"	//inclusão do arquivo com as principais definições 
#include "LCD.h"

//-------------------------------------------------------------------------------------
int main()
{	
	unsigned char digitos[tam_vetor];	//declaração da variável para armazenagem dos digitos
    unsigned char cont;	
	
	DDRD = 0xFF;						//PORTD como saída
	DDRB = 0xFF;

	inic_LCD_4bits();					//inicializa o LCD

	while(1)
	{
		for(cont=0; cont<101; cont++)
		{
			ident_num(cont,digitos);
			cmd_LCD(0x8D,0);			//desloca o cursor para que os 3 digitos fiquem a direita do LCD
			cmd_LCD(digitos[2],1);
			cmd_LCD(digitos[1],1);
			cmd_LCD(digitos[0],1);
			_delay_ms(200);				//tempo para a troca de valor
		}
	}

}
//======================================================================================