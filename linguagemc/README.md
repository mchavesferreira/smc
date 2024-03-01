# Introdução a linguagem C

O procedimento de compilação se desdobra em quatro fases principais que normalmente ocorrem de maneira sequencial: pré-processamento, compilação propriamente dita, montagem e ligação, como ilustrado na figura: 
![image](https://github.com/mchavesferreira/smc/assets/63993080/c53ea8f9-4223-4a0b-9a33-9b591eb832c8) Fonte: [Almeida, Maximiano, 2016]

A fase de <B>pré-compilação</b> trata da leitura do código fonte, executando substituições e configurações através de comandos específicos, como #define e #include, e remoção de comentários, gerando arquivos temporários com as modificações. A <B>compilação converte</b> o código C em assembly, uma linguagem de baixo nível mais próxima da máquina, mas ainda não em binário ou alocada na memória. Esta fase inclui a otimização do código, visando equilibrar a redução do tamanho do arquivo com a eficiência de execução, o que pode ser desafiador em ambientes embarcados devido a suposições do compilador que podem não se aplicar. Cada arquivo .C resulta em um arquivo intermediário em assembly após essa etapa.


A etapa de <B>linkagem</b> consiste em combinar todos os arquivos intermediários criados durante a compilação em um único arquivo, assegurando que todas as referências sejam resolvidas e integrando bibliotecas pré-compiladas, como as da linguagem C, diretamente no programa. A linkagem dinâmica é raramente empregada em sistemas embarcados devido à natureza singular dos programas e à inexistência de necessidade de compartilhamento dinâmico de bibliotecas.

A <B>assemblagem</b>, por sua vez, é o processo final que converte o código de assembly intermediário para linguagem de máquina, ajustando referências relativas para posições fixas na memória, culminando na produção do arquivo binário. Dependendo do compilador, pode ser gerado um arquivo com extensão .s19, que, apesar de conter o código de máquina, está em formato de texto para facilitar a transmissão para dispositivos de gravação, incluindo verificações para assegurar a integridade dos dados.
[Almeida, Maximiano, 2016]. 

## Organização dos programas em C
 - Comentários
 - Diretivas de compilação
 - Definições globais
 - Protótipos de funções
 - Definições de funções

 Para o aprendizado da linguagem C utilizaremos alguns destes simuladores online:
 
- Simuladores online para aprendizado:

https://www.tutorialspoint.com/compile_c_online.php

https://www.mycompiler.io/pt/new/cpp

https://www.online-cpp.com/online_c_compiler

- Comentários, edentação
- Variáveis
- Operadores
- Diretivas


## Comentários, edentação

Para começar com o aprendizado da linguagem C, especialmente com foco na aplicação em microcontroladores, é fundamental compreender como declarar variáveis, definir constantes e usar instruções de saída como printf(). Abaixo, estão alguns exemplos que cobrem esses conceitos básicos. Estes exemplos ajudarão a construir uma base sólida antes de avançar para conceitos mais complexos, como controle de fluxo, funções e manipulação de hardware específico de microcontroladores.
OBS: Ao trabalhar com microcontroladores, a função printf() pode não estar disponível ou ser prática, dependendo do ambiente de desenvolvimento e do hardware. Em muitos casos, você pode usar funções específicas do microcontrolador para enviar dados para um terminal ou display.
- Comentários
- Edentação
- caixa Alta

___
## Variáveis

### Exemplo de Variável do Tipo char


```java
#include <stdio.h>

int main() {
    char letra = 'A';
    printf("Caractere: %c\n", letra);
    return 0;
}
```

### Exemplo de Variável do Tipo int

```java
#include <stdio.h>

int main() {
    int idade = 25;
    printf("Idade: %d anos\n", idade);
    return 0;
}
```


### Exemplo de Variável do Tipo float

```java
#include <stdio.h>

int main() {
    float altura = 1.75;
    printf("Altura: %.2f metros\n", altura);
    return 0;
}
```

### Exemplo de Variável do Tipo double

```java
#include <stdio.h>

int main() {
    double distancia = 12345.6789;
    printf("Distância: %.4f quilômetros\n", distancia);
    return 0;
}
```


! Observações Importantes 

-O tipo char é frequentemente utilizado para armazenar caracteres individuais, como letras ou símbolos.
-O tipo int é usado para números inteiros, ou seja, sem casas decimais.
-O tipo float e double são usados para números reais (com casas decimais). A diferença principal entre eles é a precisão e o alcance; double tem o dobro da precisão de um float, sendo preferível quando se necessita de uma maior precisão numérica.
Em microcontroladores e outras aplicações de sistemas embarcados, a escolha entre float e double pode ser influenciada pelo espaço de armazenamento disponível e pela capacidade de processamento do dispositivo, já que operações com double podem consumir mais recursos.

### 1. Combinação de Variáveis e Uso de printf()

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

### 2. Exemplo de Uso de Constantes
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

## Modificadores 

Modificadores em C são usados para alterar os limites de armazenamento ou a precisão dos tipos de dados. Eles incluem signed, unsigned, short, long, e long long. Esses modificadores ajudam a otimizar o uso de memória e a adequar o código às necessidades específicas da aplicação, especialmente em sistemas embarcados e microcontroladores, onde o espaço de memória é limitado.

### Exemplo com signed e unsigned
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

### Exemplo com short e long
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

### Exemplo com unsigned long long
```java
#include <stdio.h>

int main() {
    unsigned long long int extremamenteLongo = 18446744073709551615ULL; // Máximo para um unsigned long long int

    printf("Valor máximo (unsigned long long int): %llu\n", extremamenteLongo);

    return 0;
}
```

## Dados Lógicos e Booleanos

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
Exercício: Modifique o exemplo anterior porém sem ultilizar a biblioteca <stbool.h>. Utilize variaveis declaradas como char.

___

## Operadores

A linguagem C se destaca por sua ampla gama de operadores, simbolizados por um ou vários caracteres, empregados para interagir com dados, seja na forma de constantes ou variáveis. É possível que, dentre as linguagens de programação, C ofereça a maior diversidade de operadores. No entanto, ela pode ser considerada limitada no que tange à variedade de símbolos, visto que o mesmo símbolo pode ser utilizado para representar operadores distintos.

| Operador                  | Significado                      |
|---------------------------|----------------------------------|
| `+`                       | Soma                             |
| `-`                       | Subtração                        |
| `*`                       | Multiplicação                    |
| `/`                       | Divisão                          |
| `%`                       | Módulo ou resto da divisão       |
| `=`                       | Atribuição                       |
| `-` (em uso como `-variavel`) | Menos unário – sinal negativo  |
| `!` | negação lógica |
| `==` | igualdade |
| `!=` | desigualdade |
| `?` |  |
| `||` | or lógico |
| `&&` | and lógico |

### Uso dos operadores aritméticos básicos: adição (+), subtração (-), multiplicação (*) e divisão (/). 

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

### Operadores % =  e - (sinal negativo) 

```java
#include <stdio.h>

int main() {
    int numero = 10;
    int divisor = 3;
    int resultadoModulo;
    int numeroNegativo;

    // Atribuição do resultado do módulo
    resultadoModulo = numero % divisor;
    printf("O resto da divisão de %d por %d é %d\n", numero, divisor, resultadoModulo);

    // Atribuição de um valor negativo usando o sinal negativo
    numeroNegativo = -numero;
    printf("O valor negativo de %d é %d\n", numero, numeroNegativo);

    return 0;
}

```

### Operadores aritméticos forma compacta

| operador | forma compacta | Significado                                   |
|----------|---------|-----------------------------------------------|
| `+=`     | `a += b` |  `a = a + b` |
| `-=`     | `a -= b` |  `a = a - b` |
| `*=`     | `a *= b` |  `a = a * b` |
| `/=`     | `a /= b` |  `a = a / b` |
| `%=`     | `a %= b` |  `a = a %/ b` |



### Operadores de incremento e decremento

| Operador | Significado         |
|----------|---------------------|
| `++`     | Incremento de um    |
| `--`     | Decremento de um    |


### Operadores binários (Bit a bit)
o uso dos operadores de bit: & (e binário), | (ou binário), ~ (não binário), >> (deslocamento para a direita) e << (deslocamento para a esquerda). 

| Operador | Significado                |
|----------|----------------------------|
| `&`      | "e" binário                |
| `|`      | "ou" binário               |
| `~`      | "não" binário              |
| `>>`     | Deslocamento para direita  |
| `<<`     | Deslocamento para esquerda |

```java
#include <stdio.h>

int main() {
    unsigned int a = 60; // 0011 1100 em binário
    unsigned int b = 13; // 0000 1101 em binário
    int resultado;

    // E binário
    resultado = a & b; // 0000 1100
    printf("Resultado de a & b: %d\n", resultado);

    // OU binário
    resultado = a | b; // 0011 1101
    printf("Resultado de a | b: %d\n", resultado);

    // NÃO binário
    resultado = ~a; // 1100 0011 (em uma arquitetura de 32 bits, isto se torna 1111 1111 1111 1111 1111 1111 1100 0011)
    printf("Resultado de ~a: %u\n", resultado);

    // Deslocamento para a direita
    resultado = a >> 2; // 0000 1111
    printf("a deslocado 2 bits para a direita: %d\n", resultado);

    // Deslocamento para a esquerda
    resultado = a << 2; // 1111 0000
    printf("a deslocado 2 bits para a esquerda: %d\n", resultado);

    return 0;
}
```
![image](https://github.com/mchavesferreira/smc/assets/63993080/50a1bd87-b20e-4ac2-b230-0bbd4b74edd8)



### Operadores binários (Bit a bit)
o uso dos operadores de bit: & (e binário), | (ou binário), ~ (não binário), >> (deslocamento para a direita) e << (deslocamento para a esquerda). 

| Operador | Significado                |
|----------|----------------------------|
| `&`      | "e" binário                |
| `|`      | "ou" binário               |
| `~`      | "não" binário              |
| `>>`     | Deslocamento para direita  |
| `<<`     | Deslocamento para esquerda |


___
## Diretivas

As diretivas de pré-processamento #if, #else, #elif, e #endif em C são utilizadas para incluir ou excluir partes do código antes da compilação, baseando-se em condições definidas. Essas diretivas são muito úteis para lidar com diferentes ambientes de compilação, plataformas de hardware, ou para incluir código de debug.

```java
#include <stdio.h>

// Definição de uma macro para controle da compilação
#define DEBUG_MODE

int main() {
    printf("Iniciando o programa.\n");

    #if defined(DEBUG_MODE)
    printf("Modo DEBUG ativado: Executando tarefas de debug.\n");
    // Código específico de debug pode ser colocado aqui
    #else
    printf("Modo DEBUG desativado: Executando tarefas normais.\n");
    // Código para execução normal
    #endif

    printf("Finalizando o programa.\n");

    return 0;
}

```
### Exemplo para compilar  diferentes partes do código com base no modelo de um processador. 
```java
#include <stdio.h>

// Defina o modelo do processador antes da função main
#define PROCESSADOR_A

 #if defined(PROCESSADOR_A)
   #define GANHO 2
#elif defined(PROCESSADOR_B)
   #define GANHO 5
#else
    #define GANHO 7
#endif
int main() {
    float entrada = 10.0;
    float saida = GANHO * entrada;
    printf("saida= %.2f \n", saida);
    return 0;
}
```

### Inclusão de arquivos
A diretiva de inclusão **** #include *** , possibilita ao desenvolvedor incorporar em seu código funções previamente desenvolvidas, armazenadas em diferentes arquivos, seja por ele ou por terceiros. A compilação dessas funções em um único arquivo, visando sua utilização posterior, é conhecida como criação de uma biblioteca.

Os arquivos com a extensão .H são conhecidos como arquivos de cabeçalho ("Header files") e tipicamente contêm apenas os protótipos das funções ou definições de tipos de variáveis que a biblioteca oferece.
```java
#include <nome_arquivo.h> / arquivo do path do compilador 
#include "nome_arquivo.h" // arquivo no mesmo diretório
```
### Definição e exanssão de macros

Uma tarefa no processo de pré-compilação é realizar substituições de símbolos, valores ou textos antes da compilação do arquivo. Essas alterações são possíveis por meio da criação de macros, utilizando a diretiva #define.

```java
#define SEGUNDOS  60
```
### macros
Cria uma estrutura similar a função com algumas limitações, como não criar variáveis locais e não realizar recursão.


```java
#define Media(a, b, c) ((a+c+b)/3)
```
### #pragma

A diretiva #pragma se distingue significativamente das demais diretivas de pré-compilação. Ao invés de modificar o código-fonte, ela emite comandos especiais ao compilador que influenciam o procedimento de compilação ou definem especificações que vão além do código.

```java
#pragma CODE_SEG _NEAR_SEG NON_BANKED 
//a variável abaixo será armazenada em memória não paginável
int variável_nao_paginável; 
#pragma CODE_SEG DEFAULT 
//a variável abaixo está armazenada na região padrão 
//da memória, podendo não estar mapeada caso haja uma 
//troca de banco de memória 
int variável_paginável;
```
Essa diretiva também pode ser utilizada para ajustar registros específicos do microcontrolador. Normalmente, esses registros gerenciam as configurações fundamentais do processador, como a frequência de operação, capacidades de depuração e outras opções relevantes.


# Vetores e matrizes


![image](https://github.com/mchavesferreira/smc/assets/63993080/aa3801cc-0e56-444e-becb-2d30bd5b907e)
Essa	declaração	indica	ao	compilador	que	ele	deve	reservar	espaço suficiente	na	memória	para	armazenar	10	elementos	do	tipo	inteiro. Além	do	espaço	de	cada	um	dos	elementos,	o	compilador	também reserva	espaço	para	um	ponteiro	que	apontará	para	o	primeiro	elemento do	vetor.


![image](https://github.com/mchavesferreira/smc/assets/63993080/cf7b3fb1-6dc1-4cd1-8944-bdba437b9f50)


```java
 int num[S]; 
 char codigo[S];
```

Posicionamento destes vetores


![image](https://github.com/mchavesferreira/smc/assets/63993080/e34a9799-e6e8-410d-96b6-b3bd20abd932)

nomeVetor[posicao] - novoValor;

```java
num[8] = 10; 
num[l] = 20; 
num[2] = 30;
// 
int num[5] = {10, 20, 30, 40, 50};

// Vetor String
char msg [] - "Bom dia"; //msg possui tamanho 8

```

#### Matrizes

```java
int a[2] [6];
```

![image](https://github.com/mchavesferreira/smc/assets/63993080/36ded4f7-cbb5-475e-8337-7f4f5615ec7c)

```java
//inicialização por lista contínua 
int mat[2] [3] = {51, 52, 53, 54, 55, 56}; 
//inicialização por linhas 
int mat[2] [3] = {{51, 52, 53}, {54, 55, 56}}; 
//inicialização por linhas e com quebra de linha 
int mat[2] [3] - {{51, 52, 53}, 
{54, 55, 56}};
```

![image](https://github.com/mchavesferreira/smc/assets/63993080/310bf071-61c4-4181-afbc-aab09a1f64ba)

