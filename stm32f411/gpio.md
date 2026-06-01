# Registradores de controle do GPIO

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

## Multi-AHB matrix 
<img width="710" height="175" alt="image" src="https://github.com/user-attachments/assets/70ee6e86-39b6-4775-bcf8-77ca769c835d" />

A Bus Matrix AHB do STM32F411 é uma estrutura interna de interconexão de 32 bits que liga os mestres (CPU e controladores DMA) aos escravos (Flash, SRAM e periféricos). Ela funciona como um sistema inteligente de roteamento de dados, permitindo múltiplos acessos simultâneos aos recursos do microcontrolador, reduzindo gargalos e aumentando o desempenho quando diversos periféricos operam ao mesmo tempo.
<img width="1480" height="924" alt="image" src="https://github.com/user-attachments/assets/6ec84e67-ff57-44d5-a58a-e78983849bd9" />

## NVIC (Nested Vectored Interrupt Controller)

O NVIC é o controlador de interrupções integrado ao núcleo ARM Cortex-M4 do STM32F411. Sua função é gerenciar todas as interrupções do sistema de forma rápida e eficiente, permitindo que eventos importantes sejam atendidos imediatamente sem a necessidade de o programa principal ficar verificando constantemente o estado dos periféricos.

O NVIC do STM32F411 suporta até 62 interrupções externas mascaráveis, além das 16 exceções internas do Cortex-M4, e permite definir 16 níveis de prioridade. Quando uma interrupção ocorre, o hardware identifica automaticamente qual rotina deve ser executada através da tabela de vetores, salva o contexto do processador e transfere o controle para a função de tratamento (ISR).

## Mapeamento das Funções Alternativas (Alternate Functions - AF) dos pinos GPIO
A tabela Alternate Function Mapping informa qual valor AF (AF0 a AF15) deve ser programado nos registradores AFRL/AFRH para conectar um periférico interno a um determinado pino GPIO. Por exemplo, AF7 conecta os periféricos USART1 e USART2, AF5 conecta SPI1 e SPI2, e AF4 conecta os módulos I²C. Ao configurar um pino para função alternativa, o registrador MODER deve ser ajustado para o modo Alternate Function e o registrador AFR deve receber o número AF correspondente ao periférico desejado. Isso permite que um mesmo pino físico desempenhe diferentes funções conforme a necessidade da aplicação.



