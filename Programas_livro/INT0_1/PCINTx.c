//------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								//	
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
//		Cada vez que um botão é pressionado o LED correspondente troca de estado		//
//===================================================================================== //

#include "def_principais.h"		//inclui arquivo com as definições principais

ISR(PCINT1_vect); 

int main()
{
	DDRC = 0x00;				//PORTC como entrada, 3 botões
	PORTC = 0xFF;				//habilita pull-ups
	DDRD  = 0b11100000;			//pinos PD5:7 do PORTC como saida (leds)
	PORTD = 0xFF;				//apaga leds e habilita pull-ups dos pinos não utilizados

	PCICR = 1<<PCIE1;			//habilita interrupção por qualquer mudança de sinal no PORTC
 	PCMSK1 = (1<<PCINT10)|(1<<PCINT9)|(1<<PCINT8);//habilita os pinos PCINT8:10 para gerar interrupção
	sei();						//habilita as interrupções
	
	while(1){}
}
//--------------------------------------------------------------------------------------
ISR(PCINT1_vect)//quando houver mais de um pino que possa gerar a interrupção é necessário testar qual foi
{
	if(!tst_bit(PINC,PC0))
		cpl_bit(PORTD,LED0);
	else if(!tst_bit(PINC,PC1))
		cpl_bit(PORTD,LED1);
	else if(!tst_bit(PINC,PC2))
		cpl_bit(PORTD,LED2);
		
	_delay_ms(200);
}
//---------------------------------------------------------------------------------------
