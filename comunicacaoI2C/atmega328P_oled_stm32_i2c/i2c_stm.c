#include "i2c_stm.h"
#include "i2c.h"

//***************************************************************************************
uint8_t stm_i2c_read_packet(uint8_t *buffer)
{
	uint8_t i;

	if (buffer == 0)
	{
		return STM32_I2C_ERROR_NULL;
	}

	/*
		Inicia a leitura do STM32.

		STM32_I2C_ADDR_7BIT = 0x30
		I2C_READ_ADDR(0x30) = 0x61
	*/

	if (i2c_start(I2C_READ_ADDR(STM32_I2C_ADDR_7BIT)))
	{
		i2c_stop();
		return STM32_I2C_ERROR_START;
	}

	/*
		Lê os 4 bytes enviados pelo STM32.

		Nos três primeiros bytes, o mestre envia ACK,
		informando que deseja continuar lendo.

		No último byte, o mestre envia NACK,
		informando que terminou a leitura.
	*/

	for (i = 0; i < STM32_PACKET_SIZE; i++)
	{
		if (i < (STM32_PACKET_SIZE - 1))
		{
			buffer[i] = i2c_read_ack();
		}
		else
		{
			buffer[i] = i2c_read_nack();
		}
	}

	i2c_stop();

	return STM32_I2C_OK;
}

//***************************************************************************************
uint8_t stm_i2c_read_adc(uint16_t *adc_value)
{
	uint8_t buffer[STM32_PACKET_SIZE];
	uint8_t checksum;

	if (adc_value == 0)
	{
		return STM32_I2C_ERROR_NULL;
	}

	/*
		Lê pacote bruto vindo do STM32.
	*/

	uint8_t status = stm_i2c_read_packet(buffer);

	if (status != STM32_I2C_OK)
	{
		return status;
	}

	/*
		Formato esperado:

		buffer[0] = ADC MSB
		buffer[1] = ADC LSB
		buffer[2] = checksum = MSB ^ LSB
		buffer[3] = marcador 0xA5
	*/

	if (buffer[3] != STM32_PACKET_END)
	{
		return STM32_I2C_ERROR_MARKER;
	}

	checksum = buffer[0] ^ buffer[1];

	if (buffer[2] != checksum)
	{
		return STM32_I2C_ERROR_CHECKSUM;
	}

	/*
		Remonta o valor de 16 bits.

		STM32 enviou:
		buffer[0] = parte alta
		buffer[1] = parte baixa
	*/

	*adc_value = ((uint16_t)buffer[0] << 8) | buffer[1];

	return STM32_I2C_OK;
}