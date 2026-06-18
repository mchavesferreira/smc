#include "i2c.h"
#include <util/delay.h>

//***************************************************************************************
void i2c_init(void)
{
	/*
		No I2C/TWI, os pinos SDA e SCL trabalham como linhas de coletor/dreno aberto.
		Por isso, mantemos os pinos como entrada e habilitamos pull-up.
	*/

	I2C_DDR &= ~((1 << SDA_PIN) | (1 << SCL_PIN));		// SDA e SCL como entrada
	I2C_PORT |= ((1 << SDA_PIN) | (1 << SCL_PIN));		// Pull-up interno

	TWCR = 0x00;
	TWSR = 0x00;										// Prescaler = 1

	TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;

	_delay_ms(50);
}

//***************************************************************************************
uint8_t i2c_start(uint8_t address)
{
	uint16_t timeout = 0;

	// Envia condição START
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)))
	{
		if (timeout++ > 10000)
		{
			return 1;
		}
	}

	// Envia endereço do dispositivo + bit R/W
	TWDR = address;
	TWCR = (1 << TWINT) | (1 << TWEN);

	timeout = 0;

	while (!(TWCR & (1 << TWINT)))
	{
		if (timeout++ > 10000)
		{
			return 1;
		}
	}

	return 0;
}

//***************************************************************************************
uint8_t i2c_byte(uint8_t byte)
{
	uint16_t timeout = 0;

	TWDR = byte;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)))
	{
		if (timeout++ > 10000)
		{
			return 1;
		}
	}

	return 0;
}

//***************************************************************************************
void i2c_stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

	/*
		Aguarda o hardware finalizar a condição STOP.
		O bit TWSTO é limpo automaticamente pelo hardware.
	*/

	while (TWCR & (1 << TWSTO))
	{
		
	}
}


//***************************************************************************************
uint8_t i2c_read_ack(void)
{
	uint16_t timeout = 0;

	/*
		Lê um byte do barramento I2C e envia ACK.

		Use esta função quando ainda existirem mais bytes para ler.
	*/

	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

	while (!(TWCR & (1 << TWINT)))
	{
		if (timeout++ > 10000)
		{
			return 0;
		}
	}

	return TWDR;
}

//***************************************************************************************
uint8_t i2c_read_nack(void)
{
	uint16_t timeout = 0;

	/*
		Lê um byte do barramento I2C e envia NACK.

		Use esta função no último byte da leitura.
	*/

	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)))
	{
		if (timeout++ > 10000)
		{
			return 0;
		}
	}

	return TWDR;
}