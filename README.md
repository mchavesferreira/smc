
Aula 10/2/2023

https://wokwi.com/projects/356295365780235265


Aula 17/02/2023

Avr Studio 7.0
http://studio.download.atmel.com/7.0.2389/as-installer-7.0.2389-full.exe

Primeiro Progama em C
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
