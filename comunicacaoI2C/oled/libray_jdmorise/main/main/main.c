//#########################################################
// (c) 2019 JD Morise
// 
// Simple Clock programm with Microchip ATmega8A and SSD1306 OLED Display
// 

/*-------------------------------------------------------------------------
# 
# (C) 2019, jdmorise@yahoo.com
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

//#########################################################

//#########################################################
// 
// Version 0.2.1
// Minor Updates for new format of include headers
//
//#########################################################

//#########################################################
// 
// Version 0.2.0
// Initial Version 
//
//#########################################################


#define F_CPU 16000000UL	//define a frequência do microcontrolador 16MHz (necessário para usar as rotinas de atraso)

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "lcd.h"
#include "i2c.h"

#define timer_reg_div ((1 << CS12) | (1 << CS10)) // Timer with divide ratio of 8

/* Variables for time control */

int8_t hour_ten,hour_one,min_ten,min_one,sec_ten,sec_one;

int16_t msec; // The variable contains is 1/16 sec, not 1 millisec

static uint8_t update_lcd = 0;

int16_t timer_cal_val = 10000; 
int8_t timer_cal_div = 1;
uint16_t timer_reg_val = 1000;

/* EEPROM Variables */ 
uint8_t EEMEM EE_timer_cal_div = (1 << CS11);
uint16_t EEMEM EE_timer_cal_val = 13590; // Calibrated Timer Value (division of 8) 
uint16_t EEMEM EE_timer_reg_val = 932; // Calibrated Regular Timer Value  (division of 1024) 

// correct initial values of TIME
uint8_t EEMEM EE_init_hour_ten = 0; 
uint8_t EEMEM EE_init_hour_one = 0; 
uint8_t EEMEM EE_init_min_ten = 0; 
uint8_t EEMEM EE_init_min_one = 0; 

/* Timer Interrupt */
ISR(TIMER1_COMPA_vect){

	msec++;

	if (msec == 4) {
		
		 OCR1A = timer_cal_val;  
		 TCCR1B = ((1 << WGM12) | timer_cal_div);
		 TCNT1 = 0; 
		 
		 if(update_lcd == 1){
		 	lcd_update_4(min_ten, min_one, sec_ten, sec_one); 
			update_lcd = 0; 
			}
	}	

	if (msec == 5){	
		OCR1A = timer_reg_val;
		TCCR1B = ((1 << WGM12) | timer_reg_div);
		TCNT1 = 0;
	
		sec_one++; 
		msec = 0; 
		if (sec_one == 10){
			sec_ten++; 
			sec_one=0;
		}
		
		if (sec_ten == 6) {min_one++; sec_ten=0;}
		if (min_one == 10) {min_ten++; min_one=0;}
		if (min_ten == 6) {hour_one++; min_ten=0;}
		if (hour_one == 10) {hour_ten++; hour_one=0;}
		if ((hour_ten == 2) & (hour_one == 4)) {
			hour_ten = 0; 
			hour_one = 0;
		}
		update_lcd = 1; 
	}
}


// Main function
//  

void lcd_clear_screen(){

	for(uint8_t i = 0; i<8; i++) {
		lcd_gotoxy(0, i); 
		lcd_puts("                      "); 
	}

}

int main (void)
{
	/* Init OLED Display */
	
    lcd_init(LCD_DISP_ON);
    lcd_clear_screen(); 
        
     /* put string to display (line 7) with linefeed */
    
	lcd_gotoxy(0,7); 
	lcd_puts("IFSP Regular 40");
	lcd_home();
	lcd_set_contrast(196);

	/* Read Timer Calibration Values from EEPROM */

	timer_cal_div = eeprom_read_byte(&EE_timer_cal_div); 
	timer_cal_val = eeprom_read_word(&EE_timer_cal_val);
  	timer_reg_val = eeprom_read_word(&EE_timer_reg_val);

	/* set Timer 1 for Clock Control */


	TCCR1B = ((1 << WGM12) | timer_reg_div);
	OCR1A = timer_reg_val;


	/* Timer Interrupt Control*/
	TIMSK1 = (1 << OCIE1A); 

	/* Global Interrupt Enable */ 
	sei();

	/* Initialize time variables */ 
	sec_one = 7;
	sec_ten = 2; 

	min_ten = 3;
	min_one = 4;

	hour_ten = 0;
	hour_one = 0; 

	/* Update LCD Display */ 

	lcd_update_4(min_ten, min_one, sec_ten, sec_one);  

	//lcd_update_6(hour_ten, hour_one, min_ten, min_one, sec_ten, sec_one);  


	while (1) {}
	return 0; 
	
}

