
Exemplo 1:

'''java

#include <avr/io.h>
#include <util/delay.h>

#define LED   PD2   // LED conectado ao PD2
#define BOTAO PD7   // Botão conectado ao PD7

// Variáveis para debounce
unsigned long tempoUltimoDebounce = 0;
const unsigned long tempoDebounce = 50;  // Tempo de debounce em milissegundos
int statusBotao = HIGH;                  // Estado atual do botão
int ultimoStatusBotao = HIGH;             // Último estado do botão

void configurarGPIO() {
    DDRD |= (1 << LED);    // Configura PD2 como saída
    PORTD |= (1 << BOTAO); // Habilita pull-up interno no PD7
}

// Função responsável por fazer o debounce
int debounceBotao() {
    int leitura = PIND & (1 << BOTAO) ? HIGH : LOW;  // Lê o estado do botão

    if (leitura != ultimoStatusBotao) {             // Se a leitura mudou
        tempoUltimoDebounce = millis();             // Reinicia o tempo de debounce
    }

    if ((millis() - tempoUltimoDebounce) > tempoDebounce) { // Se o tempo de debounce passou
        if (leitura != statusBotao) {             // Se o estado do botão mudou
            statusBotao = leitura;                // Atualiza o estado do botão
            if (statusBotao == LOW) {             // Botão pressionado (LOW devido ao pull-up)
                return 1;                         // Retorna 1 indicando que o botão foi pressionado
            }
        }
    }

    ultimoStatusBotao = leitura;  // Atualiza o último estado do botão
    return 0;                     // Retorna 0 se o botão não foi pressionado
}

int main() {
    configurarGPIO();

    while (1) {
        if (debounceBotao()) {  // Se o botão foi pressionado
            PORTD ^= (1 << LED); // Alterna o estado do LED
        }
    }
}


'''

# Exemplo 2:

'''java
#include <avr/io.h>
#include <util/delay.h>

#define LED   PD2   // LED conectado ao PD2
#define BOTAO PD7   // Botão conectado ao PD7

int contador = 0;         // Contador de iterações do botão pressionado
bool botaoConfirmado = false;  // Variável para indicar confirmação do botão pressionado

void configurarGPIO() {
    DDRD |= (1 << LED);    // Configura PD2 como saída
    PORTD |= (1 << BOTAO); // Habilita pull-up interno no PD7
}

// Função debounce que verifica o pressionamento contínuo do botão
void debounceBotao() {
    int leitura = PIND & (1 << BOTAO) ? HIGH : LOW;  // Lê o estado do botão (pull-up ativo)

    if (leitura == LOW) {  // Se o botão estiver pressionado
        contador++;  // Incrementa o contador
        _delay_ms(1); // Delay de 1 ms antes de retornar à função

        if (contador >= 50) {  // Se o botão foi pressionado por 50 iterações
            botaoConfirmado = true;  // Altera a variável de estado
        }
    } else { 
        contador = 0;  // Se o botão foi solto, reseta o contador
        botaoConfirmado = false;
    }
}

int main() {
    configurarGPIO();

    while (1) {
        debounceBotao(); // Chama a função de debounce continuamente

        if (botaoConfirmado) {  // Se o botão for pressionado por tempo suficiente
            PORTD ^= (1 << LED); // Alterna o estado do LED
            botaoConfirmado = false; // Reseta a variável para evitar reativação contínua
            _delay_ms(200); // Pequeno atraso para evitar múltiplos acionamentos rápidos
        }
    }
}
'''
