//-------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								 //	
//-------------------------------------------------------------------------------------- //

//--------------------------------------------------------------------------------------
//Sub-rotina para ler apenas um byte do barramento I2C do DS1307
//--------------------------------------------------------------------------------------
unsigned char le_RTC(unsigned char endereco)
{ 
	start_bit();
	espera_envio();
	teste_envio_start();
	
	TWDR = 0xD0;		//carrega o endereço para acesso do DS1307 (bit0 = 0, escrita)
			  			//para outro CI basta trocar este endereço
	envia_byte();
	espera_envio();
	teste_envio_end_escrita();
	
	TWDR = endereco;	//ajuste do ponteiro de endereço para a leitura do DS1307

	envia_byte();
	espera_envio();
	teste_envio_dado();

	start_bit();		//reinício
     espera_envio();
	teste_envio_restart();

	TWDR = 0xD1;		//carrega o endereço para acesso do DS1307 (bit0 = 1 é leitura)
			  			//automaticamente o ATmega chaveia para o estado de recepção
	envia_byte();
	espera_envio();
	teste_envio_end_leitura();

	recebe_byte_ret_nack();	//só lê um byte, por isso retorna um NACK
	espera_recebimento();
	teste_recebe_byte_ret_nack();

	stop_bit();
	return TWDR;		//retorna byte recebido
}
//--------------------------------------------------------------------------------------
 

//--------------------------------------------------------------------------------------
//Sub-rotina para escrever apenas um byte no barramento I2C do DS1307
//--------------------------------------------------------------------------------------
void escreve_RTC(unsigned char dado_i2c, unsigned char endereco)
{
	start_bit();
	espera_envio(); 
	teste_envio_start();	
			
	TWDR = 0xD0;		//carrega o endereço para acesso do DS1307 (bit0 = 0 é escrita)
			  			//para outro CI basta trocar este endereço
	envia_byte();
	espera_envio();
	teste_envio_end_escrita();
	
	TWDR = endereco;	//carrega o endereço para escrita do dado no DS1307

	envia_byte();
	espera_envio();
	teste_envio_dado();

	TWDR = dado_i2c;	//carrega o dado para escrita no endereço especificado

	envia_byte();
	espera_envio();
	teste_envio_dado();

	stop_bit();
}
//--------------------------------------------------------------------------------------
