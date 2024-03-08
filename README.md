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

Pinagem
Atmega328P
<img src=https://github.com/mchavesferreira/mcr/blob/main/imagens/pinout_atmega328P.png>

<img src=https://github.com/mchavesferreira/smc/assets/63993080/9310c6ec-f83e-40e3-968e-5a459110fd48)>


## Simulação online para microcontrolador

    Wokwi - Um simulador online muito popular para Arduino e outros microcontroladores. Ele suporta uma variedade de placas Arduino (que são baseadas em microcontroladores de 8 bits) e permite simular circuitos eletrônicos junto com o código. É uma ótima ferramenta para ensinar os conceitos de programação em C junto com a eletrônica básica.
    https://wokwi.com/projects/356295365780235265

    Tinkercad Circuits - Tinkercad, da Autodesk, oferece um simulador de Arduino que funciona diretamente no navegador. Ele permite aos usuários montar circuitos e escrever código para eles, tudo em uma interface gráfica amigável. É particularmente bom para iniciantes.

    Proteus - Embora não seja totalmente online, o Proteus Design Suite oferece recursos de simulação poderosos para uma ampla gama de microcontroladores. Seus estudantes podem escrever código em C, simular o funcionamento do microcontrolador e testar circuitos eletrônicos em um ambiente virtual.

    EasyEDA - Outra ferramenta que, embora seja mais focada no design de circuitos eletrônicos, também oferece suporte à simulação de microcontroladores, incluindo a escrita e teste de códigos em C.

    CircuitJS - Este é um simulador de circuitos eletrônicos baseado em JavaScript que roda diretamente no navegador. Embora seu foco principal não seja microcontroladores, ele pode ser útil para ensinar os princípios básicos de eletrônica que são relevantes para a engenharia de automação.

Simuladores para linguagem C

https://www.tutorialspoint.com/compile_c_online.php

https://www.mycompiler.io/pt/new/cpp   

https://www.online-cpp.com/online_c_compiler

## Introdução a linguagem C
https://github.com/mchavesferreira/smc/tree/main/linguagemc


##  Ambiente de programação


Avr Studio 7.0
http://studio.download.atmel.com/7.0.2389/as-installer-7.0.2389-full.exe

## Primeiro-Programa-em-C

### Pisca Led
Este primeiro exemplo de programa com um pisca Led
<img src=imagens/piscaled.png>

Simulador para o programa
https://wokwi.com/projects/363128065545249793

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
#define BOTAO PD7   //BOTAO e o substituto de PD7 na programacao     	
//-------------------------------------------------------------------------------------
int main()
{
	DDRD = 0b00000100;	//configura o PORTD, PD2 saida, os demais pinos entradas
	PORTD= 0b11111111;	/*habilita o pull-up para o botao e apaga o LED (todas as 
						entradas com pull-ups habilitados)*/
	
	while(1)								//laco infinito
	{
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
https://github.com/mchavesferreira/smc/blob/main/serialAVR/main_usart_menu.c <BR>
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



17/03/2023   - Tarefa Suap - Cronometro Big Number em LCD simulado em wokwi e/ou proteus

24/03/2023   - Tarefa Suap - Maquina de Lavar com delay simulado em wokwi e/ou proteus

31/03/2023   - Tarefa Suap - Maquina de Lavar com Timers simulado em wokwi e/ou proteus

05/05/2023  - Projeto 1: Protótipo em protoboard do projeto 1

05/05/2023  - Avaliação Presencial escrita (Sorteio de um projeto em dupla)


Junho/23  - Projeto 2 - 23/6/2023.

Junho/23  - Avaliação 2.  30/6/2023

## ESP32 e suas aplicações IOT

https://github.com/mchavesferreira/mcr/blob/main/ESP32.md

## Oled
## Display
 
<BR>Displays LCD, Oled, comunicação I2C
### LCD 16x2
  <BR>01 -<a href=https://wokwi.com/projects/342202939017790036> Exemplo LCD 16x2 paralelo</a>
  <BR>02 -<a href=https://wokwi.com/projects/342199886273315410> Exemplo LCD 16x2 I2C</a>
  
### Display Oled   
  <BR>03 -<a href=https://wokwi.com/projects/342195248670179922> Exemplo Oled U8g2lib</a>
  <BR>04 -<a href=https://wokwi.com/projects/342195418005766739> Exemplo Adafruit_SSD1306</a>
  <Br> <img src=https://github.com/mchavesferreira/mcr/blob/main/imagens/oled.png width=400 height=225><BR>
<details><summary>Exemplo Oled</summary>
<p>

```ruby  
*/
#include <U8g2lib.h>
#include <Wire.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();	// limpa memoria interna
  u8g2.setFont(u8g2_font_ncenB08_tr);	// escolha da fonte
  u8g2.drawStr(15, 10, "IFSP Catanduva");	// escrevendo na memoria interna
  u8g2.sendBuffer(); // transferindo da memoria interna para display
  delay(1000);
}  
```
</p>
</details> 

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
	
## Links e referências

Introdução a Linguagem C.
https://github.com/misaelrezende/Exercicios-do-Livro-Linguagem-C-Completa-e-Descomplicada

https://github.com/daniel-oliv3/Introducao-a-Programacao_500-Algoritmos-Resolvidos-Por-Lopes-Garcia
Introducao-a-Programacao_500-Algoritmos-Resolvidos-Por-Lopes-Garcia 


https://github.com/Franzininho/exemplos-avr-libc/tree/main/exemplos

https://embarcados.com.br/franzininho-diy-contador-de-pulsos-externos/

