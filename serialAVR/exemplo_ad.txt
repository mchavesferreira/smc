//------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								//
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
//		ACIONANDO UM DISPLAY DE CRISTAL LIQUIDO DE 16x2									//
//																						//
//				Interface de dados de 4 bits											//
//=====================================================================================	//

#include "def_principais.h"			//inclusão do arquivo com as principais definições
#include "LCD.h"

void configura_AD(){
// configura canal 0 
ADMUX = (1<<REFS0) | (1<<MUX2) | (1<<MUX0);			//Tensão interna de ref (+5V), canal ADC5
ADCSRA = (1<<ADEN) | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//habilita o AD e define um prescaler de 128 (clk_AD = F_CPU/128), 125 kHz
}
signed int le_temp();


//--------------------------------------------------------------------------------------
int main()
{
	DDRD = 0xFF;					//PORTD como saída
	DDRB = 0xFF;
	unsigned char digitos[tam_vetor];	//declaração da variável para armazenagem dos digitos
	unsigned int valorbinario;
	long valormv;   // variavel para conversao em mV
	

	inic_LCD_4bits();
	configura_AD();
	
	//inicializa o LCD
	cmd_LCD(0x80,0);
	escreve_LCD("IFSP CATANDUVA");	//string armazenada na RAM

	while(1)  {
		
		
		valorbinario=le_temp();  // le o valor binario de 10 bits
		
		
		
		// imprime valor binario
		ident_num(valorbinario,digitos);
		cmd_LCD(0xCC,0);			//desloca o cursor
		cmd_LCD(digitos[3],1);
		cmd_LCD(digitos[2],1);
		cmd_LCD(digitos[1],1);
		cmd_LCD(digitos[0],1);

		//  conversao em regra de 3 em mV
		valormv=(long)valorbinario*5000;
		valormv=valormv/1023;
		// imprime valor mV
		ident_num(valormv,digitos);
		cmd_LCD(0xC0,0);			//desloca o cursor
		cmd_LCD(digitos[3],1);
		cmd_LCD(digitos[2],1);
		cmd_LCD(digitos[1],1);
		cmd_LCD(digitos[0],1);
		escreve_LCD(" mV");
		
		_delay_ms(100);
		
	}
	//laço infinito
}
//======================================================================================

//--------------------------------------------------------------------------------
signed int le_temp()
{
	set_bit(ADCSRA, ADSC);								//inicia a conversão
	while(tst_bit(ADCSRA,ADSC));						//espera a conversão ser finalizada
	
	return (ADC);
}