//----------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.						//	
//----------------------------------------------------------------------------- //
//=============================================================================	//
//      GRAVANDO E LENDO A EEPROM												//
//=============================================================================	//
#include <avr/io.h>
#include <avr/eeprom.h> 

/*inicialização dos valores para a EEPROM começando no endereço 0x00
(default), não consome nenhum byte da memória flash – deve ser empregado quando necessário.
Gera um arquivo *.eep que é utilizado no programa de gravação do microcontrolador*/

unsigned char EEMEM uc_valor = 0x33;
unsigned char EEMEM uc_vetor[4] = {0x33, 0x22, 0x11, 0x55};
unsigned char EEMEM uc_string[13] = {"Teste EEPROM\0"};
unsigned int  EEMEM ui_valor = 0x5AB9;

unsigned char RAM_byte;
unsigned char RAM_bytes[4];
unsigned char RAM_string[13];
unsigned int  RAM_word;

//-----------------------------------------------------------------------------
int main()
{
  	unsigned char ucDado_escrita = 0x13;
	unsigned char ucDdado_leitura;
	unsigned int  uiEndereco = 0x3FF; 			//endereço 0x3FF (1024° posição da memória) valores entre 0 e 1023
	  
	_EEPUT(uiEndereco,ucDado_escrita);			//gravando 0x13 no endereco 0x3FF da EEPROM
	_EEGET(ucDdado_leitura, uiEndereco);		//lendo o conteúdo do endereco 0x3FF para a variável ucDado_leitura
	
	//lendo valores da EEPROM para a RAM
	RAM_byte = eeprom_read_byte(&uc_valor);		//lendo a variavel uc_valor para a variavel RAM_byte
	RAM_word = eeprom_read_word(&ui_valor);		//lendo a variavel ui_valor para a variavel RAM_word
	eeprom_read_block(RAM_string,uc_string,13);	//lendo a variavel uc_string com 13 bytes para a variavel RAM_string
	eeprom_read_block(RAM_bytes,uc_vetor,4);	//lendo a variavel uc_vetor com 4 bytes para a variavel RAM_bytes
	
	//escrevendo um dado na EEPROM 
	eeprom_write_byte(&uc_valor,0xEE);			//escreve o valor 0xEE na variavel uc_valor da EEPROM
 	
	 while(1){}									//código principal
}
//=============================================================================
