Sistemas Microcontrolados

## Utilizando Atmega328P para a compreensão e funcionamento de microprocessadores e microcontroladores em geral utilizando a linguagem C.

## Sumário

- [Simulação online para microcontrolador](#Simulação-online-para-microcontrolador)
- [Ambiente de programação](#Ambiente-de-programação)
- [Primeiro Programa em C](#Primeiro-Programa-em-C)
- [Lendo Botão](#Lendo-Botão)
- [Utilizando Macros](#Utilizando-Macros)
- [Display LCD](#Display-LCD)
- [Máquina de estados](#Máquina-de-estados)
- [Links e referências](#Links-e-referências)

## Simulação online para microcontrolador



https://wokwi.com/projects/356295365780235265

##  Ambiente de programação


Avr Studio 7.0
http://studio.download.atmel.com/7.0.2389/as-installer-7.0.2389-full.exe

## Primeiro-Programa-em-C

Este primeiro exemplo de programa com um pisca Led

Código para o primeiro programa
```java

#define F_CPU 16000000UL // Clock frequency, needed to delay functions
#include <avr/io.h> // Register definitions
#include <util/delay.h> // Delay functions

int main(){
  DDRB |= (1<<PB5); // Define PORTB5 as an output
  while(1){ // Infinite loop
  PORTB |= (1<<PB5); // Turn led on
  _delay_ms(1000); // Wait 1 second
   PORTB &= ~(1<<PB5); // Turn led off
  _delay_ms(1000); // Wait another second
  }
return 0;
}
```

## Utilizando Macros

Conhecendo o recurso de Macros do compilador para simplificar o código

```java
#define F_CPU 16000000UL	//define a frequ�ncia do microcontrolador 16MHz (necess�rio para usar as rotinas de atraso)
#include <avr/io.h> 	    //defini��es do componente especificado
#include <util/delay.h>		//biblioteca para o uso das rotinas de _delay_ms() e _delay_us()

//Definicoeses de macros - empregadas para o trabalho com os bits de uma vari�vel ou registrador

#define	set_bit(Y,bit_x) (Y|=(1<<bit_x))	//ativa o bit x da vari�vel Y (coloca em 1)
#define	clr_bit(Y,bit_x) (Y&=~(1<<bit_x))	//limpa o bit x da vari�vel Y (coloca em 0) 
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))  	//testa o bit x da vari�vel Y (retorna 0 ou 1)
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))	//troca o estado do bit x da vari�vel Y (complementa)

#define LED PB5				//LED � o substituto de PB5 na programa��o     	

//--------------------------------------------------------------------------------------
int main( )
{
    DDRB = 0xFF;			//configura todos os pinos do PORTB como sa�das
	
	while(1)				//la�o infinito
    {
        set_bit(PORTB,LED);	//liga LED
		_delay_ms(200);		//atraso de 200 ms
		clr_bit(PORTB,LED);	//desliga LED
		_delay_ms(200);		//atraso de 200 ms
    }
}

```


## Lendo Botão

```java

//=====================================================================================	//
//    LIGANDO E DESLIGANDO UM LED QUANDO UM BOT�O � PRESSIONADO							//
//===================================================================================== //
#define F_CPU 16000000UL	/*define a frequ�ncia do microcontrolador 16MHz (necess�rio
							para usar as rotinas de atraso)*/
#include <avr/io.h> 	    //defini��es do componente especificado
#include <util/delay.h>		//biblioteca para as rotinas de _delay_ms() e delay_us()

//Defini��es de macros - para o trabalho com os bits de uma vari�vel

#define set_bit(Y,bit_x)(Y|=(1<<bit_x))		//ativa o bit x da vari�vel Y (coloca em 1)
#define clr_bit(Y,bit_x)(Y&=~(1<<bit_x))	//limpa o bit x da vari�vel Y (coloca em 0) 
#define cpl_bit(Y,bit_x)(Y^=(1<<bit_x))		//troca o estado do bit x da vari�vel Y 
#define tst_bit(Y,bit_x)(Y&(1<<bit_x))  	//testa o bit x da vari�vel Y (retorna 0 ou 1)

#define LED   PD2   //LED � o substituto de PD2 na programa��o 
#define BOTAO PD7   //BOTAO � o substituto de PD7 na programa��o     	
//-------------------------------------------------------------------------------------
int main()
{
	DDRD = 0b00000100;	//configura o PORTD, PD2 sa�da, os demais pinos entradas
	PORTD= 0b11111111;	/*habilita o pull-up para o bot�o e apaga o LED (todas as 
						entradas com pull-ups habilitados)*/
	
	while(1)								//la�o infinito
	{
		if(!tst_bit(PIND,BOTAO))			//se o bot�o for pressionado executa o if
		{					
			while(!tst_bit(PIND,BOTAO));	//fica preso at� soltar o bot�o

			_delay_ms(10);					//atraso de 10 ms para eliminar o ru�do do bot�o

			if(tst_bit(PORTD,LED))			//se o LED estiver apagado, liga o LED
				clr_bit(PORTD,LED);			
			else							//se n�o apaga o LED
				set_bit(PORTD,LED);	

			//o comando cpl_bit(PORTD,LED) pode substituir este la�o if-else
		
		}//if do bot�o pressionado
	
	}//la�o infinito
}
```
## Display LCD

## Máquina de estados 

Este exemplo online exemplifica a aplicação da máquina de estados através de um programa para máquina de lavar.

https://wokwi.com/projects/350144439208903252



## Links e referências

Introdução a Linguagem C.
https://github.com/misaelrezende/Exercicios-do-Livro-Linguagem-C-Completa-e-Descomplicada

https://github.com/daniel-oliv3/Introducao-a-Programacao_500-Algoritmos-Resolvidos-Por-Lopes-Garcia
Introducao-a-Programacao_500-Algoritmos-Resolvidos-Por-Lopes-Garcia 


https://github.com/Franzininho/exemplos-avr-libc/tree/main/exemplos

https://embarcados.com.br/franzininho-diy-contador-de-pulsos-externos/

