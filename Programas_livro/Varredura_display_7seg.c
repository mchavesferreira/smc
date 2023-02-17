//--------------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.							//	
//---------------------------------------------------------------------------------	//
//================================================================================	//
//		VARREDURA DE DISPLAYS DE 7 SEGMENTOS										//
//================================================================================	//

#define F_CPU 16000000UL
#include <avr/io.h> 	    	
#include <avr/interrupt.h> 
	    
#define	clr_bit(Y,bit_x)	(Y&=~(1<<bit_x))	

volatile unsigned char DISP[4];		//valores para os displays

//---------------------------------------------------------------------------------
//INTERRUPCAO - VARREDURA DOS DISPLAYS DE 7 SEGMENTOS
//---------------------------------------------------------------------------------
ISR(TIMER0_OVF_vect)
{
	static unsigned char x;

	PORTB |= 0x0F;		//apaga todos os displays (o controle dos displays est� nos pinos (PB0:PB3)
  	PORTD = DISP[x];	//coloca a informa��o do display no porta correspondente
	clr_bit(PORTB,x);	//habilita o display correspondente (PB0:PB3)
	x++;

   	if(x==4)	x = 0;  //apos 4 rota��es inicializa para o primeiro display
}
//---------------------------------------------------------------------------------?
int main()
{	
	DDRD = 0xFF;		//dados dos displays
	DDRB = 0x0F;		//controle dos displays
	PORTB = 0xFF;		//apaga displays e liga pull-ups
	
	UCSR0B = 0x00;		//para usar os pinos do PORTD no Arduino

	//TC0 gerando interrup��o
	TIMSK0 = 1<<TOIE0;	//habilita a interrup��o por estouro do timer 0
	TCCR0B = 1<<CS02;	//CLK/256 prescaler (CLK=16MHz), estouro a cada 4ms
	sei();				//habilita a interrup��o global	

	while(1)	//qualquer escrita em DISP[x] � automaticamente apresentada nos displays
	{
		DISP[0]= 0xC0;	//valor para o n�mero zero
		DISP[1]= 0xF9;	//valor para o n�mero um 
		DISP[2]= 0xA4;	//valor para o n�mero dois 
		DISP[3]= 0xB0;	//valor para o n�mero tr�s 
	}
}
//=================================================================================
