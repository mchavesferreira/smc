/*
 * This file is part of lcd library for ssd1306/sh1106 oled-display.
 *
 * lcd library for ssd1306/sh1106 oled-display is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or any later version.
 *
 * lcd library for ssd1306/sh1106 oled-display is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Diese Datei ist Teil von lcd library for ssd1306/sh1106 oled-display.
 *
 * lcd library for ssd1306/sh1106 oled-display ist Freie Software: Sie können es unter den Bedingungen
 * der GNU General Public License, wie von der Free Software Foundation,
 * Version 3 der Lizenz oder jeder späteren
 * veröffentlichten Version, weiterverbreiten und/oder modifizieren.
 *
 * lcd library for ssd1306/sh1106 oled-display wird in der Hoffnung, dass es nützlich sein wird, aber
 * OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 * Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 * Siehe die GNU General Public License für weitere Details.
 *
 * Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 * Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 *
 *  lcd.h
 *
 *  Created by Michael Köhler on 22.12.16.
 *  Copyright 2016 Skie-Systems. All rights reserved.
 *
 *  lib for OLED-Display with ssd1306/sh1106-Controller
 *  first dev-version only for I2C-Connection
 *  at ATMega328P like Arduino Uno
 ****************************************************
 *  For other Atmegas/Attinys: GFX-Lib needs a
 *  minimum of 1029 byte SRAM!
 ****************************************************
 *
 */

#ifndef LCD_H
#define LCD_H
#endif /*  LCD_H  */

#ifndef YES
#define YES				1
#define NO				0
#else
#error "Check #defines for YES and NO in other sources !"
#endif

#if (__GNUC__ * 100 + __GNUC_MINOR__) < 303
#error "This library requires AVR-GCC 3.3 or later, update to newer AVR-GCC compiler !"
#endif

#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

/* TODO: define displaycontroller */
/*#define SH1106	// or SSD1306, check datasheet of your display*/
#define SSD1306

#define LCD_DISP_OFF	0xAE
#define LCD_DISP_ON		0xAF

#define WHITE			0x01
#define BLACK			0x00

#define DISPLAY_WIDTH	128
#define DISPLAY_HEIGHT	64
#define DISPLAYSIZE		DISPLAY_WIDTH*DISPLAY_HEIGHT/8	// 8 pages/lines with 128
                                                        // 8-bit-column: 128*64 pixel
#define CHAR_HEIGHT_40  40
#define CHAR_WIDTH_40  30                                                       // 1024 bytes

#define CHAR_HEIGHT_32  32
#define CHAR_WIDTH_32  24

#define CHAR_HEIGHT_24  24
#define CHAR_WIDTH_24  18



extern void lcd_init(uint8_t dispAttr);
extern void lcd_home(void);

extern void lcd_command(uint8_t cmd[], uint8_t size);				// transmit command to display
extern void lcd_data(uint8_t data[], uint16_t size);				// transmit data to display
extern void lcd_gotoxy(uint8_t x, uint8_t y);		// set curser at pos x, y. x means character, y means line (page, refer lcd manual)
extern void lcd_clrscr(void);						// clear screen
extern void lcd_putc(char c);						// print character on screen
extern void lcd_puts(const char* s);				// print string, \n-terminated, from ram on screen
extern void lcd_puts_p(const char* progmem_s);		// print string from flash on screen
extern void lcd_invert(uint8_t invert);			// invert display
extern void lcd_set_contrast(uint8_t contrast);	// set contrast for display
extern void lcd_clear_bigc(uint8_t column, uint8_t char_height); // clear big characters
extern void lcd_put_bigc(const char* addr, uint8_t column, uint8_t char_width,uint8_t general_width, uint8_t char_height); // print big characters on screen
extern void lcd_update_4(uint8_t c3, uint8_t c2, uint8_t c1, uint8_t c0); // update lcd display with 4 characters + colon
extern void lcd_update_6(uint8_t c5,uint8_t c4,uint8_t c3, uint8_t c2, uint8_t c1, uint8_t c0); // update lcd display with 4 characters + colon

// Init Sequence of SSD Display
static const uint8_t init_sequence [] PROGMEM = {	// Initialization Sequence
LCD_DISP_OFF,			// Display OFF (sleep mode)
0x20, 0b00,		// Set Memory Addressing Mode
				// 00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
				// 10=Page Addressing Mode (RESET); 11=Invalid
0xB0,			// Set Page Start Address for Page Addressing Mode, 0-7
0xC8,			// Set COM Output Scan Direction
0x00,			// --set low column address
0x10,			// --set high column address
0x40,			// --set start line address
0x81, 0x3F,		// Set contrast control register
0xA1,			// Set Segment Re-map. A0=address mapped; A1=address 127 mapped.
0xA6,			// Set display mode. A6=Normal; A7=Inverse
0xA8, DISPLAY_HEIGHT-1,		// Set multiplex ratio(1 to 64)
0xA4,			// Output RAM to Display
				// 0xA4=Output follows RAM content; 0xA5,Output ignores RAM content
0xD3, 0x00,		// Set display offset. 00 = no offset
0xD5,			// --set display clock divide ratio/oscillator frequency
0xF0,			// --set divide ratio
0xD9, 0x22,		// Set pre-charge period
0xDA, 0x12,		// Set com pins hardware configuration		
0xDB,			// --set vcomh
0x20,			// 0x20,0.77xVcc
0x8D, 0x14,		// Set DC-DC enable
};

