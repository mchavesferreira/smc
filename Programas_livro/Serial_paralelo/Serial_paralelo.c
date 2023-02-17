//--------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							//	
//---------------------------------------------------------------------------------	//
//================================================================================	//
// 		Enviando 3 bytes para o 4094												//
//================================================================================	//

#include "def_principais.h"		

#define D 		PB0				//pino de dados para o 4094
#define CLK 	PB1				//pino clock para o 4094
#define STB 	PB2				//pino de strobe para o 4094

#define pulso_CLK()	set_bit(PORTB,CLK);	_delay_us(10); clr_bit(PORTB,CLK)
#define pulso_STB()	set_bit(PORTB,STB);	_delay_us(10); clr_bit(PORTB,STB)

//----------------------------------------------------------------------------------
// Sub-rotina que envia 1 byte para o 4094 - serial/paralelo
//----------------------------------------------------------------------------------
void serial_paral(unsigned char c)
{
   unsigned char i=8;			//envia primeiro o MSB
   
   do 
   {	i--;
	   
		if(tst_bit(c,i))		//se o bit for 1, ativa o pino de DADOS
			set_bit(PORTB,D);
		else      				//se não, o zera
			clr_bit(PORTB,D);

		pulso_CLK();
	   
   } while (i!=0);
 }
//----------------------------------------------------------------------------------
int main(void)
{
	unsigned char j;
	unsigned char Dados[3]= {0x58, 0xF1, 0xAA};
	 
	DDRB  = 0b00000111;				//pinos PB0:2 como saídas
	PORTB = 0b11111000;				//zera saídas
	 
	for(j=0; j<3;j++)    
			serial_paral(Dados[j]);	//envia os 3 dados para os 4094 (primeiro o 0x58)
			
	pulso_STB();	/*depois de enviar os 3 dados dá o pulso de Strobe, neste instante os 
					dados passam para as saída*/  
    while(1)
    {}				//laço infinito
}
//==================================================================================
