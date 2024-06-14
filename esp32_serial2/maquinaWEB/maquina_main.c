
//=====================================================================================	//
//		MAQUINA DE MILKSHAKE COM FUNCOES DE MENU    							//
//																						//
//		LCD Interface de dados de 4 bits
//      Adaptacao: Luiz Eduardo Lima  versao: AVR_C                    //
//=====================================================================================	//

#include "def_principais.h"			//inclusao do arquivo com as principais definicoes
#include "LCD.h"   // biblioteca .c e .h LCD display 16x2

#include "USART.h"

#include "funcoes_maquina.h"



// Função para receber um caractere pela porta serial
unsigned char serialReceive() {
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
	
}
// Função para enviar um caractere via UART
void UART_SendChar(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));  // Aguarda o registro de transmissão estar vazio
	UDR0 = data;  // Envia o caractere
}

// Função para enviar uma string via UART
void UART_SendString(const char* str) {
	unsigned int i = 0;
	while (str[i] != '\0') {
		UART_SendChar(str[i]);
		i++;
	}
}

//TIMER 1

ISR(TIMER1_OVF_vect)                              //interrupção do TIMER1
{
	TCNT1 = 0xC2F7;    // Renicia TIMER
	if(tempo)
	{tempo--;}    // subtrai tempo se diferente de 0
}

void configura_AD(){
	// configura canal
	ADMUX = (1<<REFS0) | (1<<MUX2) | (1<<MUX0);			//Tens�o interna de ref (+5V), canal ADC5
	ADCSRA = (1<<ADEN) | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//habilita o AD e define um prescaler de 128 (clk_AD = F_CPU/128), 125 kHz
}


signed int le_potenciometro();
void set_pwm_pb3(unsigned int valor);


void set_pwm_pb3(unsigned int valor) {
	DDRD |= (1 << PD3); // Configura o PD3 como saída
	TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20); // Configura o PWM do TIMER2 em modo não-invertido
	TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20); // Define o prescaler do TIMER2 como 1024
	OCR2B = valor; // Escreve o valor lido do potenciômetro no registrador OCR2B, controlando a largura do pulso PWM
}


//--------------------------------------------------------------------------------------
int main()
{
	//declaracao da vari�vel para armazenagem dos digitos
	DDRB = 0b00111111;			//PORT B saida
	PORTB= 0b00000001;		        	//inicia desligado
	DDRC = 0b00000000;			//PORT C entrada
	PORTC= 0b11111111;          //PULL UP portC
	DDRD = 0xFF;				//PORTD como sa�da (display)
	UCSR0B = 0x00;				//PD0 e PD1 como I/O gen�rico, para uso no Arduino
	DDRC= 0b00000000;           // saidas motor e valvulas
	//TiMMER
	TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
	TCCR1B = 0;                        //limpa registrador
	TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1
	
	TCNT1 = 0xC2F7;                    // incia timer com valor para que estouro ocorra em 1 segundo
	// 65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
	
	TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1 por overflow
	sei();

	USART_Inic(MYUBRR);// iniciar comunicação serial

	inic_LCD_4bits();				//inicializa o LCD
	cmd_LCD(0x01,0); 				//desloca cursor para a segunda linha
	
	configura_AD();
	
	while(1) 					//laco infinito
	{
			
			
		
		
		switch(estado){  //estado inicial
			
			case 0: inicia();                  break;
			case 1:
			colocando_sabor();  break;
			case 2: agitacao1();  break;
			case 3: colocandocobertura1(); break;
			case 4: finalizado(); break;
			case 5: fim_processo();  break;

			//  ........
		}   // fim switch
		
		if(estado>5)  // testes de estados emergencia tilizando botao ENTER a partir do estado 5
		{
			if(!tst_bit(PINC,2))  // verifica se botao enter pressionado
			{ pressionado++;  // incrementa variavel pressionado
				if(pressionado>3000)  // compara se ultrapassou o valor limit, botao pressionado por longo periodo
				{ estado=14; }   // direciona para estado 14
			} else
			{
				pressionado=0;  // botao nao pressionado  zera valor
			}  // fim if botao pressionado
		} // fim if teste de estados emergencia
		
	}// fim do while
	
}
// fim do main
//======================================================================================

signed int le_potenciometro()
{
	set_bit(ADCSRA, ADSC);								//inicia a convers�o
	while(tst_bit(ADCSRA,ADSC));						//espera a convers�o ser finalizada
	
	return (ADC);
}