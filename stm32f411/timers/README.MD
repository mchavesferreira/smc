#  Timers (Temporizadores)

O microcontrolador **STM32F411CE** possui diversos temporizadores (Timers) responsáveis por funções como:

- Geração de PWM
- Temporizações precisas
- Interrupções periódicas
- Medição de frequência
- Medição de largura de pulso
- Controle de motores
- Leitura de encoders
- Geração de sinais sincronizados

De acordo com o manual de referência **RM0383**, o STM32F411CE possui **8 timers de hardware**.

---

# Visão Geral dos Timers

| Timer | Tipo | Tamanho | Canais |
|---------|---------|---------|---------|
| TIM1 | Advanced Control | 16 bits | 4 |
| TIM2 | General Purpose | 32 bits | 4 |
| TIM3 | General Purpose | 16 bits | 4 |
| TIM4 | General Purpose | 16 bits | 4 |
| TIM5 | General Purpose | 32 bits | 4 |
| TIM9 | General Purpose | 16 bits | 2 |
| TIM10 | General Purpose | 16 bits | 1 |
| TIM11 | General Purpose | 16 bits | 1 |

---

# Organização dos Timers

## TIM1 - Advanced Control Timer

O TIM1 é o temporizador mais completo disponível no STM32F411.

### Principais recursos

- Contador de 16 bits
- Até 4 canais PWM
- PWM complementar
- Inserção de Dead-Time
- Controle de motores trifásicos
- Interface para Encoder
- Geração de interrupções
- DMA

### Aplicações típicas

- Controle de motores BLDC
- Controle de motores trifásicos
- Inversores
- Fontes chaveadas
- Servomotores

---

## TIM2 e TIM5 - Timers de 32 bits

São os maiores timers disponíveis no STM32F411.

### Características

- Contador de 32 bits
- Até 4 canais
- PWM
- Input Capture
- Output Compare
- Encoder Interface
- One Pulse Mode

### Vantagem

Como possuem contador de 32 bits, conseguem medir intervalos de tempo muito maiores sem ocorrer overflow.

### Aplicações

- Cronômetros
- Medição de frequência
- Contadores de eventos
- RTC por software

---

## TIM3 e TIM4 - Timers de 16 bits

São os timers mais utilizados em projetos embarcados.

### Características

- Contador de 16 bits
- 4 canais independentes
- PWM
- Input Capture
- Output Compare
- Encoder Interface

### Aplicações

- Controle de LEDs
- Controle de servomotores
- Leitura de sensores
- Encoders incrementais

---

General-purpose timer block diagram

<img width="867" height="631" alt="image" src="https://github.com/user-attachments/assets/94efbf7c-3e43-4c92-9841-2ca9aae2c0a0" />

## TIM9

Timer intermediário entre os timers completos e os timers simples.

### Características

- Contador de 16 bits
- 2 canais
- PWM
- Input Capture
- Output Compare

### Aplicações

- PWM adicional
- Medição de frequência
- Temporizações independentes

---

## TIM10 e TIM11

São timers compactos e independentes.

### Características

- Contador de 16 bits
- 1 canal cada
- PWM
- Input Capture
- Output Compare

### Aplicações

- PWM simples
- Temporizações independentes
- Geração de sinais periódicos

---

# Recursos Comuns dos Timers

A maioria dos timers suporta:

## PWM (Pulse Width Modulation)

Permite gerar sinais com ciclo de trabalho variável.

Aplicações:

- Controle de brilho de LEDs
- Controle de motores
- Servomotores
- Fontes chaveadas

---

## Input Capture

Captura automaticamente o valor do contador quando ocorre uma borda em uma entrada.

Aplicações:

- Medição de frequência
- Medição de período
- Medição de largura de pulso

---

## Output Compare

Compara o valor do contador com um registrador configurado.

Aplicações:

- Geração de interrupções precisas
- Agendamento de eventos

---

## One Pulse Mode

Produz apenas um único pulso após um evento de disparo.

Aplicações:

- Acionamentos temporizados
- Controle de dispositivos externos

---

## Encoder Interface

Permite conectar diretamente encoders incrementais.

Aplicações:

- Robótica
- CNC
- Impressoras 3D
- Controle de posição

---

# Quantidade Total de Canais

Somando todos os canais disponíveis:

| Timer | Canais |
|---------|---------|
| TIM1 | 4 |
| TIM2 | 4 |
| TIM3 | 4 |
| TIM4 | 4 |
| TIM5 | 4 |
| TIM9 | 2 |
| TIM10 | 1 |
| TIM11 | 1 |

**Total: 24 canais de captura/comparação/PWM.**

---

# Timers Ausentes

O STM32F411 não possui alguns timers encontrados em outros microcontroladores da família STM32.

Não estão disponíveis:

- TIM6
- TIM7
- TIM8

---

# Sugestão de Sequência de Estudos

## Etapa 1 – TIM2

Aprender:

- Base de tempo
- Prescaler
- Auto Reload Register (ARR)
- Interrupções

Projeto sugerido:

- Pisca LED sem delay()

---

## Etapa 2 – TIM3

Aprender:

- PWM

Projeto sugerido:

- Controle de brilho de LED

---

## Etapa 3 – TIM4

Aprender:

- Input Capture

Projeto sugerido:

- Medidor de frequência

---

## Etapa 4 – TIM5

Aprender:

- Temporizações longas
- Cronometragem

Projeto sugerido:

- Cronômetro digital

---

## Etapa 5 – TIM1

Aprender:

- PWM avançado
- Dead-Time
- Controle de motores

Projeto sugerido:

- Driver para motor trifásico

---

## Etapa 6 – TIM9, TIM10 e TIM11

Aprender:

- Timers auxiliares
- PWM simples
- Temporizações independentes



Documentação oficial:

https://www.st.com/en/microcontrollers-microprocessors/stm32f411ce.html
