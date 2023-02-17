#ifndef _USART_H
#define _USART_H

#include "def_principais.h"

#define BAUD 	9600		//taxa de 9600 bps
#define MYUBRR	F_CPU/16/BAUD-1

#define tam_vetor	5	//número de digitos individuais para a conversão por ident_num()	 
#define conv_ascii	48	//48 se ident_num() deve retornar um número no formato ASCII (0 para formato normal)

void USART_Inic(unsigned int ubbr0);
void USART_Transmite(unsigned char dado);
unsigned char USART_Recebe();
void escreve_USART(char *c);
void escreve_USART_Flash(const char *c);

void ident_num(unsigned int valor, unsigned char *disp);

#endif