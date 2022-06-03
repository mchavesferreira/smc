//--------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							//	
//--------------------------------------------------------------------------------- //

//=================================================================================	//
// 		CÓDIGO EXEMPLO PARA USO DO TWI						 						//
//================================================================================	//
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);		//Envia a condição de início
//----------------------------------------------------------------------------------
	while (!(TWCR & (1<<TWINT)));	//Espera o TWINT ser ativo indicando que a condição de início foi transmitida 
//----------------------------------------------------------------------------------
	if ((TWSR & 0xF8) != START) 	//Verifica o valor do TWI no registrador de status.
		ERROR();					/*Mascara os bits do prescaler. Se o status for diferente da condição de início 
									chama uma função para o tratamento do erro*/
//-----------------------------------------------------------------------------------
	TWDR = SLA_W; 					//Carrega o endereço do escravo para a escrita
	TWCR = (1<<TWINT) | (1<<TWEN);	//limpa o bit TWINT no TWCR para começar a transmissão do endereço
//-----------------------------------------------------------------------------------
	while (!(TWCR & (1<<TWINT)));	/*Espera pela ativação do bit TWINT indicando que o endereço do escravo + o bit
									de escrita foi enviado e que o ACK/NACK foi recebido*/
//-----------------------------------------------------------------------------------
	if ((TWSR & 0xF8) != MT_SLA_ACK)//Verifica o valor do registrador de 
		ERROR();					/*status do TWI. Mascara os bits do prescaler. Se o status for diferente de
									MT_SLA_ACK chama uma função para o tratamento do erro*/
//-----------------------------------------------------------------------------------
	TWDR = DATA; 					//Carrega DATA no registrador TWDR. Limpa o bit TWINT no TWCR
	TWCR = (1<<TWINT) | (1<<TWEN);	//para iniciar a transmissão do dado.
//-----------------------------------------------------------------------------------
	while (!(TWCR & (1<<TWINT)));	/*Espera o bit TWINT ser ativo, indicando que
									o dado foi transmitido e que o ACK/NACK foi recebido*/
//-----------------------------------------------------------------------------------
	if ((TWSR & 0xF8) != MT_DATA_ACK)//Verifica o valor do registrador de 
		ERROR();					/*status do TWI. Mascara os bits do prescaler. Se o status for diferente de
									MT_DATA_ACK chama uma função para o tratamento do erro*/
//-----------------------------------------------------------------------------------
	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);//Transmite a condição de parada
//===================================================================================
