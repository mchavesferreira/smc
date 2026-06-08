# STM32F411CE (Black Pill)

## Descrição

O **STM32F411CE** é um microcontrolador de alto desempenho da família STM32 baseado no núcleo **ARM Cortex-M4**, operando em até **100 MHz**. Possui recursos avançados para aplicações embarcadas, incluindo suporte a **DSP (Digital Signal Processing)** e **FPU (Floating Point Unit)** para operações matemáticas em ponto flutuante.

### Principais Características

* Núcleo ARM Cortex-M4 de 32 bits
* Frequência de operação de até 100 MHz
* 512 kB de memória Flash
* 128 kB de SRAM
* Unidade DSP integrada
* FPU (Floating Point Unit)
* ART Accelerator (Acelerador de acesso à memória Flash)
* Interfaces UART, SPI, I2C, I2S, ADC, DMA, Timers e GPIO

---

<a href=imagens/blackpill.png><img src=imagens/blackpill.png width=300 height=300 border=0></a>

## Tópicos

* Arquitetura ARM Cortex-M4
* Organização da memória Flash e SRAM
* Clock do sistema e PLL
* Estrutura de um projeto STM32CubeIDE
* <a href=hall.md>Biblioteca Hall </a>
* <a href=https://github.com/mchavesferreira/smc/blob/main/stm32f411/gpio>GPIO</a>
* <a href=https://github.com/mchavesferreira/smc/blob/main/stm32f411/interrupcoes>Interrupções e NVIC</a>
* <a href=https://github.com/mchavesferreira/smc/blob/main/stm32f411/timers>Timers e PWM</a>
* UART
* SPI
* <a href=https://github.com/mchavesferreira/smc/tree/main/stm32f411/oled>I2C e display Oled</a>
* <a href=https://github.com/mchavesferreira/smc/tree/main/stm32f411/adc>ADC e DMA</a>
* Modos de baixo consumo
* Debug via SWD


---

## Documentação Oficial

### Página do Fabricante (STMicroelectronics)

[https://www.st.com/en/microcontrollers-microprocessors/stm32f411ce.html](https://www.st.com/en/microcontrollers-microprocessors/stm32f411ce.html)

---

## Repositório de Exemplos para STM32F411CEU6

[https://github.com/embeddedalpha/STM32F411CEU6](https://github.com/embeddedalpha/STM32F411CEU6)

Este repositório contém exemplos de utilização dos periféricos do STM32F411 utilizando STM32CubeIDE.

---

## Exemplos para Franzininho Cortex-M0+

Embora voltado ao STM32C0 (Cortex-M0+), este repositório apresenta exemplos úteis para compreender a estrutura dos projetos STM32 gerados pelo STM32CubeIDE.

[https://github.com/Franzininho/Franzininho-C0-Com-STM32CubeIDE-Artigos/tree/master](https://github.com/Franzininho/Franzininho-C0-Com-STM32CubeIDE-Artigos/tree/master)

---

## Informações sobre a Placa Black Pill

Documentação e informações adicionais sobre a placa Black Pill baseada no STM32F411:

[https://github.com/trebisky/stm32f411](https://github.com/trebisky/stm32f411)

---

## Esquema Elétrico da Black Pill

Diagrama esquemático da placa WeAct Black Pill V2.0:

[http://cholla.mmto.org/stm32all/black_pill/WeAct_Black_Pill_V2.0_schematic.pdf](http://cholla.mmto.org/stm32all/black_pill/WeAct_Black_Pill_V2.0_schematic.pdf)

---

## Ferramentas Recomendadas

* STM32CubeIDE
* STM32CubeMX
* STM32CubeProgrammer

---



## Placa Utilizada

**Black Pill STM32F411CEU6**

* Microcontrolador: STM32F411CEU6
* Arquitetura: ARM Cortex-M4
* Clock máximo: 100 MHz
* Flash: 512 kB
* SRAM: 128 kB
* Tensão de operação: 3,3 V
* Interface de programação: SWD
* Conector USB para alimentação e comunicação



## Gravador ST-Link V2


<img src=imagens/stm32-st-link-v2-arduino.png>


## Documentação Biblioteca HAL
UM1725  Description of STM32F4 HAL and low-layer drivers

https://www.st.com/resource/en/user_manual/um1725-description-of-stm32f4-hal-and-lowlayer-drivers-stmicroelectronics.pdf

