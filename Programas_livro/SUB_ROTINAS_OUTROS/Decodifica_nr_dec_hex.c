//--------------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.							//	
//--------------------------------------------------------------------------------- //

//---------------------------------------------------------------------------------
//			Decodificando um n�mero decimal em seus d�gitos hexadecimais
//---------------------------------------------------------------------------------
	unsigned char num = 113; 			//0x71
	unsigned char digito1, digito0;
	...
	digito0 = num & 0b00001111;			/*mascara os 4 bits mais 
										significativos, resultando no 
										primeiro d�gito (digito0 = 1)*/
	digito1 = num >> 4;					/*desloca o valor do n�mero 4 bits
										para a direita,
										resultando no segundo d�gito (4 mais
										significativos), digito1 = 7 */
	...
//---------------------------------------------------------------------------------
