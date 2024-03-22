
# Display LCD
DISPLAY DE CRISTAL LÍQUIDO 16 x 2 - CONTROLADOR HD44780+

## Pinagem

![image](https://github.com/mchavesferreira/smc/assets/63993080/d528e2c6-a5cd-41d6-8c04-32fcac226755)

Pinagem de um LCD 16 × 2.

Exemplos de utilização do LCD 16x2 disponiveis na bibliografia

<a href=https://github.com/mchavesferreira/smc/tree/main/Programas_livro/LCD_4bits> Programas exemplos com LCD 4 bits

Resumo dos códigos de instruções

![image](https://github.com/mchavesferreira/smc/assets/63993080/33f19801-4d3e-474a-8e92-b18778658e37)

Conjunto dos caracteres para um LCD 16 × 2.

![image](https://github.com/mchavesferreira/smc/assets/63993080/523c5da1-54fd-468f-9fa8-e323ef86c842)

Inclusão da biblioteca 
```java
#include "LCD.h"
```

Início da rotina
```java
inic_LCD_4bits();	
```

Posição do caractere através do endereço no display LCD 16x2

![image](https://github.com/mchavesferreira/smc/assets/63993080/9d009e2a-8271-42ba-b682-48f63bc23161)

```java
cmd_LCD(0x8D,0);	
```

Impressão de mensagens
```java
escreve_LCD("  INTERFACE DE");	//string armazenada na RAM
///
PROGMEM const char mensagem[] = " DADOS DE 4BITS!\0"; //mensagem armazenada na memória flash
escreve_LCD_Flash(mensagem);	//string armazenada na flash
```

Exemplo de impressão de números, primeiro é necessário separar as casas posicionais
```java
ident_num(cont,digitos);
			cmd_LCD(0x8D,0);			//desloca o cursor para que os 3 digitos fiquem a direita do LCD
			cmd_LCD(digitos[2],1);
			cmd_LCD(digitos[1],1);
			cmd_LCD(digitos[0],1);
```

## Criando caracteres especiais

Exemplo de criação de caracteres especiais para LCD 16x2 

![image](https://github.com/mchavesferreira/smc/assets/63993080/0bf58c8b-4126-4f6b-a3d7-40db9c972c1a)


## Big Number: 

Caracteres criados para se poder escrever números grandes num LCD 16 × 2

![image](https://github.com/mchavesferreira/smc/assets/63993080/3c963de3-dbdf-4141-a236-0c8caf4c24a8)

Organização de 4 caracteres para formar números grandes em um LCD 16 × 2.

![image](https://github.com/mchavesferreira/smc/assets/63993080/77b556f2-f0cb-4066-a86b-6979abfa988f)

Circuito de programação

![image](https://github.com/mchavesferreira/smc/assets/63993080/1da979b4-b02a-457e-ac1d-33fe1b420ae1)

https://wokwi.com/projects/358831286702363649[


- Fonte: AVR Técnicas de projetos
- 
