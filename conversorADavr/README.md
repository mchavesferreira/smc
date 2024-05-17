# Conversor AD

## Diagrama de blocos do conversor AD para o ATMEGA328
![quadro_geral](https://github.com/mchavesferreira/smc/assets/63993080/a335691f-e235-42ba-840a-d22053054d86)


## Registradores:
![registradores adc](https://github.com/mchavesferreira/smc/assets/63993080/7a8961f6-c7f6-4670-bb39-2026256f5e83)

### ADMUX – ADC Multiplexer Selection Register

O registrador ADMUX é usado para selecionar a entrada do ADC e configurar a referência de tensão.
Bits do ADMUX

    REFS1 e REFS0: Seleção da referência de tensão
        00: AREF, tensão de referência externa.
        01: AVcc com capacitor externo no pino AREF.
        10: Reservado.
        11: 1.1V de referência interna com capacitor externo no pino AREF.
    ADLAR: Ajuste à esquerda do resultado do ADC
        0: Resultado justificado à direita.
        1: Resultado justificado à esquerda.
    MUX3, MUX2, MUX1, MUX0: Seleção do canal de entrada
        0000: ADC0.
        0001: ADC1.
        0010: ADC2.
        0011: ADC3.
        0100: ADC4.
        0101: ADC5.
        0110: ADC6.
        0111: ADC7.
        1000: Temperatura interna do sensor (somente para ATmega328P).
        1110: 1.1V de tensão de referência (para leitura da referência interna).
        1111: 0V (conexão à terra).

 
###  ADCSRA – ADC Control and Status Register A

O registrador ADCSRA controla o funcionamento do ADC, incluindo o início da conversão e a configuração do prescaler.
Bits do ADCSRA

    ADEN: Habilitação do ADC
        0: ADC desabilitado.
        1: ADC habilitado.
    ADSC: Início da conversão
        0: Conversão não iniciada.
        1: Inicia a conversão.
    ADATE: Trigger automático de conversão
        0: Trigger automático desabilitado.
        1: Trigger automático habilitado.
    ADIF: Flag de interrupção do ADC
        0: Interrupção do ADC não ocorreu.
        1: Interrupção do ADC ocorreu.
    ADIE: Habilitação da interrupção do ADC
        0: Interrupção do ADC desabilitada.
        1: Interrupção do ADC habilitada.
    ADPS2, ADPS1, ADPS0: Seleção do prescaler (divisor de frequência)
        000: Divisor de 2.
        001: Divisor de 2.
        010: Divisor de 4.
        011: Divisor de 8.
        100: Divisor de 16.
        101: Divisor de 32.
        110: Divisor de 64.
        111: Divisor de 128.

 

### ADCL/ADCH – ADC Data Register

Os registradores ADCL e ADCH armazenam o resultado da conversão AD.
Estrutura do ADC Data Register

    ADCL: Byte menos significativo do resultado da conversão.
    ADCH: Byte mais significativo do resultado da conversão.

O resultado da conversão é de 10 bits, com os bits menos significativos armazenados em ADCL e os bits mais significativos em ADCH. Dependendo do valor de ADLAR no ADMUX, o resultado pode ser ajustado à esquerda ou à direita.

## ADCSRB – ADC Control and Status Register B

O registrador ADCSRB fornece controle adicional e funcionalidades avançadas para o ADC.
Bits do ADCSRB

    ACME: Habilitação do Multiplexador do Comparador Analógico
        0: Multiplexador do comparador desabilitado.
        1: Multiplexador do comparador habilitado.
    MUX5: Bit adicional para seleção de canal de entrada (junto com MUX[3:0] em ADMUX)
        0: Canal ADC0-7.
        1: Outros canais (temperatura, 1.1V, etc.).
    ADTS2, ADTS1, ADTS0: Seleção do Trigger Automático
        000: Free Running mode.
        001: Analog Comparator.
        010: External Interrupt Request 0.
        011: Timer/Counter0 Compare Match A.
        100: Timer/Counter0 Overflow.
        101: Timer/Counter1 Compare Match B.
        110: Timer/Counter1 Overflow.
        111: Timer/Counter1 Capture Event.

## Referência

A referência de tensão para o ADC (VREF) indica a faixa de conversão e pode ser: AVCC, referência interna de 1,1 V ou referência externa (no pino AREF). Se a referência externa for utilizada, é recomendado o emprego de um capacitor entre o pino de AREF e o terra. Independente disso, a
alimentação do ADC é feita pelo pino AVCC que não pode diferir de ± 0,3 V de VCC.

![Captura de tela 2024-05-17 130830](https://github.com/mchavesferreira/smc/assets/63993080/26924201-eb66-4d88-9abe-c91900adf2bf)



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

