/* TODO: setup pins */
#define SDA_Pin			PC4
#define SDC_Pin			PC5
#define LCD_PORT		PORTC
#define LCD_PORT_DDR	DDRC
#define LCD_PIN			PINC

/* TODO: setup i2c/twi */
#define F_CPU 16000000UL
#define LCD_I2C_ADDR	0x78	// refer lcd-manual, 0x78 for 8-bit-adressmode, 0x3c for 7-bit-adressmode
#define LCD_INIT_I2C	YES		// init I2C via lcd-lib
#define F_I2C			200000UL // clock i2c
#define PSC_I2C			1		// prescaler i2c
#define SET_TWBR		(F_CPU/F_I2C-16UL)/(PSC_I2C*2UL)

#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

extern void i2c_init(void);						// init hw-i2c
extern void lcd_send_i2c_start(void);				// send i2c_start_condition
extern void lcd_send_i2c_stop(void);				// send i2c_stop_condition
extern void lcd_send_i2c_byte(uint8_t byte);		// send data_byte
