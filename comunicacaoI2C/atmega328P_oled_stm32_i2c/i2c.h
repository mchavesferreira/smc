#ifndef I2C_H_
#define I2C_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <stdint.h>

/*
	ATmega328P - I2C / TWI

	SDA -> PC4 / A4
	SCL -> PC5 / A5
*/

#define SDA_PIN			PC4
#define SCL_PIN			PC5

#define I2C_PORT		PORTC
#define I2C_DDR			DDRC

#define SCL_CLOCK		400000UL

/*
	Conversão de endereço I2C de 7 bits.

	Exemplo:
	STM32 endereço 7 bits = 0x30

	Escrita:
	0x30 << 1 = 0x60

	Leitura:
	(0x30 << 1) | 1 = 0x61
*/

#define I2C_WRITE_ADDR(addr)	((uint8_t)(((addr) << 1) | 0))
#define I2C_READ_ADDR(addr)		((uint8_t)(((addr) << 1) | 1))

void i2c_init(void);
uint8_t i2c_start(uint8_t address);
uint8_t i2c_byte(uint8_t byte);

uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);

void i2c_stop(void);

#endif