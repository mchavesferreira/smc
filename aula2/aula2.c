/*****************************************************
* Programa liga-desliga
* Alterna led5 e led12 com as chaves Busy e Sel_Out
******************************************************/

// inclui arquivos de definições da biblioteca
#include <avr/io.h>

// define xtal da CPU para rotinas de delay.
#define F_CPU 8000000UL
#include <util/delay.h>


// inclui arquivos e definições da placa
#define Liga_D0() PORTD |= (1<<4)
#define Liga_D7() PORTC |= (1<<7)

#define Desliga_D0() PORTD &= ~(1<<4)
#define Desliga_D7() PORTC &= ~(1<<7)

#define Ch_busy_lig !(PIND & (1<<5))
#define Ch_sel_out_lig !(PINF & (1<<6))

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
		if(Ch_busy_lig){
			Liga_D0();
			Desliga_D7();
		}

		if(Ch_sel_out_lig){
			Liga_D7();
			Desliga_D0();
		}
	}
}
