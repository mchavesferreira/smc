//---------------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.							 //	
//---------------------------------------------------------------------------------- //

//------------------------------------------------------------------------------------
void USART_Init( unsigned int baud )
{
	UBRR0 = 0;

	DDRD |= (1<<PD4);		//pino XCK como sa�da, habilita o modo mestre
	
	//Modo MSPI e SPI no modo 0
	UCSR0C = (1<<UMSEL01)|(1<<UMSEL00)|(0<<UCPHA0)|(0<<UCPOL0);	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);	//habilita a transmiss�o e recep��o
	
	// Ajuste da taxa de transmiss�o
	// IMPORTANTE: A taxa de transmiss�o deve ser ajustada ap�s a habilita��o
	UBRR0 = baud;			//a vari�vel baud deve conter o valor da taxa
}
//------------------------------------------------------------------------------------
unsigned char USART_TXRX(unsigned char dado)
{
	while(!( UCSR0A & (1<<UDRE0)) );	//espera a transmiss�o ser completada

	UDR0 = data;						//envia o dado

	while(!(UCSR0A & (1<<RXC0)) );		//espera o dado ser recebido

	return UDR0;						//retorna o dado recebido
}
//------------------------------------------------------------------------------------
