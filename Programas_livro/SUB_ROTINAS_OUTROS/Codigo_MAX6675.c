//------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.					//	
//-------------------------------------------------------------------------	//

//--------------------------------------------------------------------------
//MAX6675
	...							//configura��es para uso da SPI
	clr_bit(PORTB,SS);			//pino SS em zero
   	temp_MSB =le_MAX();			//l� o byte + signific.(temp_MSB � um unsigned char)
	temp_LSB =le_MAX();			//l� o byte - signific.(temp_LSB � um unsigned char)
	set_bit(PORTB,SS);			//pino SS em 1

	valor_int = (temp_LSB>>3)|(temp_MSB<<5); //s�o 12 bits de dados, os demais n�o s�o analisados  
	valor_int = valor_int/4;				/*divide o valor por 4 para uma resolu��o de 1 grau,
											ou valor_int=(temp_LSB>>5)|(temp_MSB<<3) � j� divide.
 											valor_int � um unsigned int*/	
	...		   					//aqui vai a rotina para mostrar o valor no display	
//-----------------------------------------------------------------------------------
unsigned char  le_MAX()
{
	SPDR = 0x00;				//envia um dado qualquer para recebe um byte
	while(!(SPSR & (1<<SPIF)));	//aguarda o envio do dado
     return SPDR;				//retorna o valor recebido
}
//-----------------------------------------------------------------------------------
