/*
 * Semáforo Inteligente com Máquina de Estados
 * ATmega328P - Exemplo Prático de FSM com Switch Case
 * 
 * Descrição: Sistema de semáforo que detecta pedestres e veículos
 * Estados: VERDE, AMARELO, VERMELHO, PEDESTRE_VERDE, EMERGENCIA
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

// Definição dos estados do semáforo
typedef enum {
    VERDE_VEICULO = 0,
    AMARELO_VEICULO = 1,
    VERMELHO_VEICULO = 2,
    VERDE_PEDESTRE = 3,
    EMERGENCIA = 4
} semaforo_state_t;

// Eventos do sistema
typedef enum {
    EVENTO_NENHUM = 0,
    EVENTO_TIMEOUT = 1,
    EVENTO_PEDESTRE = 2,
    EVENTO_EMERGENCIA = 3,
    EVENTO_VEICULO_DETECTADO = 4,
    EVENTO_FIM_EMERGENCIA = 5
} semaforo_event_t;

// Configuração de tempos (em decisegundos para facilitar contagem)
#define TEMPO_VERDE_VEICULO     300  // 30 segundos
#define TEMPO_AMARELO_VEICULO   50   // 5 segundos
#define TEMPO_VERMELHO_VEICULO  50   // 5 segundos
#define TEMPO_VERDE_PEDESTRE    200  // 20 segundos
#define TEMPO_MINIMO_VERDE      100  // 10 segundos mínimo

// Definições de pinos
#define LED_VERDE_VEICULO    PB0
#define LED_AMARELO_VEICULO  PB1
#define LED_VERMELHO_VEICULO PB2
#define LED_VERDE_PEDESTRE   PB3
#define LED_VERMELHO_PEDESTRE PB4

#define BOTAO_PEDESTRE       PD2  // INT0
#define SENSOR_VEICULO       PD3  // INT1
#define BOTAO_EMERGENCIA     PD4
#define BUZZER              PD5

// Variáveis globais
volatile semaforo_state_t estado_atual = VERDE_VEICULO;
volatile semaforo_event_t evento_pendente = EVENTO_NENHUM;
volatile uint16_t contador_tempo = 0;
volatile bool pedestre_aguardando = false;
volatile bool veiculo_detectado = false;
volatile bool emergencia_ativa = false;

// Função de configuração inicial
void setup_semaforo(void) {
    // Configura LEDs como saída
    DDRB |= (1 << LED_VERDE_VEICULO) | (1 << LED_AMARELO_VEICULO) | 
            (1 << LED_VERMELHO_VEICULO) | (1 << LED_VERDE_PEDESTRE) | 
            (1 << LED_VERMELHO_PEDESTRE);

    // Configura buzzer como saída
    DDRD |= (1 << BUZZER);

    // Configura botões e sensores como entrada
    DDRD &= ~((1 << BOTAO_PEDESTRE) | (1 << SENSOR_VEICULO) | (1 << BOTAO_EMERGENCIA));
    PORTD |= ((1 << BOTAO_PEDESTRE) | (1 << SENSOR_VEICULO) | (1 << BOTAO_EMERGENCIA));

    // Configura interrupções externas
    EICRA |= (1 << ISC01) | (1 << ISC11); // Falling edge para INT0 e INT1
    EIMSK |= (1 << INT0) | (1 << INT1);   // Habilita INT0 e INT1

    // Configura Timer0 para base de tempo (100ms)
    TCCR0A = (1 << WGM01); // CTC mode
    TCCR0B = (1 << CS02) | (1 << CS00); // Prescaler 1024
    OCR0A = 155; // ~100ms com 16MHz/1024
    TIMSK0 |= (1 << OCIE0A); // Habilita interrupção de comparação

    sei(); // Habilita interrupções globais
}

// ISR para botão de pedestre (INT0)
ISR(INT0_vect) {
    static uint8_t debounce_counter = 0;

    _delay_ms(50); // Debounce básico
    if(!(PIND & (1 << BOTAO_PEDESTRE))) {
        pedestre_aguardando = true;
        if(evento_pendente == EVENTO_NENHUM) {
            evento_pendente = EVENTO_PEDESTRE;
        }
    }
}

// ISR para sensor de veículo (INT1)
ISR(INT1_vect) {
    veiculo_detectado = true;
    if(evento_pendente == EVENTO_NENHUM) {
        evento_pendente = EVENTO_VEICULO_DETECTADO;
    }
}

// ISR para timer (base de tempo)
ISR(TIMER0_COMPA_vect) {
    contador_tempo++;

    // Verifica botão de emergência (polling)
    static uint8_t emergencia_counter = 0;
    if(!(PIND & (1 << BOTAO_EMERGENCIA))) {
        emergencia_counter++;
        if(emergencia_counter > 20) { // 2 segundos pressionado
            emergencia_ativa = true;
            evento_pendente = EVENTO_EMERGENCIA;
            emergencia_counter = 0;
        }
    } else {
        emergencia_counter = 0;
        if(emergencia_ativa) {
            emergencia_ativa = false;
            evento_pendente = EVENTO_FIM_EMERGENCIA;
        }
    }
}

// Função para atualizar LEDs
void atualizar_leds(semaforo_state_t estado) {
    // Desliga todos os LEDs
    PORTB &= ~((1 << LED_VERDE_VEICULO) | (1 << LED_AMARELO_VEICULO) | 
               (1 << LED_VERMELHO_VEICULO) | (1 << LED_VERDE_PEDESTRE) | 
               (1 << LED_VERMELHO_PEDESTRE));

    switch(estado) {
        case VERDE_VEICULO:
            PORTB |= (1 << LED_VERDE_VEICULO) | (1 << LED_VERMELHO_PEDESTRE);
            break;

        case AMARELO_VEICULO:
            PORTB |= (1 << LED_AMARELO_VEICULO) | (1 << LED_VERMELHO_PEDESTRE);
            break;

        case VERMELHO_VEICULO:
            PORTB |= (1 << LED_VERMELHO_VEICULO) | (1 << LED_VERMELHO_PEDESTRE);
            break;

        case VERDE_PEDESTRE:
            PORTB |= (1 << LED_VERMELHO_VEICULO) | (1 << LED_VERDE_PEDESTRE);
            // Buzzer para deficientes visuais
            if((contador_tempo % 10) < 5) {
                PORTD |= (1 << BUZZER);
            } else {
                PORTD &= ~(1 << BUZZER);
            }
            break;

        case EMERGENCIA:
            // Pisca vermelho para veículos e pedestres
            if((contador_tempo % 5) < 3) {
                PORTB |= (1 << LED_VERMELHO_VEICULO) | (1 << LED_VERMELHO_PEDESTRE);
            }
            break;
    }
}

// Função para verificar timeouts
semaforo_event_t verificar_timeout(void) {
    static uint16_t tempo_estado = 0;

    switch(estado_atual) {
        case VERDE_VEICULO:
            if(contador_tempo - tempo_estado >= TEMPO_VERDE_VEICULO) {
                return EVENTO_TIMEOUT;
            }
            // Permite mudança antecipada se pedestre aguarda e tempo mínimo passou
            if(pedestre_aguardando && 
               (contador_tempo - tempo_estado >= TEMPO_MINIMO_VERDE)) {
                return EVENTO_PEDESTRE;
            }
            break;

        case AMARELO_VEICULO:
            if(contador_tempo - tempo_estado >= TEMPO_AMARELO_VEICULO) {
                return EVENTO_TIMEOUT;
            }
            break;

        case VERMELHO_VEICULO:
            if(contador_tempo - tempo_estado >= TEMPO_VERMELHO_VEICULO) {
                return EVENTO_TIMEOUT;
            }
            break;

        case VERDE_PEDESTRE:
            if(contador_tempo - tempo_estado >= TEMPO_VERDE_PEDESTRE) {
                return EVENTO_TIMEOUT;
            }
            break;

        case EMERGENCIA:
            // Emergência não tem timeout automático
            break;
    }

    // Atualiza tempo do estado se mudou
    static semaforo_state_t ultimo_estado = VERDE_VEICULO;
    if(estado_atual != ultimo_estado) {
        tempo_estado = contador_tempo;
        ultimo_estado = estado_atual;
    }

    return EVENTO_NENHUM;
}

// Função principal de tratamento de eventos
void processar_evento(semaforo_event_t evento) {
    switch(estado_atual) {
        case VERDE_VEICULO:
            if(evento == EVENTO_TIMEOUT) {
                estado_atual = AMARELO_VEICULO;
            } else if(evento == EVENTO_PEDESTRE) {
                estado_atual = AMARELO_VEICULO;
            } else if(evento == EVENTO_EMERGENCIA) {
                estado_atual = EMERGENCIA;
            }
            break;

        case AMARELO_VEICULO:
            if(evento == EVENTO_TIMEOUT) {
                if(pedestre_aguardando) {
                    estado_atual = VERDE_PEDESTRE;
                    pedestre_aguardando = false;
                } else {
                    estado_atual = VERMELHO_VEICULO;
                }
            } else if(evento == EVENTO_EMERGENCIA) {
                estado_atual = EMERGENCIA;
            }
            break;

        case VERMELHO_VEICULO:
            if(evento == EVENTO_TIMEOUT) {
                estado_atual = VERDE_VEICULO;
            } else if(evento == EVENTO_EMERGENCIA) {
                estado_atual = EMERGENCIA;
            }
            break;

        case VERDE_PEDESTRE:
            if(evento == EVENTO_TIMEOUT) {
                estado_atual = VERMELHO_VEICULO;
            } else if(evento == EVENTO_EMERGENCIA) {
                estado_atual = EMERGENCIA;
            }
            break;

        case EMERGENCIA:
            if(evento == EVENTO_FIM_EMERGENCIA) {
                // Volta para estado seguro
                estado_atual = VERMELHO_VEICULO;
                pedestre_aguardando = false;
                contador_tempo = 0; // Reset timer
            }
            break;

        default:
            // Estado inválido - volta para estado seguro
            estado_atual = VERMELHO_VEICULO;
            pedestre_aguardando = false;
            break;
    }
}

// Função principal
int main(void) {
    setup_semaforo();

    // Estado inicial: vermelho para dar tempo de inicialização
    estado_atual = VERMELHO_VEICULO;
    atualizar_leds(estado_atual);

    while(1) {
        // Verifica eventos pendentes
        semaforo_event_t evento = evento_pendente;
        evento_pendente = EVENTO_NENHUM;

        // Verifica timeout se não há evento pendente
        if(evento == EVENTO_NENHUM) {
            evento = verificar_timeout();
        }

        // Processa evento se houver
        if(evento != EVENTO_NENHUM) {
            processar_evento(evento);
        }

        // Atualiza LEDs
        atualizar_leds(estado_atual);

        // Pequeno delay para não sobrecarregar CPU
        _delay_ms(10);
    }

    return 0;
}

/*
 * Diagrama de Estados:
 * 
 * VERDE_VEICULO ──timeout/pedestre──> AMARELO_VEICULO
 *      ↑                                     │
 *      │                                     ↓
 * VERMELHO_VEICULO <──timeout─── VERDE_PEDESTRE (se pedestre)
 *      ↑                              │
 *      │                              │
 *      └──────────timeout──────────────┘
 * 
 * EMERGENCIA: Qualquer estado pode ir para EMERGENCIA
 *             e retorna para VERMELHO_VEICULO
 * 
 * Características:
 * - Detecção de pedestres via botão
 * - Sensor de veículos
 * - Modo emergência
 * - Buzzer para deficientes visuais
 * - Tempos adaptativos
 * - Debounce para botões
 * - Estado seguro em caso de erro
 */
