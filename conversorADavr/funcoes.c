#include <avr/io.h>
#include <avr/interrupt.h>
#include "funcoes.h"
#include "lab_uino.h"


volatile unsigned int tempo[5];

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

void Timer0_init(void)
{

	TCNT0 = 217;
	TCCR0A =0;
	TCCR0B =  (1<<CS02);
	TIMSK0 = (1<<TOIE0);
}


ISR(TIMER0_OVF_vect)
{
	TCNT0 = 217;
	tempo[0]++;
	tempo[1]++;
	tempo[2]++;
	tempo[3]++;
	tempo[4]++;
}

int Read_ADC(int canal){

	ADMUX = (1<<REFS0)|canal;  // Set reference to AVcc,seleciona canal
	ADCSRA = (1<<ADPS2)|(1<<ADPS1);  
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADEN)|(1<<ADIF); // Enable ADC
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADEN)|(1<<ADSC); //inicia conversão
	// Disable digital input buffer on the ADC pin (reduces power consumption)
	DIDR0=(1<<5)|(1<<4)|(1<<1)|(1<<0);
	while(!(ADCSRA & (1<<ADIF))); // aguarda conversão
	return ADC;
}

void Set_PWM_T1A(uint16_t valor){
   ICR1 = 0x03FF; // set the TOP value for the PWM to 0x3FF = 10bit
   TCCR1A |= (1<<COM1A1);
   TCCR1B = (1<< WGM13)|(1<< CS11)|(1<< CS10); //T=20ms com ICR=157 step 128us
   TCCR1C = 0;
   OCR1A  = valor; //inicializa PWM para saida em tensão = 0 Vcc 4mA
}

void Set_PWM_T1B(uint16_t valor){
   ICR1 = 0x03FF; // set the TOP value for the PWM to 0x3FF = 10bit
   TCCR1A |= (1<<COM1B1);
   TCCR1B = (1<< WGM13)|(1<< CS11)|(1<< CS10); //T=20ms com ICR=157 step 128us
   TCCR1C = 0;
   OCR1B  = valor; //inicializa PWM para saida em tensão = 0 Vcc 4mA
}


void Set_PWM_T1C(uint16_t valor){
   ICR1 = 0x03FF; // set the TOP value for the PWM to 0x3FF = 10bit
   TCCR1A |= (1<<COM1C1);
   TCCR1B = (1<< WGM13)|(1<< CS11)|(1<< CS10); //T=20ms com ICR=157 step 128us
   TCCR1C = 0;
   OCR1C  = valor; //inicializa PWM para saida em tensão = 0 Vcc 4mA
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
		case 13: Liga_LCD_RS();
		break;
		case 14: Liga_LCD_E();
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
		case 13: Desliga_LCD_RS();
		break;
		case 14: Desliga_LCD_E();
		break;
	}
}

