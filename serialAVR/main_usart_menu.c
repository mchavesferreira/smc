// SIMULACAO WOKWI : https://wokwi.com/projects/365174034245894145
//AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.					//
//------------------------------------------------------------------------- //
//========================================================================	//
//			COMUNICAÇÃO SERIAL ENTRE O ARDUINO E UM COMPUTADOR	
// exemplo incrementa variavel e envia para porta SERIAL			//
//=========================================================================	//
#include "def_principais.h"
#include "USART.h"

// Função para transmitir um caractere pela porta serial
void serialTransmit(unsigned char data) {
		while (!( UCSR0A & (1<<UDRE0)) );	//espera o dado ser enviado
  	UDR0 = data; 					//envia o dado

}

// Função para receber um caractere pela porta serial
unsigned char serialReceive() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}


//-------------------------------------------------------------------------
int main()
{   unsigned char digitos[tam_vetor];	//declaração da variável para armazenagem dos digitos
	unsigned int valor=0;
	USART_Inic(MYUBRR);
	
	escreve_USART("Menu ");   // envia texto para serial
		USART_Transmite(10);   // ou 10 codigo ascii pula linha
		_delay_ms(200);  // aguarda intervalo de tempo
	

while (1) {
        // Exibe o menu de opções
        serialTransmit('\n');
        serialTransmit('1');
        serialTransmit('.');
        escreve_USART(" Opção 1");
        serialTransmit('\n');
        serialTransmit('2');
        serialTransmit('.');
        escreve_USART(" Opção 2");
        serialTransmit('\n');
        serialTransmit('3');
        serialTransmit('.');
        escreve_USART(" Opção 3");
        serialTransmit('\n');
        serialTransmit('\n');
       escreve_USART("Digite a opção desejada: ");
        
        // Lê o caractere digitado pelo usuário
        unsigned char option = USART_Recebe();
        
        // Executa a ação correspondente à opção selecionada
        switch (option) {
            case '1':
                // Implemente a ação da opção 1
                serialTransmit('\n');
               escreve_USART("Opção 1 selecionada!");
                break;
                
            case '2':
                // Implemente a ação da opção 2
                serialTransmit('\n');
                escreve_USART("Opção 2 selecionada!");
                break;
                
            case '3':
                // Implemente a ação da opção 3
                serialTransmit('\n');
                escreve_USART("Opção 3 selecionada!");
                break;
                
            default:
                // Opção inválida
                serialTransmit('\n');
                escreve_USART("Opção inválida!");
                break;
        }
        
        _delay_ms(1000);  // Aguarda 1 segundo antes de exibir o menu novamente
    }
}
