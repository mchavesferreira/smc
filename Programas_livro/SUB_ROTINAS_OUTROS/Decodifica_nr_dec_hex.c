//--------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							//	
//--------------------------------------------------------------------------------- //

//---------------------------------------------------------------------------------
//			Decodificando um número decimal em seus dígitos hexadecimais
//---------------------------------------------------------------------------------
	unsigned char num = 113; 			//0x71
	unsigned char digito1, digito0;
	...
	digito0 = num & 0b00001111;			/*mascara os 4 bits mais 
										significativos, resultando no 
										primeiro dígito (digito0 = 1)*/
	digito1 = num >> 4;					/*desloca o valor do número 4 bits
										para a direita,
										resultando no segundo dígito (4 mais
										significativos), digito1 = 7 */
	...
//---------------------------------------------------------------------------------
