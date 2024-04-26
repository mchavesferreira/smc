# Interruções 

## Conhecendo Interrupções, Temporizadores e interrupções externas para Atmega 328P

Slide Interrupção:  https://github.com/mchavesferreira/smc/blob/main/aula_interrupcao_Marcos_Chaves_V2021_2.pptx

- [Interrupção](#Interrupção)
        - [Interrupção Externa](#Interrupção-Externa)
        - [Timer 0](#Interrupção-Externa)
        - [Timer 1](#Interrupção-Externa)
        - [Timer 2](#Interrupção-Externa)



## Interrupção

Comportamento das interruções

<img src=https://raw.githubusercontent.com/mchavesferreira/mice/main/interrupcao/imagens/comportamento_interrupcao.png>

## Flags da interrupção

<img src=https://github.com/mchavesferreira/mice/blob/main/interrupcao/imagens/quadro_interrupcoes.png>

Endereços (interrupt vector) das interrupções para Atmega 328P

<img src=https://github.com/mchavesferreira/mice/blob/main/interrupcao/imagens/enderecoes_interrupcao.png>



## Interrupção Externa

Pinos da interrupção PD2(Int0) e PD3(int1)

<img src=https://github.com/mchavesferreira/mice/blob/main/interrupcao/imagens/pinos_interrupcao_int01.png>

Exemplo de um circuito para exemplificar a interrupção externa, esquema do livro:

<img src=https://github.com/mchavesferreira/mice/blob/main/interrupcao/imagens/int0_livro.png>

Simulação:

<a href=https://wokwi.com/projects/359476742621416449><img src=https://raw.githubusercontent.com/mchavesferreira/mice/main/interrupcao/imagens/esquemasimula.png></a>

## Timer 0

Capítulo Livro: https://github.com/mchavesferreira/smc/blob/main/Timer_0_Livro.pdf

Código base: https://github.com/mchavesferreira/smc/blob/main/codigo_basico_timer0.pdf

Utilizando comparadores OCR:  https://github.com/mchavesferreira/smc/blob/main/exemplo_timer0_overflow_compA_CompB.c.c

Simulação Proteus e Avr Studio:  https://github.com/mchavesferreira/smc/blob/main/timer%200%20Normal%20pulsos%20quadrados.rar



## Timer 1

Capítulo Livro:  https://github.com/mchavesferreira/smc/blob/main/Timer_1_Livro.pdf

Exemplo de programação com Timer 1: 
https://github.com/mchavesferreira/smc/blob/main/interrupcao_timers/Exemplo%20Programa%C3%A7%C3%A3o%20de%20Microcontroladores.pdf

https://github.com/mchavesferreira/smc/blob/main/exemplo_Timer_1_funcoes_pwm_rapido_funcoes.c

Contador de Eventos:  https://github.com/mchavesferreira/smc/blob/main/interrupcao_timers/contador_eventos_TC1_C.zip

