//--------------------------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.										//	
//--------------------------------------------------------------------------------------------- //
//============================================================================================= //
//		Sensor Digital de temperatura TC72 com interface SPI									//
//		Resolu��o de amostragem para o LCD de 1 grau Cent�grado									//
//============================================================================================= //

#include "def_principais.h"
#include "LCD.h"

#define habilita_TC72()		set_bit(PORTB,PB2)	//n�vel l�gico do pino SS � contr�rio ao usual
#define desabilita_TC72()	clr_bit(PORTB,PB2)

void inic_SPI();
unsigned char SPI(unsigned char dado);

//-----------------------------------------------------------------------------------------
int main()
{
	unsigned char temp, tempH,tempL;
	char TEMP[3];

	DDRD = 0b11111100;//LCD
	PORTD = 0b00000011;
	
	inic_SPI();
	inic_LCD_4bits();
	
	cmd_LCD(0x80,0);
	escreve_LCD("TEMPERATURA");
	cmd_LCD(0xCE,0);
	cmd_LCD(0xDF,1);
	cmd_LCD('C',1);
	
	habilita_TC72();	//CE=1
	SPI(0x80);			//Prepara a escrita 
	SPI(0x00);			//Envia byte de controle, convers�o continua
	desabilita_TC72(); //CE=0
	
 	while (1)
	{
		
		_delay_ms(150);
		
		habilita_TC72();
		SPI(0x02);			//Prepara para a leitura 
		tempH=SPI(0x00);	//L� MSB
		tempL=SPI(0x00);	//L� LSB	
		desabilita_TC72();

		cmd_LCD(0xCA,0);
		
		if(tst_bit(tempH,7))
		{	
			cmd_LCD('-',1);
			tempH = 128 - tempH;//converte para temperatura positiva
		}		
		else
			cmd_LCD('+',1);
		
		//o valor bin�rio do MSB cont�m o valor da temperatura com resolu��o de 1 grau cent�grado
		temp = tempH & 0b01111111;//zera o bit de sinal
		ident_num(temp, TEMP);
		cmd_LCD(TEMP[2],1);
		cmd_LCD(TEMP[1],1);
		cmd_LCD(TEMP[0],1);
	}	
}
//-----------------------------------------------------------------------------------------
//Inicializa��o da SPI
//-----------------------------------------------------------------------------------------
void inic_SPI()
{
	DDRB = (DDRB & 0b11000011)|(0b00101100);//configura��o dos pinos de entrada e sa�da da SPI
	SPCR = (1<<SPE)|(1<<MSTR)|(SPR1)|(1<<CPHA);	//habilita SPI master, modo 0, CLK = f_osc/64 (250 kHz)
}											//dado ajustado na subida e amostragem na descida do sinal de clock
//-----------------------------------------------------------------------------------------
//Envia e recebe um byte pela SPI
//-----------------------------------------------------------------------------------------
unsigned char SPI(unsigned char dado)
{
	SPDR = dado;				//envia um byte
	while(!(SPSR & (1<<SPIF)));	//espera envio 
	return SPDR;				//retorna o byte recebido
}
//------------------------------------------------------------------------------------------