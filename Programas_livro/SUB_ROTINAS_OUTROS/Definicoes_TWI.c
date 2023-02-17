//-------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								 //	
//-------------------------------------------------------------------------------------- //

#include <util/twi.h> 			//definições para o uso da interface i2c
...
//-------------------------------------------------------------------------------------
// Definições para o uso da comunicação I2C
//-------------------------------------------------------------------------------------
#define start_bit()		  		TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
#define stop_bit()				TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO)
#define espera_envio()			while (!(TWCR & (1<<TWINT)))
#define envia_byte()		  	TWCR = (1<<TWINT) | (1<<TWEN)
#define recebe_byte()			TWCR = (1<<TWINT) | (1<<TWEN)
#define espera_recebimento()	while (!(TWCR & (1<<TWINT)))
#define recebe_byte_ret_nack()	TWCR = (1<<TWINT) | (1<<TWEN)

//A rotina de tratamento de erro é por conta do programador e da sua lógica de programação

#define teste_envio_start()				if((TWSR & 0xF8) != TW_START) 			trata_erro();
#define teste_envio_end_escrita()		if((TWSR & 0xF8) != TW_MT_SLA_ACK) 		trata_erro();
#define teste_envio_dado()				if((TWSR & 0xF8) != TW_MT_DATA_ACK)		trata_erro();
#define teste_envio_restart()			if((TWSR & 0xF8) != TW_REP_START) 		trata_erro();
#define teste_envio_end_leitura()		if((TWSR & 0xF8) != TW_MR_SLA_ACK)		trata_erro();
#define teste_recebe_byte_ret_nack()	if((TWSR & 0xF8) != TW_MR_DATA_NACK)	trata_erro();
//-----------------------------------------------------------------------------------
