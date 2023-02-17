//------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.					//	
//-------------------------------------------------------------------------	//
//-------------------------------------------------------------------------	//
//	Programa para a escrita e leitura de um SD/MCC							//
//	Escrita e leitura em blocos de 512 bytes								//
//------------------------------------------------------------------------	//

#include "def_principais.h"
#include "SD_MMC.h"

#define liga_led()		set_bit(PORTD,5)	//ativo em 1
#define desliga_led()	clr_bit(PORTD,5)

unsigned char dados[512];//aloca 512 bytes da RAM para poder escrever em blocos, como necessário para o trabalho com o SD card

int main(void)
{
    unsigned int i;
	
	DDRD = 1<<5;	//PD5 possui o LED sinalizador de erro
	desliga_led();	//Só liga o LED se houver erro, pisca led ao final se o funcionamento foi correto
	
	
	
	inic_SPI();
	
	if(inic_MMC()!=0)	//inicializa MMC - após inicialização a velocidade da SPI pode ser aumentada
		liga_led();
	
	//teste para a escrita em 3 setores da memória
	//----------------------------------------------------------------------
	//setor 1
	for(i=0;i<512;i++)	dados[i]=0xAA;

	if(escreve_MMC(dados,0,0)!=0)	//escreve 0xAA nos 512 bytes do setor 1
		liga_led();
	
	//----------------------------------------------------------------------		
	//setor 2
	for(i=0;i<512;i++)	dados[i]=0xBB;

	if(escreve_MMC(dados,0,512)!=0)	//escreve 0xBB nos 512 bytes do setor 2
		liga_led();
		
	//----------------------------------------------------------------------
	//setor 1000 = 0x7CE00
	for(i=0;i<512;i++)	dados[i]=(uchar)i;	
	
	if(escreve_MMC(dados,0x0007,0xCE00)!=0)	//escreve 0-511 nos 512 bytes do setor 1000
		liga_led();
			
	//----------------------------------------------------------------------
	//comparação da escrita apenas para o setor 1000 			
	if(le_MMC(dados,0x0007,0xCE00)!=0)		//lê as primeiras 512 posições
		liga_led(); 
	//while(1);
	//----------------------------------------------------------------------
	//compara os dados escritos com os lidos
	for(i=0;i<1;i++)
	{
		if(dados[0]!=(uchar)i)
			liga_led();	//liga led se o dado escrito for diferente do lido
	}
	
	//se o led não foi ligado fica piscando indicando sucesso na operação de escrita e leitura
	if(!tst_bit(PORTD,5))
	{
		while(1)
		{
			liga_led();
			_delay_ms(300);
			desliga_led();
			_delay_ms(300);
		}
	}	
	//----------------------------------------------------------------------	
	while(1);
}
