//----------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //
//=============================================================================	//
//			CONTROLE DO MÓDULO DE RF RX											//
//=============================================================================	//

#include "def_principais.h"
#include "USART.h"

#define endereco 0x05	//define o endereço de acesso
//-----------------------------------------------------------------------------
void USART_Inic(unsigned int ubbr0);
unsigned char USART_Recebe();
//-----------------------------------------------------------------------------
int main()
{
	unsigned char dado;
	
	DDRB = 0xFF;		//PORTB para sinalizar o dado recebido
	
	USART_Inic(MYUBRR);
	
	while(1) 
	{
		dado = USART_Recebe();
		
		if(!tst_bit(UCSR0A,UPE0))	//se não houver erro de paridade executa a ação correspondente
		{
			if((dado & 0x0F) == endereco)
			{
				dado = dado>>4;		//elimina o endereço do dado
			
				switch(dado)		//16 possibilidades (4 bits de informação)
				{
					case 0:		PORTB = dado; break;//cada 'case' terá a ação desejada
					case 1:		PORTB = dado; break;
					case 2:		PORTB = dado; break;
					case 3:		PORTB = dado; break;
					case 4:		PORTB = dado; break;
					case 5:		PORTB = dado; break;
					case 6:		PORTB = dado; break;
					case 7:		PORTB = dado; break;
					case 8:		PORTB = dado; break;
					case 9:		PORTB = dado; break;
					case 10:	PORTB = dado; break;
					case 11:	PORTB = dado; break;
					case 12:	PORTB = dado; break;
					case 13:	PORTB = dado; break;
					case 14:	PORTB = dado; break;
					default:	PORTB = dado; 
				}
			}
			
		}//if de paridade	
			
	}// while 1 
}	
//-----------------------------------------------------------------------------
