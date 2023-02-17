//------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								//	
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
//		INTERRUPÇÃO INT1 INTERROMPENDO A INT0											//
//=====================================================================================	//

#include "def_principais.h"	

ISR(INT0_vect);
ISR(INT1_vect);

//------------------------------------------------------------------------------------
int main()
{
    DDRD  = 0b11000000; 			
	PORTD = 0b11111111; 			
	
	UCSR0B = 0x00;				//desabilitar RX e TX para trabalho com os pinos do Arduino	

	EICRA = 0x00;      			//interrupções externas INT0 e INT1 no nível zero.
	EIMSK = (1<<INT1)|(1<<INT0);//habilita as duas interrupções
	sei();						//habilita interrupções globais, ativando o bit I do SREG
	
	while(1)
		cpl_bit(PORTD,LED2);	//pisca led numa velocidade muito grande (visualmente fica ligado)
}
//------------------------------------------------------------------------------------
ISR(INT0_vect)					//interrupção externa 0, quando o botão é pressionado o LED pisca
{
	unsigned char sreg;
	
	sreg = SREG;				//salva SREG porque a rotina pode alterar o seu valor	
	
	clr_bit(EIMSK,INT0);		//desabilita INTO para que ele não chame a si mesmo
	sei();						//habilita a interrupção geral, agora INT1 pode interromper INT0
	
	cpl_bit(PORTD,LED1);		//pisca led a cada 300 ms
	_delay_ms(300);	
	
	set_bit(EIMSK,INT0);		//habilita novamente a interrupção INT0 

	SREG = sreg;				//restaura o valor de SREG que pode ter sido alterado
}
//------------------------------------------------------------------------------------
ISR(INT1_vect)					//interrupção externa 1, mantendo o botão pressionado o LED pisca
{
	cpl_bit(PORTD,LED1);		//pisca led a cada 200 ms
	_delay_ms(200);		
}
//====================================================================================
