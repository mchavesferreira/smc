#ifndef __1WIRE_H
#define __1WIRE_H

#include "def_principais.h"

#define DDRx	DDRB	//define o DDR do pino DQ
#define PORTx	PORTB	//define o PORT do pino DQ
#define PINx	PINB	//define o PIN do pino DQ
#define DQ		PB0		//pino para a comunicação 

#define DQ_saida()		set_bit(DDRx,DQ)
#define DQ_entrada()	clr_bit(DDRx,DQ)
#define clr_DQ()		clr_bit(PORTx,DQ)
#define set_DQ()		set_bit(PORTx,DQ)
#define tst_DQ()		tst_bit(PINx,DQ)

unsigned char reset_1w();
void alimenta_1w();
unsigned char le_bit_1w() ;
void escreve_bit_1w(unsigned char bit_1w);
unsigned char le_byte_1w();
void escreve_byte_1w(unsigned char dado);

#endif