//----------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //
//=============================================================================	//
//			CONTROLE DO M�DULO DE RF TX											//
//=============================================================================	//
#include "def_principais.h"
#include "USART.h"

#define endereco 0x05	//define o endereco de acesso para o modulo RF RX 
//----------------------------------------------------------------------------
int main()
{
	unsigned char i, dado;
	
	USART_Inic(MYUBRR);//UCSR0C = (1<<UPM01)|(1<<UCSZ01)|(1<<UCSZ00);
	
	while(1)//envia continuamente 
	{
		for(i=0; i<16;i++)//envia 16 dados diferentes (s�o 4 MSB)
		{
			dado  =  (i << 4 ) | endereco; //4 LSB s�o o endere�o do m�dulo RF RX

			USART_Transmite(dado);//envia 3 vezes para aumentar a chance do dado ser recebido,
			USART_Transmite(dado);//pois n�o se sabe se o dado foi recebido
			USART_Transmite(dado);
			
			_delay_ms(500);//envia um novo dado a cada 0,5 s
		}		
	}
}
//----------------------------------------------------------------------------
