/*****************************************************
* Programa pisca-pisca
* faz o led5 sinal D0 ficar piscando indefinidamente
******************************************************/

// inclui arquivos de definições da biblioteca
#include <avr/io.h>

// define xtal da CPU para rotinas de delay.
#define F_CPU 8000000UL
#include <util/delay.h>


// inclui arquivos e definições da placa
#define Liga_D0() PORTD |= (1<<4)
#define Desliga_D0() PORTD &= ~(1<<4)


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

// programa principal
int main(void)
{
	// bloco de setup da placa
	// será executado somente 1 vez após reset

	IO_init(); // inicia pinos de IO da placa. 

	
	while(1){
		//bloco que será executado repetidamente em loop
		Liga_D0();
		_delay_ms(1000); // aguarda 1s
		Desliga_D0();
		_delay_ms(1000);
	}
}
