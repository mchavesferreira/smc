//------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.					//	
//------------------------------------------------------------------------- //
//=========================================================================	//
//           ROTINAS PARA A COMUNICA��O 1 WIRE 								//
//=========================================================================	//

#include "_1wire.h"
//--------------------------------------------------------------------------
unsigned char reset_1w()	//inicializa os dispositivos no barramento
{
	DQ_saida();				//DQ como sa�da
	clr_DQ();				//DQ em n�vel zero por 480us
	_delay_us(480);

	DQ_entrada();			//DQ como entrada, o resistor de pull-up mant�m DQ em n�vel alto
	_delay_us(60);

	if(tst_DQ())			//se nao detectou a presen�a j� retorna 1
		return 1;
		
	_delay_us(420);			//o pulso de presen�a pode ter 240 us
	return 0;				//retorna 0 para indicar sucesso
}
//---------------------------------------------------------------------------
void alimenta_1w()			//for�a o barramento em n�vel alto. 
{							//utilizado com dispositivos alimentados no modo parasita
	DQ_saida();
	set_DQ();
	_delay_ms(750);
	DQ_entrada();			//pull-up externo
}
//---------------------------------------------------------------------------
unsigned char le_bit_1w() 	//l� um bit do barramento 
{
	unsigned char dado;
	
	DQ_saida();
	clr_DQ();	
	_delay_us(2);
	DQ_entrada();
	_delay_us (15);			//aguarda o dispositivo colocar o dado na sa�da
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
unsigned char le_byte_1w()	//l� um byte do barramento
{
	unsigned char i, dado = 0;

	for (i=0;i<8;i++)		//l� oito bits iniciando pelo bit menos significativo
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
