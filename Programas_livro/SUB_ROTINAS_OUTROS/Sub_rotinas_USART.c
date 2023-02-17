//--------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							//	
//---------------------------------------------------------------------------------	//

//=================================================================================	//
//		INICIALIZANDO A USART           											//  
//=================================================================================	//
#define FOSC 	1843200		//frequência de trabalho da CPU
#define BAUD 	9600
#define MYUBRR FOSC/16/BAUD-1
//----------------------------------------------------------------------------------
void main(void)
{
	...
	USART_Init(MYUBRR);
	...
}
//----------------------------------------------------------------------------------
void USART_Init(unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr>>8);	//ajusta a taxa de transmissão
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); 	//habilita o transmissor e o receptor
 	UCSR0C = (1<<USBS0)|(3<<UCSZ00); 	//ajusta o formato do frame: 8 bits de dados e 2 de parada
}
//==================================================================================


//=================================================================================	//
//		ENVIANDO FRAMES COM 5 A 8 BITS       										//  
//=================================================================================	//
void USART_Transmit(unsigned char data)
{
	while(!( UCSR0A & (1<<UDRE0)));		//espera a limpeza do registr. de transmissão
	UDR0 = data; 						//coloca o dado no registrador e o envia
}
//==================================================================================

//=================================================================================	//
//		ENVIANDO FRAMES COM 9 BITS         											//  
//=================================================================================	//
void USART_Transmit(unsigned int data)
{
	while(!(UCSR0A &(1<<UDRE0)));		//espera a limpeza do registr. de transmissão

	UCSR0B &= ~(1<<TXB80); 				//copia o nono bit para o TXB8

	if(data & 0x0100)
	UCSR0B |= (1<<TXB80);

	UDR0 = data; 						//coloca o dado no registrador e o envia 
}
//==================================================================================
 
//=================================================================================	//
//		RECEBENDO FRAMES COM 5 A 8 BITS       										//  
//=================================================================================	//
unsigned char USART_Receive(void)
{
while(!(UCSR0A & (1<<RXC0)));			//espera o dado ser recebido
return UDR0; 							//lê o dado recebido e retorna
}
//==================================================================================

//=================================================================================	//
//		RECEBENDO FRAMES COM 9 BITS      											//  
//=================================================================================	//
unsigned int USART_Receive(void)
{
	unsigned char status, resh, resl;	//espera o dado ser recebido
	while(!(UCSR0A &(1<<RXC0)));		//obtêm o status do nono bit, então, o dado do registr.
	status = UCSR0A;
	resh = UCSR0B;
	resl = UDR0;

	if(status & (1<<FE0)|(1<<DOR0)|(1<<UPE0)) //se ocorrer um erro retorna -1
	return -1;

	resh = (resh >> 1) & 0x01; 			//filtra o nono bit, então, retorna
	return ((resh << 8) | resl);
}
//==================================================================================

//=================================================================================	//
//  LIMPANDO O REGISTRADOR DE ENTRADA (quando ocorre um erro p. ex.)				//  
//=================================================================================	//
void USART_Flush(void)
{
	unsigned char dummy;
	while(UCSR0A & (1<<RXC0)) dummy = UDR0;
}
//==================================================================================



