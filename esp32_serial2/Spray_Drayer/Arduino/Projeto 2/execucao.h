
#ifndef EXECUCAO_H_
#define EXECUCAO_H_
#include "ads1115.h"



unsigned char  estado=0;	    //declara variavel global
unsigned int cont =0, control=0, i=2, teste=0, pausa=0,c=0;
unsigned char  temperatura_t[4], Rotacao_t[4] , nivel_t[2], tempo =0, var=0, var_1=0,var_2, num; // declara as variaveis definidas no projeto
unsigned char digitos[tam_vetor];	 //declaracao da variável para armazenagem dos digitos
unsigned int valorbinario;
unsigned int temperatura, Rotacao, nivel;
long valortemp=0;


int convert();
void serial_print();


//descricao dos pinos I/O
// ENTRADAS
#define botao_manut PC4   


//SAIDAS
#define ligar PB0       // funcionamento da maquina
#define valvula_1 PB1  // indicador de enchendo e cheio
#define motor PB2      //  funcionamento do motor
#define valvula_3 PC1 //   indicador do funcionamento da ventilação
#define emergencia PC3 //  indicador de emergencia
#define desligar  PB5 //  indicador do produto final

void inicio();
void produto();
void padrao();
void temp_produto();
void rot_produto();
void nivel_produto();
void enchendo();
void cheio();
void aquecimento();
void aciona_motor();
void desliga_motor();
void queda_rot();
void desliga_ventilacao();
void produto_final();
void reiniciar();

void set_pwm_pb3(unsigned int valor)  // timer 2
{
	TCCR2A |=  (1<< COM2A1) | (1 << WGM21) | (1<<WGM20);
	TCCR2B =  0b00100111;
	OCR2A=valor;
}
void clr_pwm_pb3()  // timer 2
{
	TCCR2A =  (0<< COM2A1) | (1 << WGM21) | (1<<WGM20);
	TCCR2B =  0b00100111;
	OCR2A=0;
}

void inicio()  // inicio do programa
{
	set_bit(PORTB, desligar);
	unsigned char start1 = USART_Recebe();
	if (start1 =='S') {
		clr_bit(PORTB, desligar);
		set_bit(PORTB,ligar);
		estado=1;
	}
	else
	{
		estado =0;
	}
}
void produto()   // escolha do tipo de produto
{
	unsigned char prod1 = USART_Recebe();
	if (prod1 == 'P') {
		unsigned char prod2 = USART_Recebe();
		if (prod2 == '1') { // ovo
			i=2;
			c=10;
			estado=2;
		}
		else if (prod2 == '2') { // cafe
			i=3;
			c=100;
			estado=2;
		}
		else if (prod2 == '3') { // leite
			i=4;
			c=200;
			estado=2;
		}
		else if (prod2 == '4') { // outro
			i=5;
			c=40;
			estado=2;
		}
	}
}
void padrao()   // verificação se vai utilzar o ajuste padrão do produto
{
	unsigned char aj1 = USART_Recebe();
	if (aj1 == 'N')  // caso negativo
	{
		estado=3;
		teste =0;
	}
	else if (aj1 == 'Y') // caso positivo
	{
		if (i==2) // ovo
		{
			temperatura = 80;
			Rotacao = 150;
			estado =3;
			teste=1;
			
		}
		if (i==3) // cafe
		{
			temperatura =100 ;
			Rotacao = 200;
			estado =3;
			teste=1;
			
		}
		else // leite
		{
			temperatura = 50 ;
			Rotacao = 100 ;
			estado =3;
			teste=1;
		}
		
		
		
	}
	
}
void nivel_produto() // definição do nivel do produto
{
	unsigned char N1 = USART_Recebe();
	if (N1 == 'N'){
		unsigned char N2 = USART_Recebe();
		if (N2 == 'I'){
			nivel_t[0] = USART_Recebe();
			nivel_t[1] = '\0';
			nivel = (unsigned int) convert(nivel_t); // converte o vetor em um valor inteiro
			if (teste==0)  // verifica se o ajuste padrão não foi selecionado
			{
					estado=4;
			}
			else
			{
				estado=6;
			}
			
		}
	}
	
}
void temp_produto() // definição d a temperatura
{
	unsigned char T1 = USART_Recebe();
	if (T1 == 'T'){
		temperatura_t[0] = USART_Recebe();
		temperatura_t[1] = USART_Recebe();
		temperatura_t[2] = USART_Recebe();
		temperatura_t[3] = '\0';
		temperatura=(unsigned int) convert(temperatura_t);
		if (temperatura !=0)
		{
			estado=5;
		}
	}

}
void rot_produto() // definição da rotação
{
	unsigned char R1 = USART_Recebe();
	if (R1 == 'R'){
		Rotacao_t[0] = USART_Recebe();
		Rotacao_t[1] = USART_Recebe();
		Rotacao_t[2] = USART_Recebe();
		Rotacao_t[3] = '\0';
		Rotacao = (unsigned int) convert(Rotacao_t);
		var_2 = Rotacao;
		if (Rotacao != 0)
		{
			estado=6;
		}
	}
	
}

void enchendo() // em processo
{
		set_bit(PORTB,valvula_1);
		estado=7;
		tempo=nivel;

}
void cheio() // em processo
{
	if(!tempo) // verifica se é igual 1
	{
		clr_bit(PORTB,valvula_1);
		if (valortemp>0)
		{
			valortemp =0;
		}
		estado=8;
	}
}

void aquecimento() // leitura analogia para a temperatura
{
	valorbinario = ads1115_readADC_SingleEnded(0x48, 0,DATARATE_128SPS, FSR_4_096);
	valortemp = ( (long) valorbinario * 250) /32767;
	//char buffer[20];
	//snprintf(buffer, sizeof(buffer), "%ld\n", valortemp);
	//serial_print(buffer);

	if(valortemp<temperatura)
	{
		estado =8;
		
	}
	if(valortemp>temperatura)
	{
		set_bit(PORTC,valvula_3);
		estado =9;
		tempo =(Rotacao/50);
	}
	_delay_ms(200);
}
void aciona_motor()
{ 
	
	if(!tempo)
	{
	    set_bit(PORTB,motor);
		estado =10;
	}
	
}
void desliga_motor()
{
	
	unsigned char des1 = USART_Recebe();
	if (des1 == 'D') {
		unsigned char des2 = USART_Recebe();
		if (des2 == 'M') {
			clr_bit(PORTB,motor);
			estado=11;
			tempo =(Rotacao/50);
		}
	}
	
}
void queda_rot()
{
	if(!tempo)
	{
			estado=12;
			tempo=2;
	}
	
}
void desliga_ventilacao()
{
	clr_bit(PORTC,valvula_3);
	if(!tempo)
	{
		estado=13;
	}
	
	
}
void produto_final()
{
	set_pwm_pb3(c);
	unsigned char p1 = USART_Recebe();
	if (p1 == 'P') {
		unsigned char p2 = USART_Recebe();
		if (p2 == 'F') {
			estado =14;
			
			tempo = 2;
		}
	}
}
void reiniciar()
{
	clr_pwm_pb3(0);
	if(!tempo)
	{
		estado=0;
		teste=0;
		valortemp=0;
		clr_bit(PORTB, ligar);
		set_bit(PORTB, desligar);
		
	}
	
}


#endif /* EXECUCAO_H_ */