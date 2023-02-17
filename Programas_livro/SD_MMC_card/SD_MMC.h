#ifndef SD_MMC_H_
#define SD_MMC_H_

#include "def_principais.h"

typedef   unsigned char uchar;
typedef   unsigned int  uint;

#define DI	PB3		//entrada de dados (dados da memória)
#define DO	PB4		//saída de dados (dados para a memória)
#define CLK	PB5		//clock
#define CS	PB2		//seleção da memória (habilitação)

//comandos básicos para o SD/MMC

#define habilita_MMC()		clr_bit(PORTB,CS)
#define desabilita_MMC()	set_bit(PORTB,CS)

void inic_SPI();
unsigned char SPI(unsigned char c);

void comando_MMC(uchar index, uint ArgH, uint ArgL, uchar CRC);
unsigned char resposta_MMC(uchar resposta);
unsigned char inic_MMC();
unsigned char escreve_MMC(uchar *buffer, uint enderecoH, uint enderecoL);
unsigned char le_MMC(uchar *buffer,uint enderecoH, uint enderecoL);

#endif