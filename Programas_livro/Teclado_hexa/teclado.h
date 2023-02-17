#ifndef _TECLADO_H
#define _TECLADO_H

#include "def_principais.h"

#define LINHA   	PIND  	//registrador para leitura das linhas
#define COLUNA		PORTD	//registrador para escrita nas colunas 
							
//protótipo da função
unsigned char ler_teclado();

#endif

