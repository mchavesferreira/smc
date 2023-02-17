//--------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							//	
//--------------------------------------------------------------------------------- //

EEPROM_escrita:

	SBIC EECR,EEPE		;Espera completar um escrita prévia
	RJMP EEPROM_escrita
	OUT  EEARH, R18		;Escreve o end. (R18:R17) no registr. de end.
	OUT  EEARL, R17
	OUT  EEDR,R16		;Escreve o dado (R16) no registrador de dado
	SBI  EECR,EEMPE		;Escreve um lógico em EEMPE
	SBI  EECR,EEPE		;Inicia a escrita colocando o bit EEPE em 1
	RET


EEPROM_leitura:

	SBIC EECR,EEPE		;Espera completar um escrita prévia 
	RJMP EEPROM_leitura
	OUT  EEARH, R18		;Escreve o end.(R18:R17) no registr. de end.
	OUT  EEARL, R17
	SBI  EECR,EERE		;Inicia leitura escrevendo em EERE
	IN   R16,EEDR		;Lê dado do registrador de dados em R16
	RET
