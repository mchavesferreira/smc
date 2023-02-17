//------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.					//	
//-------------------------------------------------------------------------	//

//-------------------------------------------------------------------------
// Sobreamostragem � aumentando a resolu��o do ADC de 10 para 11 bits
//-------------------------------------------------------------------------
unsigned int ADC_11bits;
. . .
ISR(ADC_vect)	
{
	static unsigned int ADC_soma=0;
	static unsigned char cont=4;
	
	ADC_soma += ADC;    //soma o valor do ADC na vari�vel para o aumento da resolu��o
	
	cont--;
	if(cont==0)
	{
		ADC_11bits = ADC_soma >> 1;	//deslocamento de 1 bit para a direita
		ADC_soma=0;
		cont=4;
	}
}
//--------------------------------------------------------------------------
