//--------------------------------------------------------------------------------	//
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							//
//--------------------------------------------------------------------------------	//
//================================================================================	//
//      ACIONANDO UM DISPLAY DE CRISTAL LIQUIDO DE 16x2	 							//
//                               													//
//              Interface de dados de 8 bits 										//
//================================================================================	//
#define F_CPU 16000000UL		//define a frequência do microcontrolador - 16MHz

#include <avr/io.h> 			//definições do componente especificado
#include <util/delay.h>			//biblioteca para o uso das rotinas de delay
#include <avr/pgmspace.h>		//uso de funções para salvar dados na memória de programa

//Definições de macros - empregadas para o trabalho com o bits
#define	set_bit(Y,bit_x) (Y|=(1<<bit_x))	//ativa o bit x da variável Y
#define	clr_bit(Y,bit_x) (Y&=~(1<<bit_x))	//limpa o bit x da variável Y 
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))  	//testa o bit x da variável Y
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))	//troca o estado do bit x da variável Y 

//para uso no LCD
#define pulso_enable() _delay_us(1); set_bit(CONTR_LCD,E); _delay_us(1); clr_bit(CONTR_LCD,E); _delay_us(45)

#define DADOS_LCD 	PORTD   	//8 bits de dados do LCD na porta D  
#define CONTR_LCD 	PORTB		//os pinos de controle estão no PORTB
#define RS    		PB1     	//pino de instrução ou dado para o LCD
#define E     		PB0     	//pino de enable do LCD

//mensagem armazenada na memória flash
const unsigned char msg1[] PROGMEM = "ABCDEFGHIJKLMNOP"; 

//-----------------------------------------------------------------------------------
//Sub-rotina para enviar caracteres e comandos ao LCD
//-----------------------------------------------------------------------------------
void cmd_LCD(unsigned char c, char cd) //c é o dado  e cd indica se é instrução ou caractere
{
	DADOS_LCD = c; 

	if(cd==0)
		clr_bit(CONTR_LCD,RS);	//RS = 0
	else
		set_bit(CONTR_LCD,RS);	//RS = 1

	pulso_enable();

	//se for instrução de limpeza ou retorno de cursor espera o tempo necessário
	if((cd==0) && (c<4))	 
		_delay_ms(2);
}
//-----------------------------------------------------------------------------------
//Sub-rotina de inicialização do LCD - sequência ditada pelo fabricando do circuito de controle do LCD 	
//-----------------------------------------------------------------------------------
void inic_LCD_8bits()
{
	clr_bit(CONTR_LCD,RS);//o LCD será só escrito então R/W é sempre zero

	_delay_ms(15);		/*tempo para estabilizar a tensão do LCD, após VCC ultrapassar
						4.5 V (pode ser bem maior na prática)*/
		
	DADOS_LCD = 0x38;	//interface 8 bits, 2 linhas, matriz 7x5 pontos

	pulso_enable();		//enable respeitando os tempos de resposta do LCD
	_delay_ms(5);		
	pulso_enable();
	_delay_us(200);
	pulso_enable();
	pulso_enable();		

   	cmd_LCD(0x08,0);	//desliga LCD
   	cmd_LCD(0x01,0);	//limpa todo o display
   	cmd_LCD(0x0C,0);	//mensagem aparente cursor inativo não piscando   
   	cmd_LCD(0x80,0);	//escreve na primeira posição a esquerda - 1ª linha
}
//-----------------------------------------------------------------------------------
//Sub-rotina de escrita no LCD 
//-----------------------------------------------------------------------------------
void escreve_LCD(char *c)
{
   for (; *c!=0;c++) cmd_LCD(*c,1);
}
//-----------------------------------------------------------------------------------
int main()
{	
    unsigned char i;

	DDRB = 0xFF;		//PORTB como saída
    DDRD = 0xFF;		//PORTD como saída
	UCSR0B = 0x00;		//habilita os pinos PD0 e PD1 como I/O para uso no Arduino
	
	inic_LCD_8bits();	//inicializa o LCD

	for(i=0;i<16;i++)	//enviando caractere por caractere
		cmd_LCD(pgm_read_byte(&msg1[i]),1);	//lê na memória flash e usa cmd_LCD
    
	cmd_LCD(0xC0,0);	//desloca o cursor para a segunda linha do LCD
	escreve_LCD("QRSTUVXYZ 123456");//a cadeia de caracteres é criada na RAM
	
	for(;;);			//laço infinito
}
//===================================================================================
