//------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.					//	
//------------------------------------------------------------------------- //
//========================================================================	//
//			COMUNICAÇÃO SERIAL ENTRE O ARDUINO E UM COMPUTADOR				//
//=========================================================================	//
#include "def_principais.h"
#include "USART.h"

const char primeira_msg[] PROGMEM = "Transmitindo primeira mensagem para o computador! Digite agora - Para sair <*>\n\0";
const char segunda_msg[]  PROGMEM = "\nTransmissao Encerrada: Bye, Bye!\0";

//-------------------------------------------------------------------------
int main()
{
	unsigned char dado_recebido;
	
	USART_Inic(MYUBRR);
	
	escreve_USART_Flash(primeira_msg);
	
	do
	{
		dado_recebido= USART_Recebe();	//recebe caractere
		USART_Transmite('-');
		USART_Transmite('>');
		USART_Transmite(dado_recebido);	//envia o caractere recebido
	}while(dado_recebido!='*');
		
	escreve_USART_Flash(segunda_msg);
	
	while(1);//laço infinito
}
//---------------------------------------------------------------------------

