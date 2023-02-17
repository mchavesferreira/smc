//--------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							//	
//---------------------------------------------------------------------------------	//
/*=================================================================================	
	Sub-rotina para o trabalho com um teclado com 16 teclas (4 colunas e 4 linhas)
	organizados como: 
			 C1 C2 C3 C4 
			  x  x  x  x	L1 
			  x  x  x  x	L2
			  x  x  x  x	L3
			  x  x  x  x	L4								
	onde se deve empregar um unico PORT conectado da seguinte maneira:
	PORT =  L4 L3 L2 L1 C4 C3 C2 C1 (sendo o LSB o C1 e o MSB o L4) 																
=================================================================================	*/
#include "teclado.h"

/*matriz com as informações para decodificação do teclado, 
organizada de acordo com a configuração do teclado, o usuário 
pode definir valores números ou caracteres ASCII, como neste exemplo*/

const unsigned char teclado[4][4] PROGMEM = {{'1', '2', '3', 'F'},
						     				 {'4', '5', '6', 'E'},
						     				 {'7', '8', '9', 'D'},
						     				 {'A', '0', 'B', 'C'}};
										  
//-----------------------------------------------------------------------------------
unsigned char ler_teclado()
{
	unsigned char n, j, tecla=0xFF, linha;
	
	for(n=0;n<4;n++)
	{
		clr_bit(COLUNA,n);			//apaga o bit da coluna (varredura)
		_delay_ms(10);				//atraso para uma varredura mais lenta, também elimina o ruído da tecla
		linha = LINHA >> 4;			//lê o valor das linhas
	   
		for(j=0;j<4;j++)			//testa as linhas
		{
    		if(!tst_bit(linha,j))	//se foi pressionada alguma tecla, decodifica e retorna o valor
			{	
				tecla = pgm_read_byte(&teclado[j][n]);	//decodifica o valor para a tecla
				//while(!tst_bit(LINHA>>4,j));			//para esperar soltar a tecla, caso desejado, descomentar esta linha
			}			
		}
		set_bit(COLUNA,n);			//ativa o bit zerado anteriormente
	}
	return tecla;					//retorna o valor 0xFF se nenhuma tecla foi pressionada
}
//-----------------------------------------------------------------------------------