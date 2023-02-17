//-------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								 //	
//-------------------------------------------------------------------------------------- //

#include "SD_MMC.h"

//-----------------------------------------------------------------------------------------
//Inicialização da SPI
//-----------------------------------------------------------------------------------------
void inic_SPI()
{
	DDRB = (DDRB & 0b11000011)|(0b00101100);//configuração dos pinos de entrada e saída da SPI
	
	habilita_MMC();	//CS = 0

	SPCR = (1<<SPE)|(1<<MSTR)|(SPR1);	//habilita SPI master, modo 0, CLK = f_osc/64 (250 kHz)
										//100 kHz  <= f_osc <= 400 kHz
}
//-----------------------------------------------------------------------------------------
//Envia e recebe um byte pela SPI
//-----------------------------------------------------------------------------------------
unsigned char SPI(uchar dado)
{
	SPDR = dado;				//envia um byte
	while(!(SPSR & (1<<SPIF)));	//espera envio 

	return SPDR;				//retorna o byte recebido
}
//-----------------------------------------------------------------------------------------
//Envia um comando para o MMC - index + argumento + CRC (total de 6 bytes)
//-----------------------------------------------------------------------------------------
void comando_MMC(uchar index, uint ArgH, uint ArgL, uchar CRC)
{	
	//INDEX - 6 bits
	SPI(index);//sempre bit 7 = 0 e bit 6 = 1, b5:b0 (index) 
	
	//ARGUMENTO - 32 bits
	SPI((uchar)(ArgH >> 8));
	SPI((uchar)ArgH);
	SPI((uchar)(ArgL >> 8));
	SPI((uchar)ArgL);
	
	//CRC
	SPI(CRC);//bit 0 sempre 1
}
//-------------------------------------------------------------------------------------------
//Lê continuamente o MMC até obter a resposta desejada ou estourar o tempo permitido
//-------------------------------------------------------------------------------------------
unsigned char resposta_MMC(uchar resposta) 
{											
	unsigned int cont = 0xFFF;//contador para espera de um máximo tempo da resposta
	
	do
	{
		if(SPI(0xFF)==resposta)
			return 0;	//resposta normal laço acabou antes do estouro de contagem
		cont--;

	}while(cont!=0);	
	
	return 1;			//falha na resposta 
}
//-------------------------------------------------------------------------------------------
//Inicializa o MMC para trabalhar no modo SPI
//-------------------------------------------------------------------------------------------
unsigned char inic_MMC() 
{ 
	unsigned char i;
	
	desabilita_MMC();
	
	for(i=0; i<10; i++) SPI(0xFF); //80 pulsos de clock
		
	habilita_MMC();

	comando_MMC(0x40,0,0,0x95);//CMD0 (GO TO IDLE STATE - RESET) - unico vez que envia o checksum (0x95)
	
	if (resposta_MMC(0x01)) { desabilita_MMC(); return 1;}	//retorna 1 para indicar que houve erro (não entrou no modo Idle)
		
	desabilita_MMC();
	SPI(0xFF);			//alguns clocks após o modo Idle
	habilita_MMC();
	
	i=0xFF;
	do //envia o CMD1 até resposta ser zero (não estar mais no modo Idle), não haver erro, e estar dentro do nr.  máximo de repetições
	{
		i--;
		comando_MMC(0x41,0,0,0xFF);//CMD1 (SEND_OP_COND) - verifica quando saiu do modo Idle
	} while ((resposta_MMC(0x00)!=0) && (i!=0));
	
	if(i==0){ desabilita_MMC(); return 2;}		//retorna 2 para indicar que houve erro não saiu do modo Idle)
	
	desabilita_MMC();
	SPI(0xFF);//alguns clocks após modo Idle

	return 0;		//retorna 0 para indicar sucesso na operação
}
//------------------------------------------------------------------------------------------
//Escreve a partir do endereço especificado (setor), sempre em blocos de 512 bytes
//Os endereços podem ser  0, 512, 1024, 1536 ... 
//Calculados como :
//   (Nr_Setor - 1) x 512. Por exemplo: Nr_Setor = 1000, resulta no endereço 0x7CE00
//------------------------------------------------------------------------------------------
unsigned char escreve_MMC(uchar *buffer, uint enderecoH, uint enderecoL)
{ 
	unsigned int i;

	habilita_MMC();
	
	comando_MMC(0x58,enderecoH,enderecoL,0xFF);//CMD24 (WRITE_SINGLE_BLOCK) - escreve um único bloco de 512 bytes
	
	if (resposta_MMC(0x00))	{ desabilita_MMC(); return 1;} //retorna 1 para indicar erro do CMD24
			
	SPI(0xFE);//indica o inicio do bloco de dados
	
	for(i=0;i<512;i++)//transfere os 512 bytes do buffer para o MMC
	{
		SPI(*buffer);
		buffer++;
	}
	
	//no final envia dois bytes sem utilidade (dummy checksum)
	SPI(0xFF);
	SPI(0xFF);

	if ((SPI(0xFF) & 0x0F) != 0x05)	{desabilita_MMC(); 	return 2;}//retorna 2 para indicar erro na escrita 
	
	//espera final de escrita 
	i=0xFFFF;
	do 
	{	i--;
	} while ((SPI(0xFF)== 0x00) && i);
	
	if(i==0){ desabilita_MMC(); return 3;}	//retorna 3 para indicar erro no final da escrita		
	
	desabilita_MMC();	//desabilita o SD card
	SPI(0xFF);
	
	return 0;	//retorna 0 para indicar sucesso na operação
}
//-------------------------------------------------------------------------------------------
//Lê a partir do endereço especificado (setor), sempre em blocos de 512 bytes (como na escrita)
//-------------------------------------------------------------------------------------------
unsigned char le_MMC(uchar *buffer,uint enderecoH, uint enderecoL)
{ 
	unsigned int i;
		
	habilita_MMC();
	
	comando_MMC(0x51,enderecoH,enderecoL,0xFF);//CMD17 (READ_SINGLE_BLOCK) - leitura de um único bloco de 512 bytes
	
	if (resposta_MMC(0x00))	{desabilita_MMC();	return 1;}	//retorna 1 para indicar erro na leitura

	if (resposta_MMC(0xFE))	{desabilita_MMC();	return 2;}	//retorna 2 para indicar erro na leitura
	
	for(i=0; i < 512; i++) //leitura dos 512 bytes para o vetor de memória desejado (buffer)
	{
		*buffer=SPI(0xFF);  //envia 0xFF para receber o dado
		buffer++;
	}
	
	// no final envia dois bytes, retornam o CRC/checksum byte (sem importancia no programa)
	SPI(0xFF); 
	SPI(0xFF);
	
	desabilita_MMC();
	SPI(0xFF);
	
	return 0;	//retorna 0 para indicar sucesso na operação
}
//-------------------------------------------------------------------------------------------
