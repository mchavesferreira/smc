### Programação em C con controle de eventos, máquinas de estados e outros

**Pontos-Chave:**
- Existem várias técnicas alternativas às máquinas de estados para programar microcontroladores em C, incluindo programação orientada a interrupções, laços de eventos e multitarefa cooperativa com corrotinas.
- Essas técnicas permitem gerenciar eventos, leituras de entrada, controle de saídas em intervalos e comunicação serial ou com displays de forma eficiente.
- A escolha da técnica depende dos requisitos do sistema, como tempo real, consumo de recursos e complexidade do código.
- A programação orientada a interrupções é amplamente utilizada por sua eficiência em sistemas de tempo real, enquanto laços de eventos e corrotinas oferecem simplicidade e flexibilidade para sistemas menos exigentes.

**Programação Orientada a Interrupções**
Essa abordagem utiliza interrupções de hardware para responder a eventos, como pressionamento de botões ou expiração de temporizadores, de forma assíncrona. É altamente eficiente, pois evita a necessidade de verificar constantemente as entradas (polling), economizando ciclos de CPU. Em C, as rotinas de serviço de interrupção (ISRs) são definidas para lidar com eventos específicos, garantindo respostas rápidas.

**Laços de Eventos**
Um laço de eventos é uma estrutura de controle que verifica continuamente a ocorrência de eventos e despacha-os para manipuladores apropriados. É ideal para microcontroladores com recursos limitados, pois opera em um único thread, simplificando a gestão de eventos como leituras de sensores ou atualizações de display.

**Multitarefa Cooperativa com Corrotinas**
Corrotinas permitem que funções cedam o controle voluntariamente, possibilitando a execução de múltiplas tarefas de forma cooperativa. Em C, isso pode ser implementado usando macros e instruções `switch` para gerenciar o estado de cada tarefa, oferecendo uma alternativa leve para sistemas sem suporte a threads.

**Escalonamento Baseado em Temporizadores**
Essa técnica utiliza temporizadores para agendar tarefas em intervalos específicos, frequentemente por meio de interrupções de temporizador. É útil para tarefas periódicas, como atualizar um display ou enviar dados seriais, e pode ser combinada com outras abordagens para maior flexibilidade.

---

### Relatório Detalhado

A programação de microcontroladores em C para controle de eventos, leitura de entradas, gerenciamento de saídas em intervalos e comunicação serial ou com displays requer técnicas que otimizem o uso de recursos limitados, como memória e ciclos de CPU. Embora as máquinas de estados sejam uma abordagem comum e eficaz, existem alternativas que podem ser igualmente eficientes, dependendo dos requisitos do sistema. Abaixo, apresento uma análise detalhada das técnicas mais conhecidas, com exemplos práticos e considerações sobre sua implementação.

#### 1. Programação Orientada a Interrupções

**Descrição**: A programação orientada a interrupções utiliza interrupções de hardware para responder a eventos externos ou internos, como mudanças em pinos de entrada, expiração de temporizadores ou recebimento de dados seriais. Quando um evento ocorre, o microcontrolador interrompe o programa principal e executa uma rotina de serviço de interrupção (ISR), que processa o evento e retorna o controle ao programa principal.

**Vantagens**:
- Resposta rápida a eventos, essencial para aplicações de tempo real.
- Reduz o consumo de CPU, pois elimina a necessidade de polling contínuo.
- Ideal para eventos assíncronos, como leituras de sensores ou comunicação serial.

**Desvantagens**:
- Requer gerenciamento cuidadoso das prioridades de interrupção para evitar conflitos.
- ISRs devem ser curtas e eficientes para não comprometer o desempenho do sistema.

**Implementação em C**:
Em microcontroladores como o 8051 ou AVR, as ISRs são definidas usando palavras-chave específicas do compilador. Por exemplo, no AVR-GCC, a macro `ISR` é usada para declarar uma ISR. Abaixo está um exemplo de código para um AVR que lida com uma interrupção de temporizador para piscar um LED:

```c
#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN PB0

void setup() {
    DDRB |= (1 << LED_PIN); // Configura o pino do LED como saída
    TCCR1B |= (1 << WGM12); // Modo CTC
    OCR1A = 15624; // Valor para 1 segundo com prescaler 1024
    TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
    TIMSK1 |= (1 << OCIE1A); // Habilita interrupção de comparação
    sei(); // Habilita interrupções globais
}

ISR(TIMER1_COMPA_vect) {
    PORTB ^= (1 << LED_PIN); // Inverte o estado do LED
}

int main(void) {
    setup();
    while (1) {
        // Loop principal vazio, interrupção lida com o LED
    }
    return 0;
}
```

**Aplicações**:
- Leitura de sensores em tempo real.
- Controle de saídas em intervalos precisos.
- Comunicação serial assíncrona.

**Referência**: [Introduction to Microcontrollers - Interrupts](https://www.embeddedrelated.com/showarticle/469.php)

#### 2. Laços de Eventos

**Descrição**: Um laço de eventos é uma estrutura de controle central que verifica continuamente a ocorrência de eventos (como mudanças em entradas ou expiração de temporizadores) e despacha-os para funções manipuladoras. É uma abordagem comum em sistemas embarcados sem sistema operacional, onde um único thread gerencia todas as tarefas.

**Vantagens**:
- Simplicidade de implementação em microcontroladores com recursos limitados.
- Consome menos memória do que sistemas multitarefa completos.
- Facilita a integração de múltiplos eventos, como leituras de sensores e atualizações de display.

**Desvantagens**:
- Pode ser menos eficiente para eventos de alta frequência, pois depende de polling.
- Requer cuidado para evitar bloqueios no laço principal.

**Implementação em C**:
Um laço de eventos pode ser implementado com um loop `while` que verifica flags ou registros de hardware. Abaixo está um exemplo que verifica um botão e atualiza um display:

```c
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN PB1
#define LED_PIN PB0

void update_display(void) {
    // Código para atualizar o display (exemplo simplificado)
}

void handle_button(void) {
    if (!(PINB & (1 << BUTTON_PIN))) { // Botão pressionado
        PORTB ^= (1 << LED_PIN); // Inverte o LED
        update_display();
    }
}

int main(void) {
    DDRB |= (1 << LED_PIN); // LED como saída
    DDRB &= ~(1 << BUTTON_PIN); // Botão como entrada
    PORTB |= (1 << BUTTON_PIN); // Habilita pull-up no botão

    while (1) {
        handle_button();
        _delay_ms(10); // Debounce
    }
    return 0;
}
```

**Aplicações**:
- Gerenciamento de interfaces de usuário simples.
- Controle de saídas periódicas, como displays.
- Monitoramento de múltiplas entradas.

**Referência**: [Event loop - Wikipedia](https://en.wikipedia.org/wiki/Event_loop)

#### 3. Multitarefa Cooperativa com Corrotinas

**Descrição**: Corrotinas são funções que podem suspender e retomar sua execução, permitindo multitarefa cooperativa. Em C, isso pode ser implementado usando macros e instruções `switch` para gerenciar o estado de cada tarefa, como descrito por Simon Tatham. As corrotinas são úteis para dividir tarefas complexas em partes menores que cedem o controle voluntariamente.

**Vantagens**:
- Permite escrever código de forma sequencial, facilitando a manutenção.
- Leve em termos de memória, ideal para microcontroladores com recursos limitados.
- Evita a complexidade de sistemas operacionais em tempo real (RTOS).

**Desvantagens**:
- Requer disciplina do programador para garantir que as tarefas cedam o controle adequadamente.
- Pode ser menos intuitivo para desenvolvedores não familiarizados com corrotinas.

**Implementação em C**:
Abaixo está um exemplo adaptado do artigo de Simon Tatham, que implementa corrotinas para gerar uma sequência de números:

```c
#include <stdio.h>

#define crBegin static int state = 0; switch(state) { case 0:
#define crReturn(x) do { state = __LINE__; return x; case __LINE__:; } while (0)
#define crFinish }

int generate_sequence(void) {
    crBegin;
    crReturn(1);
    crReturn(2);
    crReturn(3);
    crFinish;
    return 0;
}

int main(void) {
    printf("%d\n", generate_sequence());
    printf("%d\n", generate_sequence());
    printf("%d\n", generate_sequence());
    printf("%d\n", generate_sequence());
    return 0;
}
```

**Saída Esperada**:
```
1
2
3
0
```

**Aplicações**:
- Gerenciamento de tarefas que requerem pausas, como comunicação serial.
- Implementação de sequências ou iterações complexas.
- Controle de múltiplas saídas em intervalos diferentes.

**Referência**: [Coroutines in C](https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html)

#### 4. Escalonamento Baseado em Temporizadores

**Descrição**: Essa técnica utiliza temporizadores de hardware para agendar tarefas em intervalos específicos. Frequentemente, um temporizador dispara uma interrupção que executa ou agenda tarefas, permitindo controle preciso de temporização.

**Vantagens**:
- Ideal para tarefas periódicas, como atualizar displays ou enviar dados seriais.
- Pode ser combinado com interrupções para maior eficiência.
- Simples de implementar em microcontroladores com temporizadores embutidos.

**Desvantagens**:
- Pode ser complexo gerenciar múltiplos temporizadores para várias tarefas.
- Requer cuidado para evitar sobrecarga de interrupções.

**Implementação em C**:
Um exemplo para um microcontrolador 8051 que usa um temporizador para piscar um LED a cada 500ms:

```c
#include <reg51.h>

sbit LED = P1^0;

void timer0_isr(void) interrupt 1 {
    TH0 = 0x3C; // Recarrega temporizador para ~500ms
    TL0 = 0xB0;
    LED = !LED; // Inverte o LED
}

void setup(void) {
    TMOD = 0x01; // Temporizador 0, modo 1 (16 bits)
    TH0 = 0x3C; // Valor inicial para 500ms
    TL0 = 0xB0;
    TR0 = 1; // Inicia o temporizador
    ET0 = 1; // Habilita interrupção do temporizador 0
    EA = 1; // Habilita interrupções globais
}

void main(void) {
    setup();
    while (1) {
        // Loop principal vazio
    }
}
```

**Aplicações**:
- Atualização periódica de displays.
- Envio de dados seriais em intervalos regulares.
- Controle de saídas com temporização precisa.

**Referência**: [Interrupts short and simple: Part 1 - Good programming practices](https://www.embedded.com/interrupts-short-and-simple-part-1-good-programming-practices/)

#### Comparação das Técnicas

| Técnica                          | Vantagens                                                                 | Desvantagens                                                                | Casos de Uso Ideais                                      |
|----------------------------------|---------------------------------------------------------------------------|-----------------------------------------------------------------------------|---------------------------------------------------------|
| **Interrupções**                 | Resposta rápida, eficiente em CPU, ideal para tempo real                  | Complexidade no gerenciamento de prioridades, ISRs devem ser curtas          | Sensores, comunicação serial, eventos assíncronos        |
| **Laços de Eventos**             | Simples, baixo consumo de memória, fácil de implementar                   | Menos eficiente para eventos frequentes, risco de bloqueio                  | Interfaces simples, monitoramento de entradas            |
| **Corrotinas**                   | Código sequencial, leve, flexível                                         | Requer disciplina para ceder controle, menos intuitivo                      | Tarefas complexas com pausas, sequências                |
| **Escalonamento por Temporizador**| Controle preciso de temporização, combina bem com interrupções            | Complexidade com múltiplos temporizadores, sobrecarga de interrupções        | Tarefas periódicas, atualizações de display             |

#### Considerações para Otimização

- **Eficiência de Recursos**: Em microcontroladores com memória limitada (como PIC ou MSP430), corrotinas e laços de eventos são preferíveis devido ao baixo consumo de memória. Interrupções são ideais para sistemas de tempo real, mas requerem ISRs otimizadas.
- **Escalabilidade**: Laços de eventos são escaláveis para sistemas simples, enquanto corrotinas podem gerenciar tarefas mais complexas. Para sistemas muito complexos, frameworks como QP podem ser considerados, embora usem máquinas de estados internamente.
- **Manutenção do Código**: Corrotinas permitem um código mais legível, enquanto interrupções podem ser mais difíceis de depurar devido à natureza assíncrona.

#### Conclusão

As técnicas apresentadas — programação orientada a interrupções, laços de eventos, multitarefa cooperativa com corrotinas e escalonamento baseado em temporizadores — oferecem alternativas robustas às máquinas de estados para programar microcontroladores em C. A escolha depende dos requisitos específicos do projeto, como tempo real, consumo de recursos e complexidade. Interrupções são ideais para respostas rápidas, laços de eventos para simplicidade, corrotinas para flexibilidade e temporizadores para tarefas periódicas. Cada técnica pode ser adaptada para gerenciar eventos, entradas, saídas e comunicações, garantindo um controle otimizado do programa.

**Key Citations:**
- [Introduction to Microcontrollers - Interrupts](https://www.embeddedrelated.com/showarticle/469.php)
- [Event loop - Wikipedia](https://en.wikipedia.org/wiki/Event_loop)
- [Coroutines in C](https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html)
- [Interrupts short and simple: Part 1 - Good programming practices](https://www.embedded.com/interrupts-short-and-simple-part-1-good-programming-practices/)
