#define F_CPU 16000000UL
#define endereco 0x05
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "def_principais.h"			//inclusao do arquivo com as principais definicoes
#include "USART.h"
#include "execucao.h"       // biblioteca de comandos da maquina de leite em po
#include "i2cmaster.h"
#include "ads1115.h"



int convert(const char* str)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i = 1;
	}

	while (str[i] != '\0')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}

	return result * sign;
}

ISR(TIMER1_OVF_vect);
ISR(TIMER0_OVF_vect);

void serialTransmit(char data) {
	while (!( UCSR0A & (1<<UDRE0)) );	//espera o dado ser enviado
	UDR0 = data; 					//envia o dado

}
void serial_print(const char* str) {
	int i = 0;
	while (str[i] != '\0') {
		serialTransmit(str[i]);
		i++;
	}
}
// Função para receber um caractere pela porta serial
unsigned char serialReceive() {
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}
int main()
{
	
	UCSR0B = 0x00;	                    //PD0 e PD1 como I/O genérico, para uso no Arduino
	DDRB = 0b11111111;                  // declara as saidas
	PORTB = 0;                         // inicia a siadas desligadas
	DDRC = 0b00001010;                // declara as entradas
	PORTC =0b11110001;                       // ativa o pull up
	DDRD = 0b11111111;					   //PORTD como saída (display)
	PORTD= 0b11111111;				      //desliga o display e ativa o pull up dos dois botões
	TCCR1B = (1<<CS12) | (1<<CS10);		//  carrega um prescaler de 1024
	TIMSK1 = 1<<TOIE1;					//habilita a interrupção do TC1
	TCNT1 = 49910;
	TCCR0B = (1<<CS02) | (1<<CS00);		// carrega um prescaler de 1024
	TIMSK0 = 1<<TOIE0;					//habilita a interrupção do TC0
	sei();							//habilita interrupções globais, ativando o bit I do SREG
	USART_Inic(MYUBRR);
    i2c_init(); 
	  
	while(1)
	{
		switch(estado)
		{
			
			case 0:
			inicio();
			break;
			case 1:
			if(!pausa){produto();}
			break;
			case 2:
			if(!pausa){padrao();}
			break;
			case 3:
			if(!pausa){nivel_produto();}
			break;
			case 4:
			if(!pausa){temp_produto();}
			break;
			case 5:
			if(!pausa){rot_produto();}
			break;
			case 6:
			if(!pausa){enchendo();}
			break;
			case 7:
			if(!pausa){cheio();}
			break;
			case 8:
			if(!pausa){aquecimento();}
			break;
			case 9:
			if(!pausa){aciona_motor();}
			break;
			case 10:
			if(!pausa){desliga_motor();}
			break;
			case 11:
			if(!pausa){queda_rot();}
			break;
			case 12:
			if(!pausa){desliga_ventilacao();}
			break;
			case 13:
			if(!pausa){produto_final();}
			break;
			case 14:
			if(!pausa){reiniciar();}
			break;
		}
		
	}
	
}

ISR(TIMER1_OVF_vect) // verifica a cada 1 segundo
{
	TCNT1 = 49910;
	if(tempo!=0)
	{
		tempo--;
	}

}
ISR(TIMER0_OVF_vect) // verifica a cada 16ms
{
	if(!tst_bit(PINC,4)){set_bit(PORTC,emergencia);pausa=1;}
	else{pausa=0; clr_bit(PORTC,emergencia);}

}

