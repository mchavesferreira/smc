/*****************************************************
* Programa vai-vem de leds
* 
******************************************************/

// inclui arquivos de definições da biblioteca
#include <avr/io.h>

// define xtal da CPU para rotinas de delay.
#define F_CPU 8000000UL
#include <util/delay.h>


// inclui arquivos e definições da placa
#include "lab_uino.h"

//define funções e rotinas
void IO_init(void){
	DDRB = (1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1);
	DDRC = (1<<6)|(1<<7);
	DDRD = (1<<4)|(1<<6)|(1<<7);
	DDRE = 0;
	DDRF = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = (1<<5)|(1<<1)|(1<<0);
	PORTE = (1<<2);
	PORTF = (1<<7)|(1<<6);
	MCUCR |= (1<<JTD);
	MCUCR |= (1<<JTD); //desliga interface JTAG.
}

void led_on(unsigned char led){

	switch(led){
		case 1: Liga_Strobe();
		break;
		case 2: Liga_Feed();
		break;
		case 3: Liga_Sel_in();
		break;
		case 4: Liga_Init();
		break;
		case 5: Liga_D0();
		break;
		case 6: Liga_D1();
		break;
		case 7: Liga_D2();
		break;
		case 8: Liga_D3();
		break;
		case 9: Liga_D4();
		break;
		case 10: Liga_D5();
		break;
		case 11: Liga_D6();
		break;
		case 12: Liga_D7();
		break;
	}
}

void led_off(unsigned char led){

	switch(led){
		case 1: Desliga_Strobe();
		break;
		case 2: Desliga_Feed();
		break;
		case 3: Desliga_Sel_in();
		break;
		case 4: Desliga_Init();
		break;
		case 5: Desliga_D0();
		break;
		case 6: Desliga_D1();
		break;
		case 7: Desliga_D2();
		break;
		case 8: Desliga_D3();
		break;
		case 9: Desliga_D4();
		break;
		case 10: Desliga_D5();
		break;
		case 11: Desliga_D6();
		break;
		case 12: Desliga_D7();
		break;
	}
}

// programa principal
int main(void)
{
int x;

	IO_init(); // inicia pinos de IO da placa. 

	
	while(1){

		for(x=1;x<13;x++){
			led_on(x);
			_delay_ms(50);
			led_off(x);
		}

		for(x=12;x>0;x--){
			led_on(x);
			_delay_ms(50);
			led_off(x);
		}

	}
}
