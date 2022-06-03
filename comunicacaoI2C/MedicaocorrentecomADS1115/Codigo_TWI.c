//--------------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.							//	
//--------------------------------------------------------------------------------- //

//=================================================================================	//
// 		C�DIGO EXEMPLO PARA USO DO TWI						 						//
//================================================================================	//
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);		//Envia a condi��o de in�cio
//----------------------------------------------------------------------------------
	while (!(TWCR & (1<<TWINT)));	//Espera o TWINT ser ativo indicando que a condi��o de in�cio foi transmitida 
//----------------------------------------------------------------------------------
	if ((TWSR & 0xF8) != START) 	//Verifica o valor do TWI no registrador de status.
		ERROR();					/*Mascara os bits do prescaler. Se o status for diferente da condi��o de in�cio 
									chama uma fun��o para o tratamento do erro*/
//-----------------------------------------------------------------------------------
	TWDR = SLA_W; 					//Carrega o endere�o do escravo para a escrita
	TWCR = (1<<TWINT) | (1<<TWEN);	//limpa o bit TWINT no TWCR para come�ar a transmiss�o do endere�o
//-----------------------------------------------------------------------------------
	while (!(TWCR & (1<<TWINT)));	/*Espera pela ativa��o do bit TWINT indicando que o endere�o do escravo + o bit
									de escrita foi enviado e que o ACK/NACK foi recebido*/
//-----------------------------------------------------------------------------------
	if ((TWSR & 0xF8) != MT_SLA_ACK)//Verifica o valor do registrador de 
		ERROR();					/*status do TWI. Mascara os bits do prescaler. Se o status for diferente de
									MT_SLA_ACK chama uma fun��o para o tratamento do erro*/
//-----------------------------------------------------------------------------------
	TWDR = DATA; 					//Carrega DATA no registrador TWDR. Limpa o bit TWINT no TWCR
	TWCR = (1<<TWINT) | (1<<TWEN);	//para iniciar a transmiss�o do dado.
//-----------------------------------------------------------------------------------
	while (!(TWCR & (1<<TWINT)));	/*Espera o bit TWINT ser ativo, indicando que
									o dado foi transmitido e que o ACK/NACK foi recebido*/
//-----------------------------------------------------------------------------------
	if ((TWSR & 0xF8) != MT_DATA_ACK)//Verifica o valor do registrador de 
		ERROR();					/*status do TWI. Mascara os bits do prescaler. Se o status for diferente de
									MT_DATA_ACK chama uma fun��o para o tratamento do erro*/
//-----------------------------------------------------------------------------------
	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);//Transmite a condi��o de parada
//===================================================================================
