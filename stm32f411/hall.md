
#  Biblioteca HAL no STM32

A **HAL (Hardware Abstraction Layer)** é uma biblioteca desenvolvida pela **STMicroelectronics** para facilitar a programação de microcontroladores **STM32**. Ela oferece uma camada de abstração para os periféricos do microcontrolador, permitindo que o desenvolvedor interaja com o hardware sem precisar manipular diretamente os registradores de baixo nível.

---

##  Características Principais

✔ **Abstração de Hardware** → Código mais portável entre diferentes modelos da família STM32.  
✔ **Facilidade de Uso** → APIs de alto nível simplificam a configuração de periféricos.  
✔ **Compatibilidade com CMSIS** → A HAL funciona em conjunto com o **CMSIS** (Cortex Microcontroller Software Interface Standard).  
✔ **Geração Automática com STM32CubeMX** → O STM32CubeMX pode gerar código baseado na HAL.  


-- 
## Instalação 
STM32CubeMX
https://www.st.com/content/st_com/en/stm32cubemx.html


## Gravando com UART

Configurando o modo boot:

O Blue Pill tem dois jumpers chamados BOOT0 e BOOT1 (às vezes escrito como BOOT0 e BOOT1 no PCB).

Para programar via serial:

    BOOT0 → 1 (High) (lado mais próximo da borda).

    BOOT1 → 0 (Low) (lado mais próximo dos pinos).

Depois de gravar, para rodar o programa, volte para:

    BOOT0 → 0

    BOOT1 → 0

---

##  Estrutura da Biblioteca HAL

A HAL está dividida em diferentes camadas e módulos:

- **Camada de Driver**  
  - APIs para controle de periféricos (exemplo: `HAL_GPIO_WritePin()` para configurar um GPIO).  
- **Camada de Middleware**  
  - Implementação de protocolos como **USB, TCP/IP, RTOS** e outros.  
- **Camada de Aplicação**  
  - Código final da aplicação que utiliza os drivers HAL.

---

##  Vantagens da HAL

✅ **Código mais portável** entre diferentes modelos STM32.  
✅ **Facilidade na configuração** dos periféricos sem manipular registradores diretamente.  
✅ **Compatível com middlewares** como FreeRTOS, USB e TCP/IP.  

---

## Desvantagens da HAL

❌ Pode ser **mais lenta** do que código diretamente baseado em registradores.  
❌ Ocupa **mais espaço na memória** comparado à biblioteca **LL (Low-Level)**.  

---



---
##  Exemplo de Código: Alternando um GPIO

O código abaixo configura um pino GPIO como saída e faz seu estado alternar a cada 500ms.

```java

#include "stm32f1xx_hal.h" // Biblioteca HAL para STM32F1 (exemplo)

// Função para inicializar o GPIO
void GPIO_Init(void) {
    __HAL_RCC_GPIOC_CLK_ENABLE();  // Habilita o clock do GPIOC

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_13;  // Define o pino PC13
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Modo saída push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;  // Sem resistores internos
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // Velocidade baixa
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);  // Inicializa o GPIO
}

// Função principal
int main(void) {
    HAL_Init();  // Inicializa a HAL
    GPIO_Init(); // Inicializa o GPIO

    while (1) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);  // Alterna o pino PC13
        HAL_Delay(500);  // Aguarda 500ms
    }
}

```


##  Exemplo: Alternar um GPIO sem a HAL

Este código alterna o pino PC13 (comum em placas como o STM32F103C8T6 "Blue Pill") sem usar a HAL, utilizando apenas manipulação direta dos registradores.

```java

#include "stm32f10x.h"  // Definições específicas do STM32F1 (ajuste conforme a família do STM32)

// Inicializa o GPIO manualmente
void GPIO_Init(void) {
    // Habilita o clock do GPIOC
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // Configura o PC13 como saída push-pull, velocidade de 2MHz
    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);  // Limpa os bits de configuração
    GPIOC->CRH |= (GPIO_CRH_MODE13_1); // Define como saída de 2MHz (10)
}

// Função de atraso simples (não precisa da HAL)
void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 4000; i++) {
        __NOP(); // No Operation, apenas para gastar tempo
    }
}

// Função principal
int main(void) {
    GPIO_Init(); // Inicializa o GPIO

    while (1) {
        GPIOC->ODR ^= (1 << 13);  // Alterna o estado do pino PC13
        delay_ms(500);  // Aguarda 500ms
    }
}

```



# 🚀 Aula: GPIO com STM32 HAL

## 📚 Introdução

GPIO (General Purpose Input/Output) são os pinos de propósito geral dos microcontroladores STM32, que podem ser configurados como **entrada**, **saída**, **entrada com pull-up/pull-down**, ou até para funções especiais como **interrupções externas**.

A biblioteca **HAL** oferece uma camada de abstração para manipular esses pinos de forma simples e portável.

---

## 🔧 Funções GPIO na Biblioteca HAL

### 1️⃣ **Configuração dos GPIOs**

A configuração dos pinos é feita usando a função:

```c
HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);
```

* **Parâmetros:**

  * `GPIOx`: Porta desejada (`GPIOA`, `GPIOB`, `GPIOC`, etc.).
  * `GPIO_Init`: Ponteiro para a estrutura que define os parâmetros da configuração.

* **Exemplo de estrutura de configuração:**

```c
GPIO_InitTypeDef GPIO_InitStruct = {0};

GPIO_InitStruct.Pin = GPIO_PIN_13;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
```

---

### 2️⃣ **Escrever no GPIO (Saída)**

```c
HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
```

* **Parâmetros:**

  * `GPIOx`: Porta (`GPIOA`, `GPIOB`...).
  * `GPIO_Pin`: Pino (`GPIO_PIN_13`...).
  * `PinState`: `GPIO_PIN_SET` (nível alto) ou `GPIO_PIN_RESET` (nível baixo).

* **Exemplo:**

```c
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
```

---

### 3️⃣ **Ler do GPIO (Entrada)**

```c
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
```

* **Retorna:** `GPIO_PIN_SET` ou `GPIO_PIN_RESET`.

* **Exemplo:**

```c
if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
    // Botão pressionado
}
```

---

### 4️⃣ **Alternar o estado do pino (Toggle)**

```c
HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
```

* **Exemplo:**

```c
HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
```

> 📝 *Muito útil para piscar LEDs sem precisar saber se estava ligado ou desligado antes.*

---

### 5️⃣ **Desinicializar um GPIO (Liberar recursos)**

```c
HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin);
```

* **Exemplo:**

```c
HAL_GPIO_DeInit(GPIOC, GPIO_PIN_13);
```

---

## 🏗️ Estrutura da configuração (`GPIO_InitTypeDef`)

| Campo   | Descrição                                             |
| ------- | ----------------------------------------------------- |
| `Pin`   | Qual pino será usado (`GPIO_PIN_0` até `GPIO_PIN_15`) |
| `Mode`  | Modo do pino: saída, entrada, interrupção, etc.       |
| `Pull`  | Pull-up, Pull-down, ou sem pull                       |
| `Speed` | Velocidade de operação (para saída)                   |

---

## 🔥 Modos possíveis (`Mode`)

* `GPIO_MODE_INPUT` — Entrada digital
* `GPIO_MODE_OUTPUT_PP` — Saída push-pull
* `GPIO_MODE_OUTPUT_OD` — Saída open-drain
* `GPIO_MODE_AF_PP` — Função alternativa push-pull
* `GPIO_MODE_AF_OD` — Função alternativa open-drain
* `GPIO_MODE_ANALOG` — Modo analógico
* `GPIO_MODE_IT_RISING` — Interrupção borda de subida
* `GPIO_MODE_IT_FALLING` — Interrupção borda de descida
* `GPIO_MODE_IT_RISING_FALLING` — Interrupção em ambas bordas

---

## 🎛️ Pull-up / Pull-down (`Pull`)

* `GPIO_NOPULL`
* `GPIO_PULLUP`
* `GPIO_PULLDOWN`

---

## ⚡ Velocidade (`Speed`)

* `GPIO_SPEED_FREQ_LOW`
* `GPIO_SPEED_FREQ_MEDIUM`
* `GPIO_SPEED_FREQ_HIGH`
* `GPIO_SPEED_FREQ_VERY_HIGH`

---

## 💡 Exemplo completo: Piscar LED

```c
GPIO_InitTypeDef GPIO_InitStruct = {0};

// 1. Habilita clock da porta GPIOC
__HAL_RCC_GPIOC_CLK_ENABLE();

// 2. Configura pino PC13 como saída
GPIO_InitStruct.Pin = GPIO_PIN_13;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

// 3. Loop infinito piscando LED
while (1) {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    HAL_Delay(500); // atraso de 500ms
}
```

---
