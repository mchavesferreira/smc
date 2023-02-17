//------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.					//	
//-------------------------------------------------------------------------	//


//=========================================================================	//
//Fun��es para inicializar a SPI no modo Mestre e transmitir um dado   		//    
//========================================================================	//
void SPI_Mestre_Inic()
{
	DDRB = (1<<PB5)|(1<<PB3);			//ajusta MOSI e SCK como sa�da, demais pinos como entrada
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);//habilita SPI, Mestre, taxa de clock ckl/16 
}
//--------------------------------------------------------------------------
void SPI_Mestre_Transmit(char dado)
{
	SPDR = dado; 						//inicia a transmiss�o
	while(!(SPSR & (1<<SPIF)));			//espera a transmiss�o ser completada
}
//==========================================================================


//=========================================================================	//
//    Fun��es para inicializar a SPI no modo Escravo e receber um dado		//
//======================================================================== 	//
void SPI_Escravo_Inic( )
{
	DDRB = (1<<PB4);					//ajusta o pino MISO como sa�da, demais pinos como entrada 
	SPCR = (1<<SPE);					//habilita SPI 
}
//---------------------------------------------------------------------------
char SPI_Escravo_Recebe( )
{
	while(!(SPSR & (1<<SPIF)));			//espera a recep��o estar completa
	return SPDR;		 				//retorna o registrador de dados
}
//===========================================================================
