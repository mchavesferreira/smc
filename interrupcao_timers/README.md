# Interruções 

## Conhecendo Interrupções, Temporizadores e interrupções externas para Atmega 328P


Slide Interrupção: [ https://github.com/mchavesferreira/smc/blob/main/aula_interrupcao_Marcos_Chaves_V2021_2.pptx](https://github.com/mchavesferreira/smc/blob/main/interrupcao_timers/aula_interrupcao.pdf)

- [Interrupção](#Interrupção)
        - [Interrupção Externa](#Interrupção-Externa)
        - [Timer 0](#Timer-0)
        - [Timer 1](#Timer-1)
        - [Timer 2](#Timer-2)



## Interrupção

Comportamento das interruções

<img src=https://raw.githubusercontent.com/mchavesferreira/mice/main/interrupcao/imagens/comportamento_interrupcao.png>

## Flags da interrupção

<img src=https://github.com/mchavesferreira/mice/blob/main/interrupcao/imagens/quadro_interrupcoes.png>

Endereços (interrupt vector) das interrupções para Atmega 328P

<img src=https://github.com/mchavesferreira/mice/blob/main/interrupcao/imagens/enderecoes_interrupcao.png>

![image](https://github.com/mchavesferreira/smc/assets/63993080/13bf5292-eb12-4f74-bd2c-d15305f316c0)


## Interrupção Externa

Pinos da interrupção PD2(Int0) e PD3(int1)

<img src=https://github.com/mchavesferreira/mice/blob/main/interrupcao/imagens/pinos_interrupcao_int01.png>

Exemplo de um circuito para exemplificar a interrupção externa, esquema do livro:

<img src=https://github.com/mchavesferreira/mice/blob/main/interrupcao/imagens/int0_livro.png>

Simulação:

<a href=https://wokwi.com/projects/359476742621416449><img src=https://raw.githubusercontent.com/mchavesferreira/mice/main/interrupcao/imagens/esquemasimula.png></a>

## Timer 0
(8 bits)
Capítulo Livro: https://github.com/mchavesferreira/smc/blob/main/Timer_0_Livro.pdf

Código base: https://github.com/mchavesferreira/smc/blob/main/codigo_basico_timer0.pdf

Utilizando comparadores OCR:  https://github.com/mchavesferreira/smc/blob/main/exemplo_timer0_overflow_compA_CompB.c.c

Simulação Proteus e Avr Studio:  https://github.com/mchavesferreira/smc/blob/main/timer%200%20Normal%20pulsos%20quadrados.rar

![image](https://github.com/mchavesferreira/smc/assets/63993080/fb163981-45bb-4f8f-93fd-5db121c46d01)

### Restradores de confiuração

![tccr0b](https://github.com/mchavesferreira/smc/assets/63993080/ed84f7c6-b025-4db3-8af1-99b55cd0291c)

![prescaler](https://github.com/mchavesferreira/smc/assets/63993080/5f65b55f-abdd-41ee-b954-58f20d7b0d47)

![tabelamodos](https://github.com/mchavesferreira/smc/assets/63993080/38752d83-09b6-4912-af42-d5ffa4aa8a4d)

![modo0cab](https://github.com/mchavesferreira/smc/assets/63993080/e89889e4-c70d-4715-86ee-db7647a1f6f5)



## Timer 1
(16 bits)
Capítulo Livro:  https://github.com/mchavesferreira/smc/blob/main/Timer_1_Livro.pdf

Exemplo de programação com Timer 1: 
https://github.com/mchavesferreira/smc/blob/main/interrupcao_timers/Exemplo%20Programa%C3%A7%C3%A3o%20de%20Microcontroladores.pdf

https://github.com/mchavesferreira/smc/blob/main/exemplo_Timer_1_funcoes_pwm_rapido_funcoes.c

Contador de Eventos:  https://github.com/mchavesferreira/smc/blob/main/interrupcao_timers/contador_eventos_TC1_C.zip

#### Registradores Timer 1


## Timer 2
(8 bits)


## Modos PWM

Modo Normal

![modonormal](https://github.com/mchavesferreira/smc/assets/63993080/d2244ba8-da0e-4057-9cdf-629743ba23ae)

Modo CTC
![modoCTC](https://github.com/mchavesferreira/smc/assets/63993080/e1d9e035-3905-4009-aa11-afec8ed4d2e6)


Modo Fase Corrigida

![modofasecorrigida](https://github.com/mchavesferreira/smc/assets/63993080/cd23c178-0296-4996-a6b5-9852a468bf89)


Modo PWM Rapido

![modopwmrapido](https://github.com/mchavesferreira/smc/assets/63993080/5c54a05c-1c7d-40cb-89d8-361ba99ca0ec)




