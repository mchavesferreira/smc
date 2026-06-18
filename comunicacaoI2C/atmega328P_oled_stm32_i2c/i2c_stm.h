#ifndef I2C_STM_H_
#define I2C_STM_H_

#include <stdint.h>

/*
	STM32F411 configurado como escravo I2C.

	Endereço 7 bits: 0x30

	No barramento I2C:
	- Escrita: 0x60
	- Leitura: 0x61

	A macro I2C_READ_ADDR(), definida em i2c.h, fará esse deslocamento.
*/

#define STM32_I2C_ADDR_7BIT		0x30

#define STM32_PACKET_SIZE		4
#define STM32_PACKET_END		0xA5

/*
	Códigos de retorno
*/

#define STM32_I2C_OK			0
#define STM32_I2C_ERROR_START	1
#define STM32_I2C_ERROR_MARKER	2
#define STM32_I2C_ERROR_CHECKSUM	3
#define STM32_I2C_ERROR_NULL		4

uint8_t stm_i2c_read_packet(uint8_t *buffer);
uint8_t stm_i2c_read_adc(uint16_t *adc_value);

#endif