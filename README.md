Sistemas Microcontrolados

## Utilizando Atmega328P para a compreensão e funcionamento de microprocessadores e microcontroladores em geral utilizando a linguagem C.

## Sumário

- [Simulação online para microcontrolador](#Simulação-online-para-microcontrolador)
- [Ambiente de programação](#Ambiente-de-programação)
- [Primeiro Programa em C](#Primeiro-Programa-em-C)
- [Lendo Botão](#Lendo-Botão)
- [Utilizando Macros](#Utilizando-Macros)
- [Display LCD](#Display-LCD)
- [Máquina de estados](#Maquina-de-estados)
- [Interrupção Externa] (#Interrupção-Externa)
- [Temporizador, interrução e PWM] (#PWM-Timer-1)
- [Comunicação Serial](#UART)
- [Links e referências](#Links-e-referências)

Avaliação da Disciplina:

17/03/2023   - Tarefa Suap - Cronometro Big Number em LCD simulado em wokwi e/ou proteus

24/03/2023   - Tarefa Suap - Maquina de Lavar com delay simulado em wokwi e/ou proteus

31/03/2023   - Tarefa Suap - Maquina de Lavar com Timers simulado em wokwi e/ou proteus

05/05/2023  - Projeto 1: Protótipo em protoboard do projeto 1

05/05/2023  - Avaliação Presencial escrita (Sorteio de um projeto em dupla)


Junho/23  - Projeto 2 - Data a ser divulgada

Junho/23  - Avaliação 2.  Data a ser divulgada

Orientações para Projeto 1:

Utilizando o projeto inicial da <a href=https://wokwi.com/projects/350144439208903252>maquina de lavar</a>, crie uma máquina personalizada (não será considerado máquina de lavar) que atenda os seguintes critérios:

- apresente no mínimo 05 perguntas entre (sim x não) ou ajustes de valores (exemplo tempo);
- ajustes de pelo menos 03 valores inteiros;
- transições das etapas em máquina de estdos;
- utilize pelo menos 03 leds como saídas;
- as perguntas e respostas devem utilizar display LCD e botões (exemplos para botões: + - 1 2 3 Y N enter) (2,0 pontos)
-  enviar o código e link de simulação na área trabalhos (suap), um integrante da dupla.
- As duplas não podem ter trabalhos "clones", criatividade e dificuldades serão pontuados


Orientações para Projeto 2:
Aperfeiçoamento do projeto 1 ou uma nova proposta. Acrescentar novos recursos de programação e hardware; PWM, Conversor AD externo I2C (ADS1115), comunicação serial com ESP32 (wifi), memorização de parametros em eeprom, tela OLED I2C.

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

Exemplos de utilização do LCD 16x2 disponiveis na bibliografia
http://github.com/mchavesferreira/smc/ > Programas_livro > LCD_4bits

Exemplo de criação de caracteres especiais para LCD 16x2 

Big Number:  https://wokwi.com/projects/358831286702363649

## Maquina de estados 

Compreendendo a mudança de fluxo por meio da chamada de switch-case

https://wokwi.com/projects/358828863218714625

Este exemplo online exemplifica a aplicação da máquina de estados através de um programa para máquina de lavar.

https://wokwi.com/projects/350144439208903252



## Interrupção Externa

Exemplo com interrupção externa

Programas_livro/INT0_1/ 


https://wokwi.com/projects/359476742621416449




## PWM Timer 1

Aula 24/03 - Prática de interrução

Baixe o <a href=https://github.com/mchavesferreira/smc/blob/main/interrupcao_timers/funcoes_timer.zip> interrupcao_timers/funcoes_timer.zip</a>  com simulação em proteus.

Arquivos timer 1: <a href=https://github.com/mchavesferreira/smc/tree/main/interrupcao_timers/timer1_aula24>timer1_aula24</a>

Contador de eventos externos: <a href=https://github.com/mchavesferreira/smc/blob/main/interrupcao_timers/contador_eventos_TC1_C.zip>interrupcao_timers/contador_eventos_TC1_C.zip</a>

## UART

Comuniação Serial
https://github.com/mchavesferreira/smc/blob/main/serialAVR/

Exemplo com menu:
https://github.com/mchavesferreira/smc/blob/main/serialAVR/main_usart_menu.c
https://wokwi.com/projects/365174034245894145   Simulação

Utilize o exemplo da maquina de lavar para mostrar mensagens no LCD interagindo com a comunicação serial.
https://wokwi.com/projects/350144439208903252

<BR><img src=https://raw.githubusercontent.com/mchavesferreira/smc/main/imagens/mensagem.jpg><BR>
Criando graficos para exibição na uart<Br>
```java
const char msg1 [] PROGMEM = " CONTROLANDO LEDs COM O COMPUTADOR\0";
const char msg2 [] PROGMEM = " LEDS ON -> 1, 2, 3, 4, LEDS OFF -> 5, 6, 7, 8\0";
const char msg3 [] PROGMEM = " _ _ \0";
const char msg4 [] PROGMEM = " ---\\/--- |_| \\ / |_| ---\\/---\0";
const char msg5 [] PROGMEM = " ---/\\--- | | \\/ | \\ ---/\\---\0";
```
	
## Links e referências

Introdução a Linguagem C.
https://github.com/misaelrezende/Exercicios-do-Livro-Linguagem-C-Completa-e-Descomplicada

https://github.com/daniel-oliv3/Introducao-a-Programacao_500-Algoritmos-Resolvidos-Por-Lopes-Garcia
Introducao-a-Programacao_500-Algoritmos-Resolvidos-Por-Lopes-Garcia 


https://github.com/Franzininho/exemplos-avr-libc/tree/main/exemplos

https://embarcados.com.br/franzininho-diy-contador-de-pulsos-externos/

