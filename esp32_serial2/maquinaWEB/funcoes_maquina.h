// variaveis
unsigned int tempo=4;
unsigned char  estado=0;	//declara variavel global
unsigned char pressionado=0,etapa2=0;

signed int le_potenciometro();
void set_pwm_pb3(unsigned int valor);
///  funcoes da maquina de milk-shake
int valorluz;
//descricao dos pinos I/O
// ENTRADAS

#define botao_enter PC2 // botao ENTER / STOP processo
#define sensor_cheio PC3 // sensor cheio tanque
#define sensor_cobertura PC4 // sensor vazio tanque

//SAIDAS
#define ligar PB0       // funcionamento da maquina
#define led_sorvete PB1
#define motor_agitacao PB4 // motor agitacao do sorvete
#define valvula_sorvete PB3 // valvula de entrada de sorvete
#define valvula_cobertura PB2 // valvula de vazão de coberura

unsigned int valorbinario;
int convert();
void serial_print();


void inicia(){
	set_bit(PORTB,ligar);
	//quando o arduino receber "S" do esp32 inicia o processo e envia mensagem pro esp32 via serial informando que iniciou o processo
	unsigned char start1 = USART_Recebe();
	
	if (start1 =='S') {
		
		set_bit(PORTB,valvula_sorvete) ;
		estado= 1;
		UART_SendString("G");
	}
	else
	{
		
		estado =0;
	}
	

}


//informa tbm ao esp32 que chegou na etapa de colocar sabor
void colocando_sabor()
{
	// Informa também ao ESP32 que chegou na etapa de colocar sabor
	
	if (!tst_bit(PINC, sensor_cheio))  // Verifica se o sensor de tanque cheio está desativado
	{
		clr_bit(PORTB, valvula_sorvete);  // Desliga a válvula de entrada de sorvete
		estado = 2;
		UART_SendString("U");
		tempo = 5;
		
	}
}



void agitacao1()
{
	//informa ao esp32 chegou na etapa de agitação
	set_bit(PORTB,motor_agitacao);                    //liga motor agitacao
	set_pwm_pb3(valorbinario); // controla o LED no PORTD3 com o valor lido do potenciômetro
	
	valorbinario = le_potenciometro();  // le o valor binario de 10 bits
	set_pwm_pb3(valorbinario); // controla o LED no PORTD3 com o valor lido do potenciômetro
	// ...
	if(!tempo)                           //testa tempo=0
	{
		clr_bit(PORTB,motor_agitacao);          // desliga motor agitacao
		UART_SendString("T");
		estado=3;
	}
	//  _delay_ms(1); tempo--;
}


void colocandocobertura1()
{
	//informa ao esp32 que chegou na etapa de colcoar cobertura
	set_bit(PORTB,valvula_cobertura);
	if(!tst_bit(PINC,sensor_cobertura))                     // testa sensor cheio
	{
		clr_bit(PORTB,valvula_cobertura);                 // desliga valvula de entrada
		UART_SendString("O");
		estado=4;                         // muda estdo
		tempo=1;
	}
	
	
}


void finalizado()
{
	//informa ao esp32 que o pedido esta pronto
	if(!tempo)
	{
		UART_SendString("L");
		estado=5;
		tempo=2;
	}
	
}
void fim_processo()
{
	// informa o esp32 para resetar o serverweb
	if(!tempo)
	{
		UART_SendString("F");
		tempo=2;
		estado=0;
	}
}

void pedidocancelado()
{
	unsigned char stop = USART_Recebe();
if (stop == 'N') {
	estado = 0;
	clr_bit(PORTB, valvula_cobertura);
	clr_bit(PORTB, motor_agitacao);
	clr_bit(PORTB, valvula_sorvete);
	UART_SendString("C");
}
}