# Conversor AD

## funções principais
```java
void configura_AD(){
// configura canal 
ADMUX = (1<<REFS0) | (1<<MUX2) | (1<<MUX0);			//Tensão interna de ref (+5V), canal ADC5
ADCSRA = (1<<ADEN) | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//habilita o AD e define um prescaler de 128 (clk_AD = F_CPU/128), 125 kHz
}
```


```java
signed int le_temp()
{
	set_bit(ADCSRA, ADSC);								//inicia a conversão
	while(tst_bit(ADCSRA,ADSC));						//espera a conversão ser finalizada
	
	return (ADC);
}
```

## Exemplo de utilização


```java
main(){
void configura_AD();
unsigned int valorbinario;
while(1)
   {
   valorbinario=le_temp(); 

  }
}
```

