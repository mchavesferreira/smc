//------------------------------------------------------------------------------------- //
//		AVR e Arduino: 								//	
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
//		PROJETO CAFETEIRA FUNCOES DE MENU    							//
//			tempo utilizando delay																			//
//		LCD Interface de dados de 4 bits
//      Adaptacao: prof. Marcos Chaves   versao: AVR_C junho/2025                    //
//=====================================================================================	//
//  PORTD d2 a d7 display  d0 chocoloate d2 capuccino
//  PORTB b0 valvulas  
//  PORTC  PC0- ALTERA DISPLAY
//         PC1- ENTER (EMERGENCIA EM PREPARAÇÃO)
//         PC2 - SENSOR presença coopo
//         PC4 - SENSOR CARTAO
//  

#define F_CPU 16000000UL
#include <string.h>
#include <stdbool.h>  // Adicionado para usar bool
#include <avr/io.h>
#include <util/delay.h>		//biblioteca para o uso das rotinas de _delay_
#include <avr/interrupt.h>
#include "def_principais.h"
#include "USART.h"
#include "LCD.h"

// variaveis
unsigned char digitos[tam_vetor];	//declaracao da variável para armazenagem dos digitos
unsigned int tempo=0,pressionado=0;
unsigned char tempoagitacao1=2,tempoagitacao2=3,tempomolho1=4,tempomolho2=5, tempocentrifuga=6;
unsigned char  estado=0;	//declara variavel global
	
#include "funcoes_cafeteira.h"	

// TIMER 1  *  *   *   *   *   *   *    *   *   *   *   *   *   *
void set_timer1_overflow(unsigned int valor)  // timer 1
{	TCCR1A=0b00000000;
	TCCR1B = (1<<CS12) | (1<<CS10);  // prescaler 1024
	TIMSK1= 1 << TOIE1;
	TCNT1=valor;
	//	OCR1A=52000;
	//	OCR1B=60000;
	sei();
}

ISR(TIMER1_OVF_vect)  // estouro timer 1
{  TCNT1=49910;
	if(tempo)--tempo;
	
}

#define TIMEOUT_MAX 100  // Timeout máximo em ciclos (~100ms por caractere)


// Função para ler linha da serial com timeout
uint8_t recebeComando(unsigned char *buffer, uint8_t max_len) {
	uint8_t index = 0;
	uint16_t timeout;

	timeout = 0;
	while (index < max_len - 1) {
		// Verifica se chegou dado
		if (UCSR0A & (1 << RXC0)) {
			char c = UDR0;
			if (c == '\n' || c == '\r') {
				break;
			}
			buffer[index++] = c;
			timeout = 0; // Reset do timeout após receber dado
			} else {
			_delay_ms(5); // Intervalo para evitar sobrecarga da CPU
			timeout++;
			if (timeout >= TIMEOUT_MAX) {
				return false; // Timeout
			}
		}
	}

	buffer[index] = '\0'; // Finaliza a string
	return true;
}

// Retorna 1 se há dado disponível, 0 se não há
uint8_t USART_DadoDisponivel() {
	return (UCSR0A & (1 << RXC0));
}

//--------------------------------------------------------------------------------------
int main()
{	

	DDRB = 0b11111111;			// pinos como saida
	PORTB= 0b00000000;			//
	DDRD = 0b11111111; 				//PORTD como saída (display)
	PORTD= 0b00000000;				//
	UCSR0B = 0x00;				//PD0 e PD1 como I/O genérico, para uso no Arduino
    DDRC= 0b00000000;           // configura entradas
    PORTC= 0b11111111;    /// ativar pull up
	
	unsigned char digitos[tam_vetor];	//declara??o da vari?vel para armazenagem dos digitos
	unsigned int valorbinario, valorpercentual;
    USART_Inic(MYUBRR);  // inicia comunicao serial
    inic_LCD_4bits();   // inicializa LCD
	cmd_LCD(0x01,0); 				//desloca cursor para a segunda linha
	unsigned char recebe[8];
	 char buffer[10];
	 uint8_t index = 0;
  uint8_t i = 0;
  unsigned char dado;
	 
	 set_timer1_overflow(49910);   // inicializa timer 1 para 1 segundo
	 
    tempo=5;   // varial de contagem de tempo
	while(1) 					//laco infinito
	{ 	
		 switch(estado)
			{  //inicio_switch
			  case 0: estado_inicial();       break;
			  case 1: configura_quantidadexicaras();  break; 
			  case 2: configura_tamanhoxicara();     break; 
			  case 3: configura_desejacafe();  break; 
			  case 4: configura_desejaleite();     break; 
			  case 5: configura_desejacha(); break;  
//// iniciacao dos processos
			 case 6:  inicializando_processo();  break;
			 case 7:  enchendoagua();        break;  // 
			 case 8:  preparando_cafe();       break; //
			 case 9:  preparando_leite();          break; // 	 
        	 case 10: preparando_cha();       break; //
			 case 11: preparando_acucar();         break; // 
			 case 12: preparando_capuccino();      break;  // 
			 case 13: preparando_chocolate();      break; //
			 case 14: reinicializando(); break; // reinicializando	  
			}   // fim switch
      
	if(estado>5)  // testes de estados emergencia tilizando botao ENTER a partir do estado 5
          {
           if(!tst_bit(PINC,1))  // verifica se botao enter pressionado
                { pressionado++;  // incrementa variavel pressionado
                  if(pressionado>3000)  // compara se ultrapassou o valor limit, botao pressionado por longo periodo
                     { estado=14; }   // direciona para estado 14 reinica processo
                } else
                {
                  pressionado=0;  // botao nao pressionado  zera valor
                }  // fim if botao pressionado
          } // fim if teste de estados emergencia
     

        if (USART_DadoDisponivel()) {
	       unsigned char carac_recebe = USART_Recebe();
            
	         if (carac_recebe == 'P') {  /// P inicio da msg vinda do esp32
				  i=0;
				 while (i < 9) {
					 dado = USART_Recebe();
                     if(i==0 && dado== 'R') { estado=14; break; }   // R pedido de cancelar recebido
					 // Testa quebra de linha
					 if (dado == '\n' || dado == '\r') {
						 break;
					 }

					 buffer[i++] = dado;
				 }
			
			if(estado<7){	       // Processa pedido	   
				  if(buffer[1]='s')  { set_bit(flag1,deseja_cafe);  } else {  clr_bit(flag1,deseja_cafe); }
		    	  if(buffer[3]='p')	 quantidaaguaPMG=1;
				  if(buffer[3]='m')	 quantidaaguaPMG=2;
			      if(buffer[3]='g')	 quantidaaguaPMG=3;
			      if(buffer[5]='s')  {  set_bit(flag1,deseja_cha);  }  else {  clr_bit(flag1,deseja_cha);  }
			      if(buffer[7]='s')  {  set_bit(flag1,deseja_leite); } else {  clr_bit(flag1,deseja_leite);  }
			      estado=6;  tempo=8; /// iniciando processo 8 segundo para iniciar
	                 }
	          } // fim do inicio da mensagem 
      } // fim uart recebendo dados
		
		
	 		
	}  // fim do while
	
} // fim do main
//======================================================================================	


