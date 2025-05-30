/*
 * exemplo_funcoes_pwm_ad_interrupcao.c
 *
 * Created: 23/05/2019 
 * Author : Marcos Chaves
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>		//biblioteca para o uso das rotinas de _delay_
#include <avr/interrupt.h>
#include "def_principais.h"
#include "USART.h"
			//inclusão do arquivo com as principais definições
unsigned int conta;


void configura_AD(){
	// configura canal 0
	ADMUX = (1<<REFS0) | (1<<MUX2) | (1<<MUX0);			//Tensão interna de ref (+5V), canal ADC5
	ADCSRA = (1<<ADEN) | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//habilita o AD e define um prescaler de 128 (clk_AD = F_CPU/128), 125 kHz
}


signed int le_temp()
{
	set_bit(ADCSRA, ADSC);								//inicia a conversão
	while(tst_bit(ADCSRA,ADSC));						//espera a conversão ser finalizada	
	return (ADC);
}

ISR(TIMER0_OVF_vect) // estouro interrupção do TC0
{   conta++;
	TCNT0=100; // 156 contagens equivalem a 10ms em 16mhz
	if(conta==100) // 100* 10ms = 1 seg
	{
		cpl_bit(PORTB,0); // inverte led segundos
        conta=0;
	}
}

ISR(TIMER1_OVF_vect)  // estouro timer 1
{  TCNT1=49910; 
	cpl_bit(PORTB,3);
	
}

ISR(TIMER1_COMPA_vect) // comparacao valor A
{    
	cpl_bit(PORTB,5);
}


void set_pwm_pd6(unsigned char valor)  // timer 0
{
	TCCR0A |=  (1<< COM0A1) | (1 << WGM01) | (1<<WGM00);
	TCCR0B =  0b00000011;
	OCR0A=valor;
	sei();
}

void set_pwm_pd5(unsigned char valor) // timer 0
{
	TCCR0A |=  (1<< COM0B1) | (1 << WGM01) | (1<<WGM00);
	TCCR0B =  0b00000011;
	OCR0B=valor;
	sei();
}


void set_pwm_pb1(unsigned int valor)  // timer 1
{	ICR1 = 1023; // estabelece o valor TOP para o PWM em 1023 = 10bit
	TCCR1A |= (1<<COM1A1);
	TCCR1B = (1<< WGM13)|(1<< CS11); //T=20ms prescaler 64
	TCCR1C = 0;
	OCR1A  = valor; //inicializa PWM para saida em tensão = 0 Vcc 
	sei();
}

void set_pwm_pb2(unsigned int valor)   // timer 1
{	ICR1 = 1023; // estabelece o valor TOP para o PWM em 1023 = 10bit
	TCCR1A |= (1<<COM1B1);
	TCCR1B = (1<< WGM13)|(1<< CS11); //T=20ms //T=20ms prescaler 64
	TCCR1C = 0;
	OCR1B  = valor; //inicializa PWM para saida em tensão = 0 Vcc
	sei();
}

void set_timer1_overflow(unsigned int valor)  // timer 1
{	TCCR1A=0b01010000;
	TCCR1B = (1<<CS12) | (1<<CS10);  // prescaler 1024  
	TIMSK1= 1 << TOIE1;
	TCNT1=valor;
	OCR1A=52000;
	OCR1B=60000;
	sei();
}

void set_timer0_overflow(unsigned int valor)
{
	    TCCR0A = 0b01010000;
	    TCCR0B = (1<<CS02) | (1<<CS00);		//TC0 com prescaler de 1024, a 16 MHz gera uma interrupção a cada 16,384 ms
	    TIMSK0 =   1<<TOIE0  ;			//		//habilita a interrupção estouro TC0
	    TCNT0= valor;  // contagem iniciando 
	    sei();
}

void set_timer1_contapulso(unsigned int valor)   // timer 1 entrada PD5
{	TIMSK1 = (1<<OCIE1A);	//habilita a interrupção do TC1 por igualdade de comparação
	TCCR1B = (1<<WGM12)|(1<<CS12) | (1<<CS11) |(1<<CS10);//clock externo  contagem na borda de subida  PD5- modo CTC
	OCR1A = 10;							/*valor para a contagem máxima do TC1 – VALOR DE COMPARAÇÃO. 
										chama-se a interrupcao TIMER1_COMPA_vect
										Como o sinal de clock externo é de 60 Hz, é gerada uma interrupção a cada 1 s*/
	sei();								//liga a interrupção

}


int main()
{
	DDRB  = 0b00111111;					//somente pino do LED como saída
	PORTB = 0b00000000;					//apaga LED 
	
	DDRD  = 0b00000000;						//somente pino do LED como saída
	
	UCSR0B = 0x00;				//PD0 e PD1 como I/O genérico, para uso no Arduino
    DDRC= 0b00000000;  // entrada
    PORTC= 0b11111111;
	
    //	unsigned char digitos[tam_vetor];	//declaração da variável para armazenagem dos digitos
    //	unsigned int valorbinario;
   //   USART_Inic(MYUBRR);  // inicia comunicao serial
    //  inic_LCD_4bits();   // inicializa LCD
  //  configura_AD();  // configura leitura AD escolhendo canal

 // set_pwm_pd6(200);
 //set_pwm_pd5(10);
  
 // set_timer1_contapulso(100);
 set_timer1_overflow(49910);
  //set_pwm_pb1(1021);
 // set_pwm_pb2(512);
  set_timer0_overflow(100);

	//inicializa o LCD
//	cmd_LCD(0x80,0);
//	escreve_LCD("IFSP CATANDUVA");	//string armazenada na RAM
  
	while(1)
	{
	//	cpl_bit(PORTB,2);
		_delay_ms(500);		


    /*  leitura conversor AD  
 
		valorbinario=le_temp();  // le o valor binario de 10 bits
		
		// imprime valor binario
		ident_num(valorbinario,digitos);
		cmd_LCD(0xCC,0);			//desloca o cursor
		cmd_LCD(digitos[3],1);   // impressao LCD
		cmd_LCD(digitos[2],1);
		cmd_LCD(digitos[1],1);
		cmd_LCD(digitos[0],1);
		OCR1B=valorbinario;  // atribui leitura 10 bits (0-1024)  ao ajuste de pwm
		ident_num(valorbinario,digitos);  // separa casas do numero
		USART_Transmite(digitos[3]);  // transmissao serial
		USART_Transmite(digitos[2]);
		USART_Transmite(digitos[1]);
		USART_Transmite(digitos[0]);
    	USART_Transmite('\n');	
  */
			 
	}
}
//==============================================================================


			
