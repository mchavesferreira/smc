//Neste segundo exemplo será feita uma comunicação simples com o computador utilizando a biblioteca UART.h, 
///convertendo as letras maiúsculas em minúsculas e vice-versa.
// fonte:   Professor Rodrigo Rech

#include <avr/io.h>
#include <avr/interrupt.h> #include "UART.h"
//Criação da string que será enviadda pela UART
char s[] = "Comunicacao SERIAL...";
// Interrupção da UART //====================================================== ISR (USART_RX_vect)
{
char ch; //armazena o caractere lido
ch = UDR0; //Faz a leitura do buffer da serial
   // Converte letras minúsculas em maiúsculas e maiúsculas em minúsculas
if (ch>='a' && ch<='z') ch = ch - 'a' + 'A';
else if (ch>='A' && ch <='Z') ch = ch - 'A' + 'a';
   // Envia para o computador
   UART_enviaCaractere(ch);
}
//------------------------------------------------------
int main() {
    UART_config();
    UART_enviaString(s);
    sei();
while(1){ }
}