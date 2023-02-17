#ifndef _DS1307_H
#define _DS1307_H

#include "def_principais.h"

#define start_bit() 				TWCR |= (1<<TWSTA)
#define stop_bit()					TWCR |= (1<<TWSTO)	
#define clr_start_bit()				TWCR &= ~(1<<TWSTA)

//TWI
void inic_TWI();
void escreve_DS1307(unsigned char end_escrita, unsigned char dado);
unsigned char le_DS1307(unsigned char end_leitura);
ISR(TWI_vect);

//trabalho com o LCD para mostrar o tempo
void converte2BCD(unsigned char dado, unsigned char endereco);
void ler_convert_tudo(unsigned char ende);
void ajusta_tempo(unsigned char end, unsigned char limite,unsigned char ini_nr1);
void ajusta_tempo2(unsigned char qual);
void mostra_tempo();
void mostra_pontos(unsigned char desliga);
void alerta_display(unsigned char qual);

#endif