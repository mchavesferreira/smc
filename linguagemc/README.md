Introdução a linguagem C


Para começar com o aprendizado da linguagem C, especialmente com foco na aplicação em microcontroladores, é fundamental compreender como declarar variáveis, definir constantes e usar instruções de saída como printf(). Abaixo, estão alguns exemplos que cobrem esses conceitos básicos. Estes exemplos ajudarão a construir uma base sólida antes de avançar para conceitos mais complexos, como controle de fluxo, funções e manipulação de hardware específico de microcontroladores.
OBS: Ao trabalhar com microcontroladores, a função printf() pode não estar disponível ou ser prática, dependendo do ambiente de desenvolvimento e do hardware. Em muitos casos, você pode usar funções específicas do microcontrolador para enviar dados para um terminal ou display.

Exemplo de Variável do Tipo char

#include <stdio.h>

int main() {
    char letra = 'A';
    printf("Caractere: %c\n", letra);
    return 0;
}

Exemplo de Variável do Tipo int

#include <stdio.h>

int main() {
    int idade = 25;
    printf("Idade: %d anos\n", idade);
    return 0;
}


Exemplo de Variável do Tipo float

#include <stdio.h>

int main() {
    float altura = 1.75;
    printf("Altura: %.2f metros\n", altura);
    return 0;
}

Exemplo de Variável do Tipo double

#include <stdio.h>

int main() {
    double distancia = 12345.6789;
    printf("Distância: %.4f quilômetros\n", distancia);
    return 0;
}

Observações Importantes

-O tipo char é frequentemente utilizado para armazenar caracteres individuais, como letras ou símbolos.
-O tipo int é usado para números inteiros, ou seja, sem casas decimais.
-O tipo float e double são usados para números reais (com casas decimais). A diferença principal entre eles é a precisão e o alcance; double tem o dobro da precisão de um float, sendo preferível quando se necessita de uma maior precisão numérica.
Em microcontroladores e outras aplicações de sistemas embarcados, a escolha entre float e double pode ser influenciada pelo espaço de armazenamento disponível e pela capacidade de processamento do dispositivo, já que operações com double podem consumir mais recursos.

1. Combinação de Variáveis e Uso de printf()

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

