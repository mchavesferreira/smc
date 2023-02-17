//--------------------------------------------------------------------------------	//
//		AVR e Arduino: T�cnicas de Projeto, 2a ed. - 2012.							//
//--------------------------------------------------------------------------------	//
//================================================================================	//
//      ACIONANDO UM DISPLAY DE CRISTAL LIQUIDO DE 16x2	 							//
//                               													//
//              Interface de dados de 8 bits 										//
//================================================================================	//
#define F_CPU 16000000UL		//define a frequ�ncia do microcontrolador - 16MHz

#include <avr/io.h> 			//defini��es do componente especificado
#include <util/delay.h>			//biblioteca para o uso das rotinas de delay
#include <avr/pgmspace.h>		//uso de fun��es para salvar dados na mem�ria de programa

//Defini��es de macros - empregadas para o trabalho com o bits
#define	set_bit(Y,bit_x) (Y|=(1<<bit_x))	//ativa o bit x da vari�vel Y
#define	clr_bit(Y,bit_x) (Y&=~(1<<bit_x))	//limpa o bit x da vari�vel Y 
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))  	//testa o bit x da vari�vel Y
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))	//troca o estado do bit x da vari�vel Y 

//para uso no LCD
#define pulso_enable() _delay_us(1); set_bit(CONTR_LCD,E); _delay_us(1); clr_bit(CONTR_LCD,E); _delay_us(45)

#define DADOS_LCD 	PORTD   	//8 bits de dados do LCD na porta D  
#define CONTR_LCD 	PORTB		//os pinos de controle est�o no PORTB
#define RS    		PB1     	//pino de instru��o ou dado para o LCD
#define E     		PB0     	//pino de enable do LCD

//mensagem armazenada na mem�ria flash
const unsigned char msg1[] PROGMEM = "ABCDEFGHIJKLMNOP"; 

//-----------------------------------------------------------------------------------
//Sub-rotina para enviar caracteres e comandos ao LCD
//-----------------------------------------------------------------------------------
void cmd_LCD(unsigned char c, char cd) //c � o dado  e cd indica se � instru��o ou caractere
{
	DADOS_LCD = c; 

	if(cd==0)
		clr_bit(CONTR_LCD,RS);	//RS = 0
	else
		set_bit(CONTR_LCD,RS);	//RS = 1

	pulso_enable();

	//se for instru��o de limpeza ou retorno de cursor espera o tempo necess�rio
	if((cd==0) && (c<4))	 
		_delay_ms(2);
}
//-----------------------------------------------------------------------------------
//Sub-rotina de inicializa��o do LCD - sequ�ncia ditada pelo fabricando do circuito de controle do LCD 	
//-----------------------------------------------------------------------------------
void inic_LCD_8bits()
{
	clr_bit(CONTR_LCD,RS);//o LCD ser� s� escrito ent�o R/W � sempre zero

	_delay_ms(15);		/*tempo para estabilizar a tens�o do LCD, ap�s VCC ultrapassar
						4.5 V (pode ser bem maior na pr�tica)*/
		
	DADOS_LCD = 0x38;	//interface 8 bits, 2 linhas, matriz 7x5 pontos

	pulso_enable();		//enable respeitando os tempos de resposta do LCD
	_delay_ms(5);		
	pulso_enable();
	_delay_us(200);
	pulso_enable();
	pulso_enable();		

   	cmd_LCD(0x08,0);	//desliga LCD
   	cmd_LCD(0x01,0);	//limpa todo o display
   	cmd_LCD(0x0C,0);	//mensagem aparente cursor inativo n�o piscando   
   	cmd_LCD(0x80,0);	//escreve na primeira posi��o a esquerda - 1� linha
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

	DDRB = 0xFF;		//PORTB como sa�da
    DDRD = 0xFF;		//PORTD como sa�da
	UCSR0B = 0x00;		//habilita os pinos PD0 e PD1 como I/O para uso no Arduino
	
	inic_LCD_8bits();	//inicializa o LCD

	for(i=0;i<16;i++)	//enviando caractere por caractere
		cmd_LCD(pgm_read_byte(&msg1[i]),1);	//l� na mem�ria flash e usa cmd_LCD
    
	cmd_LCD(0xC0,0);	//desloca o cursor para a segunda linha do LCD
	escreve_LCD("QRSTUVXYZ 123456");//a cadeia de caracteres � criada na RAM
	
	for(;;);			//la�o infinito
}
//===================================================================================
