Sistemas Microcontrolados

## Utilizando Atmega328P para a compreensão e funcionamento de microprocessadores e microcontroladores em geral utilizando a linguagem C.

ChatGPT:   https://chatgpt.com/g/g-TFvuISQH5-professor-dos-embarcados

## Sumário

- [Simulação online para microcontrolador](#Simulação-online-para-microcontrolador)
- [Ambiente de programação](#Ambiente-de-programação)
- [Primeiro Programa em C](#Primeiro-Programa-em-C)
- [Lendo Botão](#Lendo-Botão)
- [Utilizando Macros](#Utilizando-Macros)
- [Máquina de estados](#Maquina-de-estados)
- <a href=https://github.com/mchavesferreira/smc/blob/main/display7segmentos.md>Display de 7 segmentos</a>
- <a href=https://github.com/mchavesferreira/smc/blob/main/displaylcd.md>Display LCD</a>
- [Exemplo Maquina de Lavar ](#Exemplo-Maquina-de-Lavar )
- [Trabalhos-Turma-2024](#Trabalhos-Turma-2024)
- <a href=https://github.com/mchavesferreira/smc/tree/main/interrupcao_timers#readme>Interrupções</a>
- [Comunicação Serial](#UART)
- <a href=https://github.com/mchavesferreira/smc/tree/main/conversorADavr>Conversor AD</a>
- <a href=https://github.com/mchavesferreira/smc/tree/main/comunicacaoI2C>Comunicação I2C</a>
- <a href=https://github.com/mchavesferreira/mcr/blob/main/ESP32.md>ESP32 Introdução</a>
- <a href=https://github.com/mchavesferreira/smc/tree/main/esp32_serial2>ESP32 Iot e Webserver</a>
- [Links e referências](#Links-e-referências)


Avaliação da Disciplina:



## Aula 14/02/2025

- Apresentação da disciplina, histórico de microprocessadores, avaliação
- Material SUAP: SMC _ Cap 1 Introdução aos Sistemas Embarcados _Rodrigo Maximiano.pdf
  

## Aula 21/02/2025

- Introdução a linguagem C, Variáveis, diretivas de compilação, comentários - https://github.com/mchavesferreira/smc/tree/main/linguagemc,  Material SUAP SMC _ Cap 3 Linguagem C_Rodrigo_Maximiano



## Aula 28/02/2025

- Protótipo de funções, função main, operadores, Material SUAP SMC _ Cap 3 Linguagem C_Rodrigo_Maximiano
  
- Variáveis, tipos básicos, typecast, modificadores de acesso, persistência, ponteiros s - Material SUAP: SMC _ SMC _ Cap 4 Variaveis_Rodrigo_Maximiano

Exercício: ex2_modificadores.c, ex2_precisaovariaveis.c, Ex4.c e Ex5.c
  
- Variáveis e estruturas - Material SUAP:  SMC _ Cap 5 Variáveis e estruturas_Rodrigo_Maximiano

Exercício: Ex3.c

## Aula 07/03/2025

-  Operadores binários - Material SUAP: SMC _ Cap 6 Operadores Binarios_Rodrigo Maximiano
-  Ambiente de programação
-  Primeiro Programa em C
-  Utilizando Macros
  
Avr Studio 7.0
http://studio.download.atmel.com/7.0.2389/as-installer-7.0.2389-full.exe

## Primeiro-Programa-em-C

#### Pisca Led
Este primeiro exemplo de programa com um pisca Led

<img src=imagens/piscaled.png>

### Pinagem
Atmega328P
<img src=https://github.com/mchavesferreira/mcr/blob/main/imagens/pinout_atmega328P.png>

<img src=https://github.com/mchavesferreira/smc/assets/63993080/9310c6ec-f83e-40e3-968e-5a459110fd48)>

### Código para o primeiro programa
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

#define LED PB5				//LED é o substituto de PB5 na programação     	

//--------------------------------------------------------------------------------------
int main( )
{
    DDRB = 0xFF;			//configura todos os pinos do PORTB como sa�das
	
	while(1)				//laço infinito
    {
        set_bit(PORTB,LED);	//liga LED
		_delay_ms(200);		//atraso de 200 ms
		clr_bit(PORTB,LED);	//desliga LED
		_delay_ms(200);		//atraso de 200 ms
    }
}

```

## Aula 14/03/2024

Programação prática com pinos em modo Entrada, uso de botões e máquina de estados

## Lendo Botão

A técnica de debounce, ou "debouncing", é utilizada para mitigar o efeito de "rebote" que ocorre quando um botão (ou chave) é pressionado ou liberado.

<img src=imagens/ruido.png>

<img src=imagens/ledbotao.png>

```java

//=====================================================================================	//
//    LIGANDO E DESLIGANDO UM LED QUANDO UM BOTaO e PRESSIONADO							//
//===================================================================================== //
#define F_CPU 16000000UL	/*define a frequ�ncia do microcontrolador 16MHz (necess�rio
							para usar as rotinas de atraso)*/
#include <avr/io.h> 	    //definicoes do componente especificado
#include <util/delay.h>		//biblioteca para as rotinas de _delay_ms() e delay_us()

//Definicoes de macros - para o trabalho com os bits de uma variavel

#define set_bit(Y,bit_x)(Y|=(1<<bit_x))		//ativa o bit x da variavel Y (coloca em 1)
#define clr_bit(Y,bit_x)(Y&=~(1<<bit_x))	//limpa o bit x da variavel Y (coloca em 0) 
#define cpl_bit(Y,bit_x)(Y^=(1<<bit_x))		//troca o estado do bit x da variavel Y 
#define tst_bit(Y,bit_x)(Y&(1<<bit_x))  	//testa o bit x da variavel Y (retorna 0 ou 1)

#define LED   PD2   //LED e o substituto de PD2 na programacao
#define LEDPISCA   PD3   //LED e o substituto de PD2 na programacao 

#define BOTAO PD7   //BOTAO e o substituto de PD7 na programacao     	
//-------------------------------------------------------------------------------------
int main()
{
        unsigned int contador=0;
	DDRD = 0b00000100;	//configura o PORTD, PD2 saida, os demais pinos entradas
	PORTD= 0b11111111;	/*habilita o pull-up para o botao e apaga o LED (todas as 
						entradas com pull-ups habilitados)*/
	while(1)								//laco infinito
	{
                //////// pisca led
                contador++;
                _delay_ms(1);		
                if(contador>500) {  contador=0; cpl_bit(PORTD,LEDPISCA);   }
                //////// pisca led

		if(!tst_bit(PIND,BOTAO))			//se o botao for pressionado executa o if
		{					
			while(!tst_bit(PIND,BOTAO));	//fica preso ate soltar o botao
			_delay_ms(10);					//atraso de 10 ms para eliminar o ruido do botao
			if(tst_bit(PORTD,LED))			//se o LED estiver apagado, liga o LED
				clr_bit(PORTD,LED);			
			else							//se nao apaga o LED
				set_bit(PORTD,LED);	
			//o comando cpl_bit(PORTD,LED) pode substituir este laco if-else	
		}//if do botao pressionado
	}//laco infinito
}
```

## Aula 21/03/2025

### Display 7 segmentos

<a href=https://github.com/mchavesferreira/smc/blob/main/display7segmentos.md>Exemplo display 7 segmentos</a>

###  Display LCD

<a href=https://github.com/mchavesferreira/smc/blob/main/displaylcd.md>Exemplo LCD</a>


### Maquina de estados 

![image](https://github.com/mchavesferreira/smc/assets/63993080/3765f170-1abe-4377-89a2-41d980c8b771)

### Switch-case

A estrutura switch-case é uma técnica eficaz para implementar máquinas de estados em programação de microcontroladores, facilitando o controle de fluxo do programa com base nos valores de uma variável. Aqui está um exemplo simplificado utilizando em uma função:
```java
// Exemplo de máquina de estados usando switch-case
void stateMachineExample(int state) {
    switch(state) {
        case 1:
            // Ação para o estado 1
            break;
        case 2:
            // Ação para o estado 2
            break;
        // Adicione mais estados conforme necessário
        default:
            // Ação padrão se nenhum estado anterior corresponder
            break;
    }
}
```
Este exemplo demonstra a base de uma máquina de estados, onde state determina o fluxo de execução. Cada case representa um estado único, permitindo ações específicas para cada um, e o default oferece uma ação padrão para estados não especificados. Esta abordagem organiza logicamente o código, tornando-o mais legível e fácil de manter.

Compreendendo a mudança de fluxo por meio da chamada de switch-case em um programa principal:

https://wokwi.com/projects/358828863218714625



## Aula 21/03/2025




## Simulação online para microcontrolador

Existem simuladores online, na seção a seguir apresentamos alguns:

### Wokwi 

Um simulador online muito popular para Arduino e outros microcontroladores. Ele suporta uma variedade de placas Arduino (que são baseadas em microcontroladores de 8 bits) e permite simular circuitos eletrônicos junto com o código. É uma ótima ferramenta para ensinar os conceitos de programação em C junto com a eletrônica básica.
 - Exemplo 1:   https://wokwi.com/projects/356295365780235265
 - Exemplo 2:   https://wokwi.com/projects/363128065545249793
    
-Tinkercad Circuits - Tinkercad, da Autodesk, oferece um simulador de Arduino que funciona diretamente no navegador. Ele permite aos usuários montar circuitos e escrever código para eles, tudo em uma interface gráfica amigável. É particularmente bom para iniciantes.

-Proteus - Embora não seja totalmente online, o Proteus Design Suite oferece recursos de simulação poderosos para uma ampla gama de microcontroladores. Seus estudantes podem escrever código em C, simular o funcionamento do microcontrolador e testar circuitos eletrônicos em um ambiente virtual.

-EasyEDA - Outra ferramenta que, embora seja mais focada no design de circuitos eletrônicos, também oferece suporte à simulação de microcontroladores, incluindo a escrita e teste de códigos em C.

-CircuitJS - Este é um simulador de circuitos eletrônicos baseado em JavaScript que roda diretamente no navegador. Embora seu foco principal não seja microcontroladores, ele pode ser útil para ensinar os princípios básicos de eletrônica que são relevantes para a engenharia de automação.







     
### Exemplo de um programa para controle de uma caixa d'agua.

<BR>Defina pinos de entrada e saída. As entradas com push button aterradas e  pull up ativos. O Programa aguarda “Start” ser pressionado, que liga a  Valvula 1 até que sensor cheio seja acionado. O misturador é acionado  por2 segundos. Esvazia-se o tanque até o sensor vazio ser acionado, retornando ao estado inicial. Considere clock 16Mhz.
<br><BR>**Solução:**
<br>Para que servem e quais são os registradores de I/O de um AVR Atmega?  Os registradores de IO  funcionam para configurar, ler e escrever cada  pino das portas  do microcontrolador, cada bit representa um pino:  DDRx  quando em 0=entrada e 1=saída. PINx para a leitura do pino quando este é  definido com entrada; PORTx escreve na saída se o pino é definido como  saída ou ativa pull-up se o pino é definido como entrada.
	<Br>

<details><summary>Exemplo em assembly</summary>
<p>

```ruby  
.ORG 0x000				
INICIO:
     LDI R19, 0b00000111	//carrega R19 
     OUT DDRB,R19		//configura todos os pinos
     LDI R19, 0b00111000
     OUT PORTB, R19
; aguarda botao start
PRINCIPAL:      
     SBIC PINB,5		
     RJMP Principal
     RJMP ENCHER
; Liga válvula aguarda sensor cheio
ENCHER:
    SBI PORTB,0
    SBIC PINB,3
    RJMP ENCHER
    RJMP MISTURAR

; desliga V1, liga misturador por 2 seg. 
MISTURAR:
    CBI PORTB,0
    SBI PORTB,2
    RCALL ATRASO 
    RCALL ATRASO 
    CBI PORTB, 2
    RJMP ESVAZIAR

; Liga válvula 2 aguarda sensor vazio
ESVAZIAR:
    SBI PORTB,1
    SBIC PINB,4
    RJMP ESVAZIAR
    CBI PORTB,1
    RJMP PRINCIPAL
; .  .    .   .    .    .    .    .   .     .   
; rotina de atraso 1 segundo. 
ATRASO:	
      LDI R19,80	
volta:		
      DEC  R17	
      BRNE volta
      DEC  R18	
      BRNE volta
      DEC  R19
      BRNE volta
      RET
```
</p>
</details> 





## Exemplo Maquina de Lavar 

Este exemplo online exemplifica a aplicação da máquina de estados e uso do LCD através de um programa para máquina de lavar.

https://wokwi.com/projects/350144439208903252








## Interrupções

Saima mais sobre Interrupções: https://github.com/mchavesferreira/smc/tree/main/interrupcao_timers

## UART

Comuniação Serial
https://github.com/mchavesferreira/smc/blob/main/serialAVR/

Comunicação Serial (ESP32)
https://github.com/mchavesferreira/mcr/blob/main/esp32/serialprint.md

Exemplo com menu:
https://github.com/mchavesferreira/smc/blob/main/serialAVR/main_usart_menu.c <BR>
https://wokwi.com/projects/365174034245894145   Simulação

![image](https://github.com/mchavesferreira/smc/assets/63993080/9b5c31a2-7060-45b2-ad95-73ccb14e9c3c)
Blocos do UAR

Registradores:

UBRRn - A taxa de transmissão (baud rate) é calculada com base na frequência do clock 

UDR0 – USART I/O Data Register

UCSR0A 

UCSR0B 

UCSR0C 

Bibliotecas:

<details><summary>UARTC.c</summary>
	
```ruby  
//=============================================================================	//
//		Funções para trabalhalho com a USART									//
//=============================================================================	//

#include "USART.h"


//---------------------------------------------------------------------------
void USART_Inic(unsigned int ubrr0)
{
	UBRR0H = (unsigned char)(ubrr0>>8);	//Ajusta a taxa de transmissão
	UBRR0L = (unsigned char)ubrr0;

	UCSR0A = 0;//desabilitar velocidade dupla (no Arduino é habilitado por padrão)
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //Habilita a transmissão e a recepção
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);/*modo assíncrono, 8 bits de dados, 1 bit de parada, sem paridade*/
}
//---------------------------------------------------------------------------
void USART_Transmite(unsigned char dado)
{
	while (!( UCSR0A & (1<<UDRE0)) );	//espera o dado ser enviado
	UDR0 = dado; 					//envia o dado
}
//---------------------------------------------------------------------------
unsigned char USART_Recebe()
{
	while (!(UCSR0A & (1<<RXC0)));	//espera o dado ser recebido
	return UDR0; 				//retorna o dado recebido
}
//---------------------------------------------------------------------------
void escreve_USART(char *c)		//escreve String (RAM)
{
   for (; *c!=0;c++) USART_Transmite(*c);
}
//---------------------------------------------------------------------------
void escreve_USART_Flash(const char *c)	//escreve String (Flash)
{
   for (;pgm_read_byte(&(*c))!=0;c++) USART_Transmite(pgm_read_byte(&(*c)));
}
//---------------------------------------------------------------------------	
//Conversão de um número em seus digitos individuais
//---------------------------------------------------------------------------
void ident_num(unsigned int valor, unsigned char *disp)
{   
 	unsigned char n;

	for(n=0; n<tam_vetor; n++)
		disp[n] = 0 + conv_ascii;	//limpa vetor para armazenagem dos digitos 

	do
	{
       *disp = (valor%10) + conv_ascii;	//pega o resto da divisao por 10 
	   valor /=10;		//pega o inteiro da divisão por 10
	   disp++;

	}while (valor!=0);
}
//------------------------------------------------------------------------------
```
</details>

<details><summary>UART.h</summary>
	
```ruby 
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
```
</details>

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
	
Criando figuras:
```java	
serialTransmit('   *   \n');
serialTransmit('  ***  \n');
serialTransmit(' ***** \n');
serialTransmit('*******\n');
serialTransmit(' ***** \n');
serialTransmit('  ***  \n');
serialTransmit('   *   \n');
```	

### Exemplo analisando uma combinação com iniciais "FA"
<BR>https://wokwi.com/projects/365183451516854273
	
	
### Exemplo recebe "LEDOF1"  e "LEDON1" através da porta serial e acende ou apaga um led.
<BR>https://wokwi.com/projects/365185955727181825

### Cocatenar variáveis e frases (stream)

No C, um "stream" é uma sequência de dados que pode ser lida ou escrita de forma contínua. Quando falamos de streams no contexto de microcontroladores, estamos frequentemente nos referindo ao uso de buffers e funções para manipulação de strings para formar mensagens que podem ser exibidas em um LCD ou enviadas via comunicação serial.

#### Concatenando Variáveis e Frases

Para concatenar variáveis e frases, usamos principalmente funções da biblioteca <stdio.h> e <string.h>.
Funções Comuns para Manipulação de Strings

    sprintf: Formata uma string e armazena o resultado em um buffer.
    strcat: Concatena duas strings.
    strcpy: Copia uma string para outra
    
#### Exemplo com sprintf
Aqui está um exemplo de como usar sprintf para formatar uma mensagem que inclui variáveis e strings fixas, e então enviar essa mensagem via comunicação serial.

```java	
char serial_buffer[20];
sprintf(serial_buffer,"* Opção %c selecionada ",option);  //%d  %f formatos das variáveis
escreve_USART(serial_buffer);
```

Exemplo:  https://wokwi.com/projects/365174034245894145

## ESP32 e suas aplicações IOT

https://github.com/mchavesferreira/mcr/blob/main/ESP32.md


# Aula 13/06/2025

Exemplos de Bridge ESP32 <>UNO


Codigo exemplo trabalho 2

https://github.com/mchavesferreira/smc/tree/main/exemplotrabalho2

Pagina interativa com controle de eventos

http://monitor.rpiot.com.br/aula/eventos/


# Trabalhos Turma 2025
## Orientações para Projeto 1:

Utilizando o projeto inicial da <a href=https://wokwi.com/projects/350144439208903252>maquina de lavar</a>, crie uma máquina personalizada (não será considerado máquina de lavar) que atenda os seguintes critérios:

- apresente no mínimo 05 perguntas entre (sim x não) ou ajustes de valores (exemplo tempo);
- ajustes de pelo menos 03 valores inteiros;
- transições das etapas em máquina de estados;
- utilize pelo menos 03 leds como saídas;
- as perguntas e respostas devem utilizar display LCD e botões (exemplos para botões: + - 1 2 3 Y N enter) 
-  enviar o código e link de simulação na área trabalhos (suap), um integrante da dupla. Lembre-se colocar "Lock" em seu projeto 
- As duplas não podem ter trabalhos "clones", criatividade e dificuldades serão pontuados
<BR>
<B>OBS: 
Para tempos de atraso, acima de 10 ms total, utilizar TIMERS 0, 1 ou 2.</B><BR>
- ** outras especificidades posteriormente informadas.

## Orientações para Projeto 2:
Aperfeiçoamento do projeto 1 ou uma nova proposta com a programação do STM32. Acrescentar novos recursos de programação e hardware; PWM, comunicação serial com ESP32 (wifi), memorização de parametros em eeprom, tela OLED I2C.



Projeto 2: Microcontrolado com Wifi

    Visualizar Solicitação
    Editar Solicitação
    Remover Solicitação

Projeto em AVR C Microcontrolador Atmega 328P utilizando I2C e UART com wifi
Entregar em formato relatório resumido texto contendo introdução teórica sobre a variável (sensor) utilizada e referências; e enviar por email ou neste canal (suap) também o código fonte.


Semelhante a maquina de lavar, o programa deve conter

-Leitura de um sensor analógico utilizando conversor AD

-Função de transferência para o sensor,

- Interface com ESP32 com acesso wifi para uma dashboard em html.

- Atualização de STATUS no OLED e Dashboard

- Comandos na interface será mais ponderados na pontuação.

- Exibir valor no display OLED protocolo i2c.

- Menu para 2 Set Point, ou seja, quando alcançar um valor mínimo, aciona-se LED 1, e quando alcança um limite máximo, acende-se um Led 2.
- Verifiquem no laboratório a disponibilidade de microntroladores e protoboard
.
Use como referências de código o reposítório: https://github.com/mchavesferreira/smc

Recomenda-se como prazo de entrega o dia 27/06/2025.

# Exemplo projeto 2 

https://github.com/mchavesferreira/IoT_Esp32_Uno_SMC_projeto2



Exemplos de projetos
https://github.com/mchavesferreira/smc/tree/main/esp32_serial2

- 
<BR><h1>Sugestão de lista de compras para montagem de projetos com ESP32</h1>
<BR>
<BR>-Esp32  Devkit Esp32-wroom-32 ou ESP32S3 - 30 Pinos - Tipo C

<BR>-Display Oled 0.96 I2c Branco/amarelo ou Azul 

<BR>
<BR>-Cabo Wire Jumper 20cm 40 Fios Fêmea-macho Protoboard 

<BR>
<BR>-Jumper Macho X Macho 65pcs Fio Arduino 

<BR>
<BR>-Protoboard 830 Furos


<BR>
<BR>-Minimo 5 Leds, resistores, botões Push-buttons

<BR>

- ** outras especificidades posteriormente informadas.
- 
# Exemplo para identificar uma sequencia de caracteres na porta serial

Olhe este exemplo que recebe uma sequencia de caracteres, sendo que o primeiro tem que ser X

https://wokwi.com/projects/402417705867398145
	
## Links e referências

Introdução a Linguagem C.
https://github.com/misaelrezende/Exercicios-do-Livro-Linguagem-C-Completa-e-Descomplicada

https://github.com/daniel-oliv3/Introducao-a-Programacao_500-Algoritmos-Resolvidos-Por-Lopes-Garcia
Introducao-a-Programacao_500-Algoritmos-Resolvidos-Por-Lopes-Garcia 


https://github.com/Franzininho/exemplos-avr-libc/tree/main/exemplos

https://embarcados.com.br/franzininho-diy-contador-de-pulsos-externos/


## Turma 2025
   - Tarefa Suap - Cronometro Big Number em LCD simulado em wokwi e/ou proteus

  - Tarefa Suap - Maquina de Lavar com delay simulado em wokwi e/ou proteus

   - Tarefa Suap - Maquina de Lavar com Timers simulado em wokwi e/ou proteus

- Projeto 1: Protótipo em protoboard do projeto 1

 - Avaliação Presencial escrita (Sorteio de um projeto em dupla)


  - Projeto 2 - 27/6/2025.

  - Avaliação 2.  27/6/2025
