Introdução a linguagem C


Para começar com o aprendizado da linguagem C, especialmente com foco na aplicação em microcontroladores, é fundamental compreender como declarar variáveis, definir constantes e usar instruções de saída como printf(). Abaixo, estão alguns exemplos que cobrem esses conceitos básicos. Estes exemplos ajudarão a construir uma base sólida antes de avançar para conceitos mais complexos, como controle de fluxo, funções e manipulação de hardware específico de microcontroladores.
OBS: Ao trabalhar com microcontroladores, a função printf() pode não estar disponível ou ser prática, dependendo do ambiente de desenvolvimento e do hardware. Em muitos casos, você pode usar funções específicas do microcontrolador para enviar dados para um terminal ou display.

1. Exemplo de Declaração de Variáveis e Uso de printf()

#include <stdio.h>

int main() {
    // Declaração de variáveis
    int idade = 30;
    float altura = 1.75;
    char inicial = 'A';

    // Impressão das variáveis
    printf("Idade: %d anos\n", idade);
    printf("Altura: %.2f metros\n", altura);
    printf("Inicial do nome: %c\n", inicial);

    return 0;
}

2. Exemplo de Uso de Constantes
Este exemplo utiliza uma constante (PI) para calcular a área de um círculo dado um raio. A constante é definida usando #define.

#include <stdio.h>

#define PI 3.14159

int main() {
    float raio = 10.0;
    float area = PI * raio * raio;

    printf("A área de um círculo com raio %.2f é %.2f\n", raio, area);

    return 0;
}

3. Exemplo Combinando Variáveis e Constantes
Este exemplo combina o uso de variáveis e constantes para calcular os anos restantes até a aposentadoria, baseando-se em uma idade máxima definida.

#include <stdio.h>

#define MAX_IDADE 65

int main() {
    int idade = 30;
    int anosParaAposentadoria = MAX_IDADE - idade;

    printf("Idade atual: %d\n", idade);
    printf("Anos até a aposentadoria: %d\n", anosParaAposentadoria);

    return 0;
}

