//------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.					//	
//------------------------------------------------------------------------- //
//=========================================================================	//
//           ROTINAS PARA A COMUNICAÇÃO 1 WIRE 								//
//=========================================================================	//

#include "_1wire.h"
//--------------------------------------------------------------------------
unsigned char reset_1w()	//inicializa os dispositivos no barramento
{
	DQ_saida();				//DQ como saída
	clr_DQ();				//DQ em nível zero por 480us
	_delay_us(480);

	DQ_entrada();			//DQ como entrada, o resistor de pull-up mantém DQ em nível alto
	_delay_us(60);

	if(tst_DQ())			//se nao detectou a presença já retorna 1
		return 1;
		
	_delay_us(420);			//o pulso de presença pode ter 240 us
	return 0;				//retorna 0 para indicar sucesso
}
//---------------------------------------------------------------------------
void alimenta_1w()			//força o barramento em nível alto. 
{							//utilizado com dispositivos alimentados no modo parasita
	DQ_saida();
	set_DQ();
	_delay_ms(750);
	DQ_entrada();			//pull-up externo
}
//---------------------------------------------------------------------------
unsigned char le_bit_1w() 	//lê um bit do barramento 
{
	unsigned char dado;
	
	DQ_saida();
	clr_DQ();	
	_delay_us(2);
	DQ_entrada();
	_delay_us (15);			//aguarda o dispositivo colocar o dado na saída
	dado = tst_DQ();
	_delay_us(50);
	return (dado);			//retorna o dado
}
//---------------------------------------------------------------------------
void escreve_bit_1w(unsigned char bit_1w)//escreve um bit no barramento 
{
	DQ_saida();
	clr_DQ();
	_delay_us(2);
		
	if(bit_1w) 
		set_DQ(); 
		
	_delay_us(120);
	DQ_entrada();
}
//---------------------------------------------------------------------------
unsigned char le_byte_1w()	//lê um byte do barramento
{
	unsigned char i, dado = 0;

	for (i=0;i<8;i++)		//lê oito bits iniciando pelo bit menos significativo
	{
		if (le_bit_1w()) 
			set_bit(dado,i);
	}
	return (dado);
}
//----------------------------------------------------------------------------
void escreve_byte_1w(unsigned char dado)	//escreve um byte no barramento 
{
	unsigned char i;

	for (i=0; i<8; i++)		//envia o byte iniciando do bit menos significativo
		escreve_bit_1w(tst_bit(dado,i));//escreve o bit no barramento
}
//----------------------------------------------------------------------------
