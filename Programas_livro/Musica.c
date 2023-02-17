//--------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							//	
//---------------------------------------------------------------------------------	//
//=================================================================================	//
//		MUSICAS COM O ATMEGA														//
//		Leitura de arquivos RTTTL - Ringtones  										//
//=================================================================================	//

#define F_CPU 16000000UL					//frequência de operação de 16MHz
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

//Definições de macros 
#define	set_bit(Y,bit_x) (Y|=(1<<bit_x))	//ativa  bit 
#define	clr_bit(Y,bit_x) (Y&=~(1<<bit_x))	//limpa bit  

#define som		PB1			//pino OC1A para saída do sinal

#define d_inic	4			//valor inicial de duração da nota musical
#define o_inic	5			//valor  inicial da oitava 
#define b		100			//o nr de batidas indica a velocidade da musica (alterar p/ mudar a velocidade), maior =  mais rápido

#define t_min  (7500/b)*10  //tempo mínimo para formar o tempo base das notas musicais (1/32)

/*Max. de 255 caract. para MUSICA, caso contrário o índice de varredura deve ser alterado para unsigned int
Marcha Imperial - Star Wars (não usar espaço entre os caracteres) – escrever em uma única linha*/

const char MUSICA[] PROGMEM ={"e,e,e,8c,16p,16g,e,8c,16p,16g,e,p,b,b,b,8c6,16p,16g,d#,8c,16p,16g,e,8p"}; 
				
//---------------------------------------------------------------------------
int main()
{
	unsigned int k;
	unsigned char d, o, j, n, i=0; 
	
    DDRB |= (1<<som);		//habilita a saída de som	
	
	TCCR1A = 1<<COM1A0;		//TC1 modo CTC comparação com OCR1A, prescaler=1
	TCCR1B = (1<<WGM12)|(1<<CS10);	
	
	//-----------------------------------------------------------------------
	//LEITURA E EXECUÇÃO DO ARQUIVO RTTTL
	//-----------------------------------------------------------------------
	do
   	{
		o = o_inic;		//carrega o valor default para a oitava		

		if((pgm_read_byte(&MUSICA[i])=='3')&&(pgm_read_byte(&MUSICA[i+1])=='2')){d=32; i+=2;}
    	else if((pgm_read_byte(&MUSICA[i])=='1')&&(pgm_read_byte(&MUSICA[i+1])=='6')){d=16; i+=2;}
    	else if(pgm_read_byte(&MUSICA[i])=='8') {d=8; i++;} 
    	else if(pgm_read_byte(&MUSICA[i])=='4') {d=4; i++;} 
    	else if(pgm_read_byte(&MUSICA[i])=='2') {d=2; i++;} 
    	else if(pgm_read_byte(&MUSICA[i])=='1') {d=1; i++;} 
		else d=d_inic; 	//carrega o valor dafault para a duração

		if(pgm_read_byte(&MUSICA[i+1])=='#')
		{	
			switch(pgm_read_byte(&MUSICA[i]))//carrega a oitava # default (4a) 
			{
            		case 'a': OCR1A = 17159;  break;//A# - Lá#
                	case 'c': OCR1A = 14429;  break;//C# - Dó# 
                	case 'd': OCR1A = 12852;  break;//D# - Ré#
                	case 'f': OCR1A = 10807;  break;//F# - Fá#
                	case 'g': OCR1A =  9627;  break;//G# - Sól#
            }
            i+=2;
        }
		else
		{
            switch(pgm_read_byte(&MUSICA[i]))//carrega a oitava default (4a) 
			{
               	case 'a': OCR1A = 18181;  break;//A - Lá
               	case 'b': OCR1A = 16197;  break;//B - Si
               	case 'c': OCR1A = 15287;  break;//C - Dó
               	case 'd': OCR1A = 13618;  break;//D - Ré
               	case 'e': OCR1A = 12131;  break;//E - Mi
               	case 'f': OCR1A = 11449;  break;//F - Fá
               	case 'g': OCR1A = 10199;  break;//G - Sol
 				case 'p': clr_bit(TCCR1A,COM1A0); break;//p = pausa (som como entrada, desliga o som)
            }
            i++;
        }
		n = 32/d;			//tempo de duração de cada nota musical
        
		if(pgm_read_byte(&MUSICA[i])=='.'){n=n+(n/2); i++;}//duração 50% >

       	if(pgm_read_byte(&MUSICA[i])=='4')     { o=4; i++;}
		else if(pgm_read_byte(&MUSICA[i])=='5'){ o=5; i++;}
		else if(pgm_read_byte(&MUSICA[i])=='6'){ o=6; i++;} 
		else if(pgm_read_byte(&MUSICA[i])=='7'){ o=7; i++;} 

        if(pgm_read_byte(&MUSICA[i])=='.'){n=n+(n/2); i++;}// duração 50% >

       	switch(o)//troca a oitava se nao for a default (o = 4)
		{
			case 5: OCR1A = OCR1A>>1; break; //divide por 2 
			case 6: OCR1A = OCR1A>>2; break; //divide por 4
			case 7: OCR1A = OCR1A>>4; break; //divide por 8
		}
		//-------------------------------------------------------------------		
		for(j=0;j<n;j++)//nr de repetições para a nota 1/32
		{
			for(k=t_min;k!=0;k--) _delay_us(100);
		}
		//------------------------------------------------------------------- 
     	set_bit(TCCR1A,COM1A0);	//habilita o som

	}while(pgm_read_byte(&MUSICA[i++])==',');//enquanto não chegar ao final da música, continua lendo

    TCCR1A=0;		//desabilita o som e o TC1
	TCCR1B=0;
	//------------------------------------------------------------------------
	
	while(1){}		//laço infinito
}
//============================================================================
