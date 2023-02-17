//-------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								 //	
//-------------------------------------------------------------------------------------- //
//====================================================================================== //
//		Programa para a leitura de temperatura de um DS18S20							 //
//				Envio dos dados ao computador											 //
//====================================================================================== //

#include "def_principais.h"
#include "USART.h"
#include "_1wire.h"

const char msg[] PROGMEM = "Sensor de Temperatura DS18S20\n\0";
unsigned char digitos[tam_vetor];

//------------------------------------------------------------------------------------
int main()
{
    char sinal;
	unsigned char temp_LSB, temp_MSB;
	unsigned int valor_temp;
	
	USART_Inic(MYUBRR);
	escreve_USART_Flash(msg);
	
	while(1)
    {
 		reset_1w();						//reset do sensor (a resposta de presença é retornada mas não avaliada).
		escreve_byte_1w(0xCC);			//comando para pular ROM (só 1 dispositivo no barramento).
		escreve_byte_1w(0x44);			//manda iniciar a conversão 
		alimenta_1w();					//alimentação parasita (quando usar comentar a linha abaixo) 
		//_delay_ms(750);				//sem alimentação parasita (quando usar comentar a linha acima)
		reset_1w();			
		escreve_byte_1w(0xCC);
		escreve_byte_1w(0xBE);			//avisa que quer ler a memória
		
		temp_LSB = le_byte_1w();		//só interesse em ler os dois bytes da temperatura
		temp_MSB = le_byte_1w();
										
		if (temp_MSB>0)					//verifica se a temperatura é negativa
		{ 	
			temp_LSB = 256 - temp_LSB;	//converte número negativo para positivo
  			sinal = '-';				//sinaliza o caractere de sinal da temperatura para o LCD
		}
		else			
			sinal='+';
		
		//conversão do número lido para um valor inteiro sem vírgula (temp_LSB*10/2)
		valor_temp = 5*temp_LSB;		//retirar a virgula do número e converte, cada bit LSB vale 0,5°C
										//Para uso do DS18B20 a fórmula deve ser alterada.		
		ident_num(valor_temp,digitos);
		USART_Transmite(sinal);			//envio dos dado ao computador
		USART_Transmite(digitos[3]);
		USART_Transmite(digitos[2]);
		USART_Transmite(digitos[1]);
		USART_Transmite(',');
		USART_Transmite(digitos[0]);
		USART_Transmite(176);			//simbolo 'o'
		USART_Transmite('C');
		USART_Transmite('\n');
    }
}
//------------------------------------------------------------------------------------
