/*
 * main.c
 *
 * Created: 25/05/2022 17:20:27
 * Author : mchav
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "SSD1306.h"




int main(void) {
	
	OLED_Init();  //initialize the OLED
	OLED_Clear(); //clear the display (for good measure)
	
	while (1) {
		
		OLED_SetCursor(0, 0);        //set the cursor position to (0, 0)
		OLED_Printf("Hello World!"); //Print out some text
		OLED_ScrollMessage(1, "Scroollllll");
		OLED_SetCursor(4, 0);        //set the cursor position to (0, 0)
		OLED_Printf("SMC - IFSP Catanduva"); //Print out some text

	}
	
	return 0; // never reached
}

