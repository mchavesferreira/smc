# Display de 7 Segmentos
![image](https://github.com/mchavesferreira/smc/assets/63993080/bc143a19-708e-40a5-90df-d26952f0ade5)

O display de 7 segmentos é amplamente utilizado em projetos de automação e microcontroladores para exibir informações numéricas de forma simples e direta. Consistindo de sete LEDs arranjados em um padrão específico, permite a representação de dígitos de 0 a 9 e algumas letras, acendendo combinações específicas de segmentos.
Ao integrá-lo a microcontroladores, desenvolvedores podem facilmente criar interfaces de usuário para mostrar leituras de sensores, contadores, horas e outras métricas vitais em dispositivos automatizados. Sua simplicidade, eficiência energética e baixo custo fazem dele uma escolha popular para projetos que exigem uma saída numérica clara, como relógios, termômetros e contadores.

- Diferentes Display
Display Anodo comum
Todos os ânodos de cada LED estão conectados juntos. Para um segmente “acender” é necessário que as saídas esta baixa (0)<BR>
<img src=https://github.com/mchavesferreira/smc/blob/main/imagens/display-anodo-comum.jpg>

Display Catodo comum
Todos os catodos de cada LED estão conectados juntos. Para um segmente “acender” é necessário que as saídas esteja em nível alto (1)<BR>
<img src=https://github.com/mchavesferreira/smc/blob/main/imagens/display-catodo-comum.jpg>


** Mapeamento de valores para exibição no Display **

<img src=https://github.com/mchavesferreira/smc/blob/main/imagens/display_setesementos_micro.png>

Antes do envio para a porta do microcntrolador, a mesagem precisa ser codificada para o display utilizando uma biblioteca ou função de decodificação.
<BR>
<img src=https://github.com/mchavesferreira/smc/blob/main/imagens/numeros_display.png>

Exemplo de tabela de conversão:<BR>
<img src=https://github.com/mchavesferreira/smc/blob/main/imagens/tabela_anodo_catodo_display.png>


- Funções de decodificação:
  
<details><summary>Mapeia os valores hexadecimais para os pinos correspondentes no portD</summary>
<p>



```ruby
// utilizando no codigo principal:   ex:  PORTD = seg7_hex[3];
const unsigned char seg7_hex[] = {  0x40,
                                     0x79,
                                     0x24,
                                     0x30,
 0x19,
0x12,
0x02,
 0x78,
 0x00,
0x18,
0x08,
0x03,
0x46,
0x21,
0x06,
0x0E};

```
</p>
</details> 


### Montagem do Display 7 segmentos na porta D do Atmega 328P
<BR>
<img src=https://github.com/mchavesferreira/smc/assets/63993080/0ff59182-d118-4795-92c8-6a0e59dcaec7><BR>

<a href=https://github.com/mchavesferreira/smc/blob/main/imagens/montando%20display%207%20segmentos.pdf> Manual</a>

<details><summary>Código do Livro</summary>
<p>

```ruby
//--------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.							//	
//--------------------------------------------------------------------------------- //
//================================================================================	//
//    		ESCREVENDO EM UM DISPLAY DE 7 SEGMENTOS ANODO COMUM						//
//================================================================================	//
#define F_CPU 16000000UL	//define a frequência do microcontrolador em 16MHz

#include <avr/io.h> 	 	//definições do componente especificado
#include <util/delay.h>		//biblioteca para o uso das rotinas de _delay_
#include <avr/pgmspace.h>	//biblioteca para poder gravar dados na memória flash 

//Definições de macros - para o trabalho com os bits de uma variável
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) //testa o bit x da variável Y (retorna 0 ou 1)

#define DISPLAY	 PORTD		//define um nome auxiliar para o display  
#define BOTAO 	 PB0 		//define PB0 com o nome de BOTAO

//variável gravada na memória flash
const unsigned char Tabela[] PROGMEM = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};
//-----------------------------------------------------------------------------------

int main()
{
	unsigned char valor = 0;	//declara variável local
	
	DDRB = 0b11111110;			//PB0 como pino de entrada, os demais pinos como saída
	PORTB= 0x01;				//habilita o pull-up do PB0		 
	DDRD = 0xFF;				//PORTD como saída (display)
	PORTD= 0xFF;				//desliga o display
	UCSR0B = 0x00;				//PD0 e PD1 como I/O genérico, para uso no Arduino

	while(1) 					//laço infinito
	{
		if(!tst_bit(PINB,BOTAO))//se o botão for pressionado executa  
		{ 
			if(valor==0x0F)		//se o valor for igual a 0xF, zera o valor, 
				valor=0;
			else 				//se não o incrementa
				valor++;

			//decodifica o valor e mostra no display, busca o valor na Tabela.
			DISPLAY = pgm_read_byte(&Tabela[valor]); 
			
			_delay_ms(200);		//atraso para incremento automático do nr. no display
			
		}//if botão

	}//laço infinito
}
//===================================================================================
```
</p>
</details> 


- Circuitos integrados conversores
<img src=https://github.com/mchavesferreira/smc/blob/main/imagens/4511dsp.gif>

- Multiplexação de displays
<BR><img src=https://github.com/mchavesferreira/smc/blob/main/imagens/7-display-multiplexing.jpg><BR><BR>
Em muitos casos é necessário a exibição em mais um display de 7 segmentos, porém não pinos disponíveis, então utiliza-se a técnica de multiplexação de displays

<img src=https://github.com/mchavesferreira/smc/blob/main/imagens/multiplexing.gif>

<img src=https://github.com/mchavesferreira/smc/blob/main/imagens/ligacao-multiplexing.jpg>

[<a href=Readme.md>Voltar</a>]
