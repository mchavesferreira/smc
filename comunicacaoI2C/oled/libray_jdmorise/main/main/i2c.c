// 
// Library for abstraction of I2C Hardware to SW functions for AVR
// This library is reuse from the SSD1306 LCD lib from Michael Koehler and just packaged differently

/*-------------------------------------------------------------------------
# 
#  
# 	 This program is free software: you can redistribute it and/or modify
# 	 it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
#
#-------------------------------------------------------------------------
*/
#include "i2c.h"
#include <avr/interrupt.h>

void i2c_init(void){
	LCD_PORT |= (1 << SDA_Pin)|(1 << SDC_Pin);		// experimental, pullups for 12c_bus
	LCD_PORT_DDR |= (1 << SDA_Pin)|(1 << SDC_Pin);
	// set clock
	switch (PSC_I2C) {
		case 4:
			TWSR = 0x1;
			break;
		case 16:
			TWSR = 0x2;
			break;
		case 64:
			TWSR = 0x3;
			break;
		default:
			TWSR = 0x00;
			break;
	}
	TWBR = (uint8_t)SET_TWBR;
	// enable
	TWCR = (1 << TWEN);
}
void lcd_send_i2c_start(void){
    // i2c start
    TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
    while((TWCR & (1 << TWINT)) == 0);
    // send adress
    TWDR = LCD_I2C_ADDR;
    TWCR = (1 << TWINT)|( 1 << TWEN);
    while((TWCR & (1 << TWINT)) == 0);
}
void lcd_send_i2c_stop(void){
    // i2c stop
    TWCR = (1 << TWINT)|(1 << TWSTO)|(1 << TWEN);
}
void lcd_send_i2c_byte(uint8_t byte){
    TWDR = byte;
    TWCR = (1 << TWINT)|( 1 << TWEN);
    while((TWCR & (1 << TWINT)) == 0);
}