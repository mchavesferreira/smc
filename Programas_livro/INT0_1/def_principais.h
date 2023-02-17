#ifndef _DEF_PRINCIPAIS_H
#define _DEF_PRINCIPAIS_H

#define F_CPU 16000000UL		//frequência de trabalho
#include <avr/io.h> 	    	//definições do componente especificado
#include <avr/interrupt.h>		//define algumas  macros para as interrupções
#include <util/delay.h>			//biblioteca para o uso das rotinas de delay

//Definições de macros para o trabalho com bits
#define	set_bit(y,bit)	(y|=(1<<bit))	//coloca em 1 o bit x da variável Y
#define	clr_bit(y,bit)	(y&=~(1<<bit))	//coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) 	(y^=(1<<bit))	//troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) 	(y&(1<<bit))	//retorna 0 ou 1 conforme leitura do bit

#define LED0 PD5
#define LED1 PD6
#define LED2 PD7

#endif
