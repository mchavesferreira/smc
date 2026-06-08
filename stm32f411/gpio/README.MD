# 1. Instrodução aos GPIO


## Registradores de controle do GPIO

rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics-1.pdf (cap. 8, p.146)

### Descrição funcional dos GPIOs

Sujeito às características específicas de hardware de cada porta de E/S listadas no datasheet, cada bit das portas de entrada/saída de propósito geral (**GPIO**) pode ser configurado individualmente por software em vários modos:

* Entrada flutuante
* Entrada com pull-up
* Entrada com pull-down
* Analógico
* Saída open-drain com capacidade de pull-up ou pull-down
* Saída push-pull com capacidade de pull-up ou pull-down
* Função alternativa push-pull com capacidade de pull-up ou pull-down
* Função alternativa open-drain com capacidade de pull-up ou pull-down

<img width="1135" height="644" alt="image" src="https://github.com/user-attachments/assets/58aa660a-fa2f-4068-bc52-89017be0c768" />


### MODER (Mode Register)

O registrador **MODER** define o modo de operação de cada pino da porta GPIO. Cada pino utiliza dois bits para determinar sua função, podendo ser configurado como **entrada digital (Input)**, **saída digital (Output)**, **função alternativa (Alternate Function)** ou **modo analógico (Analog)**. No STM32F411, esse registrador é normalmente o primeiro a ser configurado, pois determina como o hardware interno irá conectar o pino aos circuitos de entrada, saída, periféricos ou conversores analógicos.

### OTYPER (Output Type Register)

O registrador **OTYPER** define o tipo de saída utilizado quando o pino está configurado como saída digital ou função alternativa. Cada pino possui um bit que permite selecionar entre **Push-Pull** (empurra para nível alto e baixo através dos transistores internos) ou **Open-Drain** (apenas força nível baixo, exigindo um resistor pull-up externo ou interno para gerar nível alto). O modo Push-Pull é o mais comum para LEDs e acionamentos gerais, enquanto Open-Drain é amplamente utilizado em barramentos como o I²C.

### OSPEEDR (Output Speed Register)

O registrador **OSPEEDR** controla a velocidade de comutação dos transistores de saída do GPIO. Cada pino possui dois bits que permitem selecionar níveis de velocidade como **Low Speed**, **Medium Speed**, **High Speed** ou **Very High Speed**. Embora seja frequentemente interpretado como frequência, esse registrador controla principalmente a taxa de subida e descida dos sinais elétricos. Velocidades mais altas permitem sinais mais rápidos, porém aumentam consumo de energia, ruído eletromagnético (EMI) e possibilidade de interferências.

### PUPDR (Pull-Up/Pull-Down Register)

O registrador **PUPDR** habilita ou desabilita os resistores internos de polarização dos pinos GPIO. Cada pino pode ser configurado como **sem resistor (No Pull)**, **Pull-Up** (ligado internamente ao VDD) ou **Pull-Down** (ligado internamente ao GND). Esses resistores são importantes para evitar estados indefinidos ("flutuantes") em entradas digitais quando nenhum sinal externo está conectado. Por exemplo, um botão ligado ao GND normalmente utiliza Pull-Up interno, mantendo a entrada em nível lógico alto enquanto o botão não é pressionado.

### Resumo Prático

| Registrador | Função Principal                                                      |
| ----------- | --------------------------------------------------------------------- |
| **MODER**   | Define se o pino será Entrada, Saída, Função Alternativa ou Analógico |
| **OTYPER**  | Define o tipo de saída: Push-Pull ou Open-Drain                       |
| **OSPEEDR** | Ajusta a velocidade de comutação dos sinais de saída                  |
| **PUPDR**   | Configura resistores internos Pull-Up ou Pull-Down                    |

Uma forma simples de lembrar é:

**MODER → O que o pino faz**
**OTYPER → Como ele gera a saída**
**OSPEEDR → Quão rápido ele muda de estado**
**PUPDR → Como ele se comporta quando ninguém está acionando o pino**

Esses quatro registradores são os principais responsáveis pela configuração elétrica e funcional dos GPIOs do STM32F411.
