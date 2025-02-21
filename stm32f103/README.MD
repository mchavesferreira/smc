

Curso STM32f103


STM32F103 - PDF Documentation

https://www.st.com/en/microcontrollers-microprocessors/stm32f103/documentation.html


#  Biblioteca HAL no STM32

A **HAL (Hardware Abstraction Layer)** é uma biblioteca desenvolvida pela **STMicroelectronics** para facilitar a programação de microcontroladores **STM32**. Ela oferece uma camada de abstração para os periféricos do microcontrolador, permitindo que o desenvolvedor interaja com o hardware sem precisar manipular diretamente os registradores de baixo nível.

---

##  Características Principais

✔ **Abstração de Hardware** → Código mais portável entre diferentes modelos da família STM32.  
✔ **Facilidade de Uso** → APIs de alto nível simplificam a configuração de periféricos.  
✔ **Compatibilidade com CMSIS** → A HAL funciona em conjunto com o **CMSIS** (Cortex Microcontroller Software Interface Standard).  
✔ **Geração Automática com STM32CubeMX** → O STM32CubeMX pode gerar código baseado na HAL.  

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

## 📌 Referências Oficiais

🔹 Documentação oficial da ST: [HAL and LL Drivers](https://www.st.com/content/st_com/en/products/embedded-software/mcu-middleware/stm32-hal-library.html)  
🔹 Repositório STM32Cube no GitHub: [STMicroelectronics/STM32Cube](https://github.com/STMicroelectronics)  
🔹 Documentação CMSIS (ARM): [CMSIS Overview](https://developer.arm.com/tools-and-software/embedded/cmsis)  

---
## 📌  Exemplo de Código: Alternando um GPIO

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
