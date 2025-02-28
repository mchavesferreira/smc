#include <stdio.h>

int main(void)
{
    // Declaração da variável 'var1' e inicialização com 10
    char var1 = 10;
    printf("Passo 0: var1 foi declarado e recebeu o valor %d\n", var1);
    printf("Endereço de var1: %p\n\n", (void*)&var1);

    // Declaração do ponteiro 'p1'
    char *p1;

    // Antes da atribuição do ponteiro, imprimimos o valor de var1
    printf("Passo 1: Antes da atribuição do ponteiro\n");
    printf("Valor de var1: %d\n", var1);
    printf("Endereço de var1: %p\n\n", (void*)&var1);

    // p1 recebe o endereço de var1
    p1 = &var1;
    printf("Passo 2: Ponteiro 'p1' recebe o endereço de var1\n");
    printf("Valor armazenado em p1 (endereço de var1): %p\n", (void*)p1);
    printf("Valor apontado por p1 (*p1): %d\n\n", *p1);

    // Modificamos var1 usando o ponteiro
    *p1 = 30;
    printf("Passo 3: Modificamos o valor de var1 através do ponteiro\n");
    printf("Valor armazenado em var1 agora: %d\n", var1);
    printf("Valor apontado por p1 (*p1): %d\n", *p1);
    printf("Endereço de var1 (confirmando que não mudou): %p\n", (void*)&var1);

    return 0;
}
