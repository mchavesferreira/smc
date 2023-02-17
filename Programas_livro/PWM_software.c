//--------------------------------------------------------------------------------- //
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.							//	
//---------------------------------------------------------------------------------	//
//=================================================================================	//
//       PWM borda simples - n�o invertido, via software							//
//=================================================================================	//

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define	set_bit(y,bit)	(y|=(1<<bit))	//coloca em 1 o bit x da vari�vel Y
#define	clr_bit(y,bit)	(y&=~(1<<bit))	//coloca em 0 o bit x da vari�vel Y

#define PWM1		PB0					//escolha do pino para o sinal PWM1
#define Resol_PWM1 1000					//PWM1 com 1000 passos temporais de resolu��o

volatile unsigned int Passo_PWM1 = 0;
volatile unsigned int Ciclo_Ativo_PWM1;

//---------------------------------------------------------------------------------
ISR(TIMER0_OVF_vect)//o tempo de estouro do TC0  determina a menor resolu��o temporal para o PWM (ciclo ativo)
{
	Passo_PWM1++;						//incremento do passo de tempo 
	
	if(Passo_PWM1==Resol_PWM1)
	{	
		Passo_PWM1=0;					//inicializa o contador
		set_bit(PORTB,PWM1);			//na igualdade de compara��o coloca o pino PWM1 em 1
	}	
		
	if(Passo_PWM1==Ciclo_Ativo_PWM1)
		clr_bit(PORTB,PWM1);			//quando o contador atinge o valor do ciclo ativo do PWM1 o pino vai a zero	
		
}
//---------------------------------------------------------------------------------
int main()
{
	DDRB  = 0b00000001;					//somente o pino do LED como sa�da
	PORTB = 0b11111110;					//apaga o LED e habilita pull-ups nos pinos n�o utilizados
	
	TCCR0B = 1<<CS00;					//TC0 com prescaler de 1, a 16 MHz gera uma interrup��o a cada 16 us
	TIMSK0 = 1<<TOIE0;					//habilita a interrup��o do TC0
	sei();								//habilita interrup��es globais
	
	Ciclo_Ativo_PWM1 = 500;				//determina��o do ciclo ativo para o PWM1

	while(1)
	{
		//Aqui vai o c�digo principal
	}
}
//=================================================================================
