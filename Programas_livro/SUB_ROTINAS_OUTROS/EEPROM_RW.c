//--------------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.							//	
//--------------------------------------------------------------------------------- //

void EEPROM_escrita(unsigned int uiEndereco, unsigned char ucDado)
{
	while(EECR & (1<<EEPE)); 	//Espera completar um escrita pr�via 
	EEAR = uiEndereco; 			//Carrega o endere�o para a escrita
	EEDR = ucDado;				//Carrega o dado a ser escrito
	EECR |= (1<<EEMPE); 		//Escreve um l�gico em EEMPE
	EECR |= (1<<EEPE); 			//Inicia a escrita ativando EEPE
}

unsigned char EEPROM_leitura(unsigned int uiEndereco)
{
	while(EECR & (1<<EEPE)); 	//Espera completar um escrita pr�via 
	EEAR = uiEndereco; 			//Escreve o endere�o de leitura
	EECR |= (1<<EERE); 			//Inicia a leitura ativando EERE 
	return EEDR; 				//retorna o valor lido do registrador de
								//dados
}
