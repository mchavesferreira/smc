//------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.					//
//------------------------------------------------------------------------- //
//========================================================================	//
//			COMUNICAÇÃO SERIAL ENTRE O ARDUINO E UM COMPUTADOR	
// exemplo incrementa variavel e envia para porta SERIAL			//
//=========================================================================	//
#include "def_principais.h"
#include "USART.h"

//-------------------------------------------------------------------------
int main()
{   unsigned char digitos[tam_vetor];	//declaração da variável para armazenagem dos digitos
	unsigned int valor=0;
	USART_Inic(MYUBRR);
	
	escreve_USART("teste ");   // envia texto para serial
		USART_Transmite(13);   // codigo ascii pula linha
		_delay_ms(200);  // aguarda intervalo de tempo
	
	while(1)
	{
		valor++;
		ident_num(valor,digitos);  // separa casas do numero 
	    USART_Transmite(digitos[3]);
		USART_Transmite(digitos[2]);
		USART_Transmite(digitos[1]);
	    USART_Transmite(digitos[0]);
		USART_Transmite(13);   // codigo ascii pula linha
		_delay_ms(200);  // aguarda intervalo de tempo
	}
}
