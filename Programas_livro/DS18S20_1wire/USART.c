//----------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //
//=============================================================================	//
//		Fun��es para trabalhalho com a USART									//
//=============================================================================	//

#include "USART.h"

//---------------------------------------------------------------------------
void USART_Inic(unsigned int ubrr0)
{
	UBRR0H = (unsigned char)(ubrr0>>8);	//Ajusta a taxa de transmiss�o
	UBRR0L = (unsigned char)ubrr0;

	UCSR0A = 0;//desabilitar velocidade dupla (no Arduino � habilitado por padr�o)
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //Habilita a transmiss�o e a recep��o
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);/*modo ass�ncrono, 8 bits de dados, 1 bit de parada, sem paridade*/
}
//---------------------------------------------------------------------------
void USART_Transmite(unsigned char dado)
{
	while (!( UCSR0A & (1<<UDRE0)) );	//espera o dado ser enviado
	UDR0 = dado; 					//envia o dado
}
//---------------------------------------------------------------------------
unsigned char USART_Recebe()
{
	while (!(UCSR0A & (1<<RXC0)));	//espera o dado ser recebido
	return UDR0; 				//retorna o dado recebido
}
//---------------------------------------------------------------------------
void escreve_USART(char *c)		//escreve String (RAM)
{
   for (; *c!=0;c++) USART_Transmite(*c);
}
//---------------------------------------------------------------------------
void escreve_USART_Flash(const char *c)	//escreve String (Flash)
{
   for (;pgm_read_byte(&(*c))!=0;c++) USART_Transmite(pgm_read_byte(&(*c)));
}
//---------------------------------------------------------------------------	
//Convers�o de um n�mero em seus digitos individuais
//---------------------------------------------------------------------------
void ident_num(unsigned int valor, unsigned char *disp)
{   
 	unsigned char n;

	for(n=0; n<tam_vetor; n++)
		disp[n] = 0 + conv_ascii;	//limpa vetor para armazenagem dos digitos 

	do
	{
       *disp = (valor%10) + conv_ascii;	//pega o resto da divisao por 10 
	   valor /=10;		//pega o inteiro da divis�o por 10
	   disp++;

	}while (valor!=0);
}
//------------------------------------------------------------------------------
