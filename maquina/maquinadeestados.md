# Máquinas de Estados com Switch Case para ATmega328P

## Introdução

As máquinas de estados finitas (FSM - Finite State Machines) representam uma das técnicas mais fundamentais e amplamente utilizadas para controle de eventos em sistemas embarcados. Esta abordagem oferece uma forma estruturada e intuitiva de organizar o comportamento do sistema através de estados bem definidos e transições controladas.

## Características Fundamentais

### Definição e Conceitos

Uma máquina de estados finita é um modelo matemático que representa um sistema com:
- **Estados**: Condições ou situações específicas do sistema
- **Eventos**: Estímulos externos ou internos que podem causar mudanças
- **Transições**: Mudanças de um estado para outro baseadas em eventos
- **Ações**: Operações executadas durante estados ou transições

### Vantagens da Implementação com Switch Case

1. **Clareza de Código**: Estrutura visual clara das transições de estado
2. **Facilidade de Manutenção**: Modificações localizadas em casos específicos
3. **Eficiência**: Compiladores otimizam switch statements eficientemente
4. **Debugabilidade**: Estados são facilmente identificáveis durante depuração
5. **Escalabilidade**: Novos estados podem ser adicionados facilmente

## Implementação Prática no ATmega328P

### Estrutura Básica

```c
#include <avr/io.h>
#include <util/delay.h>

// Definição dos estados usando enum
typedef enum {
    STATE_IDLE = 0,
    STATE_ACTIVE = 1,
    STATE_PROCESSING = 2,
    STATE_ERROR = 3
} system_state_t;

// Variável global para estado atual
system_state_t current_state = STATE_IDLE;

int main(void) {
    // Inicializações
    setup_gpio();
    
    while(1) {
        // Máquina de estados principal
        switch(current_state) {
            case STATE_IDLE:
                handle_idle_state();
                break;
                
            case STATE_ACTIVE:
                handle_active_state();
                break;
                
            case STATE_PROCESSING:
                handle_processing_state();
                break;
                
            case STATE_ERROR:
                handle_error_state();
                break;
                
            default:
                // Estado inválido - volta ao estado seguro
                current_state = STATE_IDLE;
                break;
        }
        
        _delay_ms(10); // Delay do loop principal
    }
}
```

### Exemplo Avançado: Sistema de Controle de Motor

```c
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

// Estados do sistema de controle
typedef enum {
    MOTOR_STOPPED = 0,
    MOTOR_STARTING = 1,
    MOTOR_RUNNING = 2,
    MOTOR_STOPPING = 3,
    MOTOR_ERROR = 4
} motor_state_t;

// Eventos do sistema
typedef enum {
    EVENT_NONE = 0,
    EVENT_START_REQUESTED = 1,
    EVENT_STOP_REQUESTED = 2,
    EVENT_SPEED_REACHED = 3,
    EVENT_OVERCURRENT = 4,
    EVENT_TIMEOUT = 5
} motor_event_t;

// Variáveis globais
motor_state_t current_motor_state = MOTOR_STOPPED;
motor_event_t pending_event = EVENT_NONE;
uint16_t motor_speed = 0;
uint16_t target_speed = 0;
uint32_t state_timer = 0;

// Definições de pinos
#define START_BUTTON    PD2
#define STOP_BUTTON     PD3
#define MOTOR_PWM       PB1
#define STATUS_LED      PB5
#define ERROR_LED       PB4

void setup_motor_system(void) {
    // Configura botões como entrada
    DDRD &= ~((1 << START_BUTTON) | (1 << STOP_BUTTON));
    PORTD |= ((1 << START_BUTTON) | (1 << STOP_BUTTON)); // Pull-ups
    
    // Configura LEDs como saída
    DDRB |= ((1 << STATUS_LED) | (1 << ERROR_LED));
    
    // Configura PWM para motor (Timer1)
    DDRB |= (1 << MOTOR_PWM);
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
    ICR1 = 399; // Frequência PWM ~10kHz
    OCR1A = 0;  // Duty cycle inicial 0%
    
    // Configura ADC para leitura de corrente
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

motor_event_t check_events(void) {
    // Verifica botões
    if(!(PIND & (1 << START_BUTTON))) {
        _delay_ms(20); // Debounce
        if(!(PIND & (1 << START_BUTTON))) {
            return EVENT_START_REQUESTED;
        }
    }
    
    if(!(PIND & (1 << STOP_BUTTON))) {
        _delay_ms(20); // Debounce
        if(!(PIND & (1 << STOP_BUTTON))) {
            return EVENT_STOP_REQUESTED;
        }
    }
    
    // Verifica sobrecorrente via ADC
    ADCSRA |= (1 << ADSC);
    while(ADCSRA & (1 << ADSC));
    uint16_t current_reading = ADC;
    
    if(current_reading > 900) { // Threshold de sobrecorrente
        return EVENT_OVERCURRENT;
    }
    
    // Verifica se velocidade alvo foi atingida
    if(current_motor_state == MOTOR_STARTING && motor_speed >= target_speed) {
        return EVENT_SPEED_REACHED;
    }
    
    // Verifica timeout
    if(state_timer > 10000) { // 10 segundos
        return EVENT_TIMEOUT;
    }
    
    return EVENT_NONE;
}

void set_motor_speed(uint16_t speed_percent) {
    if(speed_percent > 100) speed_percent = 100;
    OCR1A = (speed_percent * ICR1) / 100;
    motor_speed = speed_percent;
}

void update_status_leds(void) {
    switch(current_motor_state) {
        case MOTOR_STOPPED:
            PORTB &= ~(1 << STATUS_LED);
            PORTB &= ~(1 << ERROR_LED);
            break;
            
        case MOTOR_STARTING:
        case MOTOR_RUNNING:
            PORTB |= (1 << STATUS_LED);
            PORTB &= ~(1 << ERROR_LED);
            break;
            
        case MOTOR_STOPPING:
            // Pisca LED de status
            PORTB ^= (1 << STATUS_LED);
            PORTB &= ~(1 << ERROR_LED);
            break;
            
        case MOTOR_ERROR:
            PORTB &= ~(1 << STATUS_LED);
            PORTB |= (1 << ERROR_LED);
            break;
    }
}

int main(void) {
    setup_motor_system();
    
    while(1) {
        // Verifica eventos pendentes
        pending_event = check_events();
        
        // Máquina de estados do motor
        switch(current_motor_state) {
            case MOTOR_STOPPED:
                set_motor_speed(0);
                
                if(pending_event == EVENT_START_REQUESTED) {
                    current_motor_state = MOTOR_STARTING;
                    target_speed = 80; // 80% da velocidade máxima
                    state_timer = 0;
                }
                break;
                
            case MOTOR_STARTING:
                // Aceleração gradual
                if(motor_speed < target_speed) {
                    set_motor_speed(motor_speed + 2);
                    _delay_ms(50);
                }
                
                if(pending_event == EVENT_SPEED_REACHED) {
                    current_motor_state = MOTOR_RUNNING;
                    state_timer = 0;
                } else if(pending_event == EVENT_STOP_REQUESTED || 
                         pending_event == EVENT_TIMEOUT) {
                    current_motor_state = MOTOR_STOPPING;
                    state_timer = 0;
                } else if(pending_event == EVENT_OVERCURRENT) {
                    current_motor_state = MOTOR_ERROR;
                    state_timer = 0;
                }
                break;
                
            case MOTOR_RUNNING:
                // Mantém velocidade constante
                
                if(pending_event == EVENT_STOP_REQUESTED) {
                    current_motor_state = MOTOR_STOPPING;
                    state_timer = 0;
                } else if(pending_event == EVENT_OVERCURRENT) {
                    current_motor_state = MOTOR_ERROR;
                    state_timer = 0;
                }
                break;
                
            case MOTOR_STOPPING:
                // Desaceleração gradual
                if(motor_speed > 0) {
                    set_motor_speed(motor_speed - 5);
                    _delay_ms(30);
                } else {
                    current_motor_state = MOTOR_STOPPED;
                    state_timer = 0;
                }
                
                if(pending_event == EVENT_OVERCURRENT) {
                    current_motor_state = MOTOR_ERROR;
                    set_motor_speed(0); // Para imediatamente
                    state_timer = 0;
                }
                break;
                
            case MOTOR_ERROR:
                set_motor_speed(0); // Para motor imediatamente
                
                // Auto-recuperação após 5 segundos se condição de erro não persistir
                if(state_timer > 5000 && pending_event != EVENT_OVERCURRENT) {
                    current_motor_state = MOTOR_STOPPED;
                    state_timer = 0;
                }
                break;
                
            default:
                // Estado inválido - vai para estado seguro
                current_motor_state = MOTOR_ERROR;
                set_motor_speed(0);
                state_timer = 0;
                break;
        }
        
        update_status_leds();
        state_timer++;
        _delay_ms(1);
    }
    
    return 0;
}
```

### Exemplo Simplificado: Controle de LED com Botões

```c
#include <avr/io.h>
#include <util/delay.h>

// Estados do sistema LED
typedef enum {
    LED_OFF = 0,
    LED_RED = 1,
    LED_BLUE = 2,
    LED_GREEN = 3
} led_state_t;

led_state_t current_state = LED_OFF;
led_state_t next_state = LED_RED;

// Pinos
#define ON_OFF_BUTTON   PD2
#define COLOR_BUTTON    PD3
#define RED_LED         PB0
#define BLUE_LED        PB1
#define GREEN_LED       PB2

void setup_leds(void) {
    // Botões como entrada com pull-up
    DDRD &= ~((1 << ON_OFF_BUTTON) | (1 << COLOR_BUTTON));
    PORTD |= ((1 << ON_OFF_BUTTON) | (1 << COLOR_BUTTON));
    
    // LEDs como saída
    DDRB |= ((1 << RED_LED) | (1 << BLUE_LED) | (1 << GREEN_LED));
    PORTB &= ~((1 << RED_LED) | (1 << BLUE_LED) | (1 << GREEN_LED));
}

void update_leds(led_state_t state) {
    // Desliga todos os LEDs
    PORTB &= ~((1 << RED_LED) | (1 << BLUE_LED) | (1 << GREEN_LED));
    
    // Liga LED específico
    switch(state) {
        case LED_RED:
            PORTB |= (1 << RED_LED);
            break;
        case LED_BLUE:
            PORTB |= (1 << BLUE_LED);
            break;
        case LED_GREEN:
            PORTB |= (1 << GREEN_LED);
            break;
        case LED_OFF:
        default:
            // Todos desligados
            break;
    }
}

int main(void) {
    setup_leds();
    
    while(1) {
        switch(current_state) {
            case LED_OFF:
                if(!(PIND & (1 << ON_OFF_BUTTON))) {
                    current_state = next_state;
                    update_leds(current_state);
                    _delay_ms(200); // Debounce
                }
                break;
                
            case LED_RED:
                if(!(PIND & (1 << ON_OFF_BUTTON))) {
                    current_state = LED_OFF;
                    next_state = LED_RED;
                    update_leds(current_state);
                    _delay_ms(200);
                } else if(!(PIND & (1 << COLOR_BUTTON))) {
                    current_state = LED_BLUE;
                    update_leds(current_state);
                    _delay_ms(200);
                }
                break;
                
            case LED_BLUE:
                if(!(PIND & (1 << ON_OFF_BUTTON))) {
                    current_state = LED_OFF;
                    next_state = LED_RED;
                    update_leds(current_state);
                    _delay_ms(200);
                } else if(!(PIND & (1 << COLOR_BUTTON))) {
                    current_state = LED_GREEN;
                    update_leds(current_state);
                    _delay_ms(200);
                }
                break;
                
            case LED_GREEN:
                if(!(PIND & (1 << ON_OFF_BUTTON))) {
                    current_state = LED_OFF;
                    next_state = LED_RED;
                    update_leds(current_state);
                    _delay_ms(200);
                } else if(!(PIND & (1 << COLOR_BUTTON))) {
                    current_state = LED_RED;
                    update_leds(current_state);
                    _delay_ms(200);
                }
                break;
                
            default:
                current_state = LED_OFF;
                update_leds(current_state);
                break;
        }
        
        _delay_ms(50);
    }
    
    return 0;
}
```

## Boas Práticas de Implementação

### 1. Uso de Enums para Estados
```c
typedef enum {
    STATE_INIT = 0,
    STATE_READY = 1,
    STATE_ACTIVE = 2,
    STATE_ERROR = 99
} system_state_t;
```

### 2. Estado Default de Segurança
```c
default:
    // Sempre incluir tratamento para estados inválidos
    current_state = SAFE_STATE;
    log_error("Invalid state detected");
    break;
```

### 3. Separação de Verificação de Eventos
```c
event_t check_system_events(void) {
    // Centraliza verificação de todos os eventos
    // Retorna evento prioritário
}
```

### 4. Funções de Estado Separadas
```c
void handle_idle_state(void) {
    // Código específico do estado IDLE
    if(button_pressed()) {
        current_state = STATE_ACTIVE;
    }
}
```

## Comparação com Outras Técnicas

| Aspecto | Switch Case FSM | Interrupções | Event Loop | Corrotinas |
|---------|----------------|--------------|------------|------------|
| **Complexidade** | Baixa | Média | Baixa | Alta |
| **Latência** | Média (ms) | Muito baixa (μs) | Média-Alta | Média |
| **Uso de Memória** | Baixo | Baixo | Baixo | Médio |
| **Manutenibilidade** | Muito alta | Média | Alta | Média |
| **Escalabilidade** | Alta | Baixa | Média | Alta |

## Aplicações Práticas

### 1. Interfaces de Usuário
- Menus hierárquicos
- Controle de displays
- Navegação por botões

### 2. Controle de Processos
- Sequências de inicialização
- Protocolos de comunicação
- Controle de motores

### 3. Sistemas de Segurança
- Monitoramento de sensores
- Alarmes e alertas
- Procedimentos de emergência

## Limitações e Considerações

### 1. Limitações
- Não é adequado para tempo real crítico
- Estados muito complexos podem tornar switch statements extensos
- Dificulta compartilhamento de código entre estados

### 2. Quando Não Usar
- Sistemas com requisitos de tempo real rígidos
- Aplicações com muitos estados aninhados
- Quando eventos são muito frequentes (>1kHz)

## Conclusão

As máquinas de estados implementadas com switch case representam uma técnica fundamental para organização de código em sistemas embarcados. Oferecem excelente balance entre simplicidade, manutenibilidade e eficiência, sendo especialmente adequadas para sistemas de controle, interfaces de usuário e protocolos de comunicação no ATmega328P.

A escolha desta técnica deve considerar os requisitos temporais, complexidade do sistema e necessidades de manutenção do projeto, combinando-a adequadamente com outras técnicas quando necessário.
