Introdução a linguagem C


Para começar com o aprendizado da linguagem C, especialmente com foco na aplicação em microcontroladores, é fundamental compreender como declarar variáveis, definir constantes e usar instruções de saída como printf(). Abaixo, estão alguns exemplos que cobrem esses conceitos básicos. Estes exemplos ajudarão a construir uma base sólida antes de avançar para conceitos mais complexos, como controle de fluxo, funções e manipulação de hardware específico de microcontroladores.
OBS: Ao trabalhar com microcontroladores, a função printf() pode não estar disponível ou ser prática, dependendo do ambiente de desenvolvimento e do hardware. Em muitos casos, você pode usar funções específicas do microcontrolador para enviar dados para um terminal ou display.

Exemplo de Variável do Tipo char


```java
#include <stdio.h>

int main() {
    char letra = 'A';
    printf("Caractere: %c\n", letra);
    return 0;
}
```

Exemplo de Variável do Tipo int

```java
#include <stdio.h>

int main() {
    int idade = 25;
    printf("Idade: %d anos\n", idade);
    return 0;
}
```


Exemplo de Variável do Tipo float

```java
#include <stdio.h>

int main() {
    float altura = 1.75;
    printf("Altura: %.2f metros\n", altura);
    return 0;
}
```

Exemplo de Variável do Tipo double

```java
#include <stdio.h>

int main() {
    double distancia = 12345.6789;
    printf("Distância: %.4f quilômetros\n", distancia);
    return 0;
}
```

Observações Importantes

-O tipo char é frequentemente utilizado para armazenar caracteres individuais, como letras ou símbolos.
-O tipo int é usado para números inteiros, ou seja, sem casas decimais.
-O tipo float e double são usados para números reais (com casas decimais). A diferença principal entre eles é a precisão e o alcance; double tem o dobro da precisão de um float, sendo preferível quando se necessita de uma maior precisão numérica.
Em microcontroladores e outras aplicações de sistemas embarcados, a escolha entre float e double pode ser influenciada pelo espaço de armazenamento disponível e pela capacidade de processamento do dispositivo, já que operações com double podem consumir mais recursos.

1. Combinação de Variáveis e Uso de printf()

```java
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
```

2. Exemplo de Uso de Constantes
Este exemplo utiliza uma constante (PI) para calcular a área de um círculo dado um raio. A constante é definida usando #define.

```java
#include <stdio.h>

#define PI 3.14159

int main() {
    float raio = 10.0;
    float area = PI * raio * raio;

    printf("A área de um círculo com raio %.2f é %.2f\n", raio, area);

    return 0;
}
```

3. Exemplo Combinando Variáveis e Constantes
Este exemplo combina o uso de variáveis e constantes para calcular os anos restantes até a aposentadoria, baseando-se em uma idade máxima definida.

```java
#include <stdio.h>

#define MAX_IDADE 65

int main() {
    int idade = 30;
    int anosParaAposentadoria = MAX_IDADE - idade;

    printf("Idade atual: %d\n", idade);
    printf("Anos até a aposentadoria: %d\n", anosParaAposentadoria);

    return 0;
}
```

Modificadores 

Modificadores em C são usados para alterar os limites de armazenamento ou a precisão dos tipos de dados. Eles incluem signed, unsigned, short, long, e long long. Esses modificadores ajudam a otimizar o uso de memória e a adequar o código às necessidades específicas da aplicação, especialmente em sistemas embarcados e microcontroladores, onde o espaço de memória é limitado.

Exemplo com signed e unsigned
```java
#include <stdio.h>

int main() {
    unsigned int positivo = 4294967295; // Máximo para um unsigned int de 32 bits
    signed int negativo = -2147483648; // Mínimo para um signed int de 32 bits

    printf("Valor máximo (unsigned int): %u\n", positivo);
    printf("Valor mínimo (signed int): %d\n", negativo);

    return 0;
}
```

Exemplo com short e long
```java
#include <stdio.h>

int main() {
    short int curto = 32767; // Máximo para um short int
    long int longo = 2147483647; // Máximo para um long int de 32 bits
    long long int muitoLongo = 9223372036854775807; // Máximo para um long long int de 64 bits

    printf("Valor máximo (short int): %d\n", curto);
    printf("Valor máximo (long int): %ld\n", longo);
    printf("Valor máximo (long long int): %lld\n", muitoLongo);

    return 0;
}
```

Exemplo com unsigned long long
```java
#include <stdio.h>

int main() {
    unsigned long long int extremamenteLongo = 18446744073709551615ULL; // Máximo para um unsigned long long int

    printf("Valor máximo (unsigned long long int): %llu\n", extremamenteLongo);

    return 0;
}
```

Dados Lógicos e Booleanos

Em C, os dados lógicos, ou valores booleanos, são representados usando o tipo int, onde 0 representa false (falso) e qualquer outro valor representa true (verdadeiro). A linguagem C, em sua forma padrão, não inclui um tipo específico para valores booleanos. No entanto, a partir do padrão C99, foi introduzido um tipo específico _Bool para representar valores booleanos. Além disso, a biblioteca padrão <stdbool.h> define bool como um alias para _Bool e define as constantes true e false.

```java
#include <stdio.h>
#include <stdbool.h> // Necessário para usar bool, true e false

int main() {
    // Declaração de variáveis booleanas
    bool estaChovendo = true;
    bool estaSol = false;

    // Verificação e impressão dos valores booleanos
    if (estaChovendo) {
        printf("Está chovendo.\n");
    } else {
        printf("Não está chovendo.\n");
    }

    if (estaSol) {
        printf("Está sol.\n");
    } else {
        printf("Não está sol.\n");
    }

    return 0;
}
```
Exercício: Modifique o exemplo anterior sem a biblioteca <stbool.h>, utilizando int para as variáveis.

Operadores
A linguagem C se destaca por sua ampla gama de operadores, simbolizados por um ou vários caracteres, empregados para interagir com dados, seja na forma de constantes ou variáveis. É possível que, dentre as linguagens de programação, C ofereça a maior diversidade de operadores. No entanto, ela pode ser considerada limitada no que tange à variedade de símbolos, visto que o mesmo símbolo pode ser utilizado para representar operadores distintos.

Operador	Significado
+	Soma
-	Subtração
*	Multiplicação
/	Divisão
%	Módulo ou resto da divisão
=	Atribuição
- (em uso como -variavel)	Menos unário – sinal negativo


Uso dos operadores aritméticos básicos: adição (+), subtração (-), multiplicação (*) e divisão (/). 

```java
#include <stdio.h>

int main() {
    int num1 = 10;
    int num2 = 5;

    // Adição
    int soma = num1 + num2;
    printf("%d + %d = %d\n", num1, num2, soma);

    // Subtração
    int diferenca = num1 - num2;
    printf("%d - %d = %d\n", num1, num2, diferenca);

    // Multiplicação
    int produto = num1 * num2;
    printf("%d * %d = %d\n", num1, num2, produto);

    // Divisão
    int quociente = num1 / num2;
    printf("%d / %d = %d\n", num1, num2, quociente);

    return 0;
}

```

