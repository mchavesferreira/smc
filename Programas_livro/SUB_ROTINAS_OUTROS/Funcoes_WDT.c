//--------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							//	
//--------------------------------------------------------------------------------- //

//---------------------------------------------------------------------------------
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

void WDT_off(void)
{
	cli();							//desabilita as interrupções
	wdt_reset();
	
	MCUSR &= ~(1<<WDRF);			//limpa o flag sinalizador do WDT	
	WDTCSR |= (1<<WDCE) | (1<<WDE);	/*escreve 1 em WDCE e WDE. Mantém valores prévios
 									do prescaler para prevenir um estouro não intencional*/	
	WDTCSR = 0x00;					//desliga o WDT
	sei();							//habilita as interrupções
}
//--------------------------------------------------------------------------------
void WDT_Prescaler_Change(void)
{
	cli();							//desabilita interrupções
	
	wdt_reset();
	WDTCSR |= (1<<WDCE) | (1<<WDE);	//sequência de inicialização
	WDTCSR = (1<<WDE) | (1<<WDP2) | (1<<WDP0);/*ajusta o novo valor de prescaler
											  (tempo de estouro)*/
	sei();							//habilita interrupções
}
//--------------------------------------------------------------------------------
