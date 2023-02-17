//---------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							 //	
//---------------------------------------------------------------------------------- //

//------------------------------------------------------------------------------------
void USART_Init( unsigned int baud )
{
	UBRR0 = 0;

	DDRD |= (1<<PD4);		//pino XCK como saída, habilita o modo mestre
	
	//Modo MSPI e SPI no modo 0
	UCSR0C = (1<<UMSEL01)|(1<<UMSEL00)|(0<<UCPHA0)|(0<<UCPOL0);	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);	//habilita a transmissão e recepção
	
	// Ajuste da taxa de transmissão
	// IMPORTANTE: A taxa de transmissão deve ser ajustada após a habilitação
	UBRR0 = baud;			//a variável baud deve conter o valor da taxa
}
//------------------------------------------------------------------------------------
unsigned char USART_TXRX(unsigned char dado)
{
	while(!( UCSR0A & (1<<UDRE0)) );	//espera a transmissão ser completada

	UDR0 = data;						//envia o dado

	while(!(UCSR0A & (1<<RXC0)) );		//espera o dado ser recebido

	return UDR0;						//retorna o dado recebido
}
//------------------------------------------------------------------------------------
