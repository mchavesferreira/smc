//------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								//	
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
//       			CRIANDO CARACTERES PARA O LCD 16x2	   								//
//																						//
//          			Via de dados de 4 bits											//
//=====================================================================================	//

#include "def_principais.h"			//inclusão do arquivo com as principais definições 
#include "LCD.h"

//informação para criar caracteres novos armazenada na memória flash
const unsigned char carac1[] PROGMEM = {0b01110,//Ç
                         				0b10001,
                         				0b10000,
                         				0b10000,
                         				0b10101,
                         				0b01110,
                         				0b10000};
										 
const unsigned char carac2[] PROGMEM = {0b00100,//Delta
                         				0b00100,
                         				0b01010,
                         				0b01010,
                         				0b10001,
                         				0b11111,
                         				0b00000};

//--------------------------------------------------------------------------------------
int main()
{	
    unsigned char k;
	
	DDRD = 0xFF;					//PORTD como saída
	DDRB = 0xFF;					//PORTB como saída

	inic_LCD_4bits();				//inicializa o LCD
	
   	cmd_LCD(0x40,0);				//endereço base para gravar novo segmento 0x40
    for(k=0;k<7;k++)
   		cmd_LCD(pgm_read_byte(&carac1[k]),1);	//grava 8 bytes na DDRAM começando no end. 0x40
	cmd_LCD(0x00,1);				//apaga última posição do end. da CGRAM para evitar algum dado espúrio
	   
   	cmd_LCD(0x48,0);				//endereço base para gravar novo segmento  0x48
    for(k=0;k<7;k++)
      	cmd_LCD(pgm_read_byte(&carac2[k]),1);	//grava 8 bytes na DDRAM começando no end. 0x48 
   	cmd_LCD(0x00,1);				//apaga última posição do end. da CGRAM para evitar algum dado espúrio
	   
	cmd_LCD(0x80,0);				//endereça a posição para escrita dos caracteres
   	cmd_LCD(0x00,1);				//apresenta primeiro caractere 0x00
   	cmd_LCD(0x01,1);				//apresenta segundo  caractere 0x01 
	   
	for(;;);	//laço infinito
}
//=====================================================================================	