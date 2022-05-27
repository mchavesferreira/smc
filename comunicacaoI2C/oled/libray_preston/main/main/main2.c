
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "SSD1306.h"



#include <stdlib.h>
#include "i2c.c"
#include "i2c.h"

#define  SSD1306_ADDRESS 0x3C

void initDisplay()
{
	i2c_start(SSD1306_ADDRESS);

	i2c_write(0xAE);          // 0xAE // display off
	i2c_write(0xD5);          // 0xD5 // set display clock division
	i2c_write(0x80);          // the suggested ratio 0x80
	i2c_write(0xA8);          // 0xA8 set multiplex
	i2c_write(63);            // set height
	i2c_write(0xD3);          // set display offset
	i2c_write(0x0);           // no offset
	i2c_write(64);            // line #0 setstartline
	i2c_write(0x8D);          // 0x8D // chargepump
	i2c_write(0x14);
	i2c_write(0x20);          // memory mode
	i2c_write(0x00);          // 0x0 act like ks0108
	i2c_write(161);           // segremap
	i2c_write(0xC8);          // comscandec
	i2c_write(0xDA);          // 0xDA set com pins
	i2c_write(0x12);
	i2c_write(0x81);          // 0x81 // set contract
	i2c_write(0xCF);
	i2c_write(0xD9);          // 0xd9 set pre-charge
	i2c_write(0xF1);
	i2c_write(0xDB);          // SSD1306_SETVCOMDETECT
	i2c_write(0x40);
	i2c_write(0xA4);          // 0xA4 // display all on resume
	i2c_write(0xA6);          // 0xA6 // normal display
	i2c_write(0x2E);          // deactivate scroll
	i2c_write(0xAF);          // --turn on oled panel

	i2c_stop();
}

void drawPixel()
{
	i2c_start( SSD1306_ADDRESS );

	i2c_write(0x21);          // column address
	i2c_write(0);             // Column start address (0 = reset)
	i2c_write(127);           // Column end address (127
	i2c_write(0x22);          // page address
	i2c_write(0x00);          // Page start address (0 = reset)
	i2c_write(7);             // Page end address

	int i;

	int z=0;

	for ( i = 0; i < ( 128 * 64 / 8 ); i++ )
	{
		if ( z == 0 )
		{
			i2c_write( 0xff );
			z = 1;
		}
		else
		{
			i2c_write( 0x00 );
			z = 0;
		}
	}

	i2c_stop();
}

int main(void){

	i2c_init();
	initDisplay();
	drawPixel();

	return 0;
}