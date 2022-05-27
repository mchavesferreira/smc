/*
 *  Created: 19.06.2016 11:38:00
 *  Author: Ulrich
 */ 

#ifndef __oled_H
	#define __oled_H

	#include <inttypes.h>
	#include <avr/io.h>
	#include <avr/pgmspace.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <ctype.h>
	#include <string.h>
	#include <util/delay.h>

	#define SDA_PIN			PC4
	#define SCL_PIN			PC5
	#define I2C_PORT		PORTC

	#define OLED_I2C_ADDR	0x78
	#define SCL_CLOCK		400000UL
    #define F_CPU 16000000UL

	void oled_init(void);
	void oled_clear_screen(void);
	void oled_font_size (uint8_t byte);
	void oled_gotoxy(uint8_t x, uint8_t y);
	void oled_write_char(char c);
	void oled_write_str(char* str);
	void oled_write_P (const char *Buffer,...);

	#define oled_write(format, args...)   oled_write_P(PSTR(format) , ## args)

	#define COMMAND						0x00
	#define DATA						0x40

	#define SET_CONTRAST_CONTROL		0x81
	#define SET_DISPLAY_ON				0xAF
	#define SET_DISPLAY_OFF				0xAE
	#define SET_DISPLAY_NORMAL			0xA6
	#define SET_DISPLAY_INVERSE		0xA7
	#define ENTIRE_DISPLAY_ON			0xA4
	
	#define SET_MEMORY_ADDR_MODE		0x20
		#define HORIZONTAL_ADDRESSING_MODE	0x00
		#define VERTICAL_ADDRESSING_MODE	0x01
		#define PAGE_ADDRESSING_MODE		0x02
		
	#define SET_PAGE_START				0xB0	//~0xB7
	#define SET_COLUMN_ADDRESS			0x21
	#define SET_PAGE_ADDRESS			0x22
	
	#define SET_COM_OUTPUT_NORMAL		0xC0
	#define SET_COM_OUTPUT_REMAPPED		0xC8
	
	#define SET_DISPLAY_OFFSET			0xD3
	#define SET_DISPLAY_CLOCK			0xD5
	#define SET_PRECHARGE_PERIOD		0xD9
	#define SET_COM_PINS				0xDA
	
	#define SET_VCOMH_DESELECT			0xDB	//0x00,0x20,0x30
	
	#define	SET_LOWER_COLUMN			0x00
	#define	SET_HIGHER_COLUMN			0x10
	#define	SET_DISPLAY_START_LINE		0x40
	
	#define SET_SEGMENT_REMAP_O1		0xA0	
	#define SET_SEGMENT_REMAP_O2		0xA1
	
	#define SET_MULTIPLEX_RATIO			0xA8
	#define COMMAND_NO_OPERATION		0xE3
	
	#define CHARGE_BUMB_SETTING			0x8D


#endif // __oled_H 
