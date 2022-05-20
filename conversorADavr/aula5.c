/*****************************************************
* Programa lendo ADC
* 
******************************************************/

// para incluir printf com float colocar em opcoes do linker
// -Wl,-u,vfprintf -lprintf_flt -lm


#include <avr/io.h>
#include <stdio.h>

#define F_CPU 8000000UL
#include <util/delay.h>


#include "lab_uino.h"
#include "lcd_usb.h"
#include "funcoes.h"



// programa principal
int main(void)
{
char lcd_buffer[20];
int valor_adc;
float tensao;

	IO_init(); // inicia pinos de IO da placa. 
	lcd_init(LCD_DISP_ON); //inicia o LCD
	lcd_clrscr(); //Limpa tela do LCD

	while(1){


		valor_adc=Read_ADC(1);
		tensao =  valor_adc * 0.004887; //(5/1023)
		lcd_gotoxy(0,0);
		sprintf(lcd_buffer,"ADC_1  = %d ",valor_adc);
		lcd_puts(lcd_buffer);
		lcd_gotoxy(0,1);
		sprintf(lcd_buffer,"Tensao = %1.2fV  ",tensao);
		lcd_puts(lcd_buffer);

	}
}
