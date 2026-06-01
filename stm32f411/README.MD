TM32F411CE


High-performance access line, Arm Cortex-M4 core with DSP and FPU, 512 Kbytes of Flash memory, 100 MHz CPU, ART Accelerator 


https://www.st.com/en/microcontrollers-microprocessors/stm32f411ce.html


https://github.com/embeddedalpha/STM32F411CEU6


Exemplos projeto Franzininho cortex M0+: https://github.com/Franzininho/franzininho-c0-exemplos-stm32cubeide


Informações sobre a blackpill:

https://github.com/trebisky/stm32f411

esquema blackpill:  http://cholla.mmto.org/stm32all/black_pill/WeAct_Black_Pill_V2.0_schematic.pdf


pisca led

  /* USER CODE BEGIN WHILE */

  while (1)
  {
```java

	   HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);	// Inverte a saída do LED1
	   HAL_Delay(100);	
```
    /* USER CODE END WHILE */


OU

```java
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);

	   HAL_Delay(200);
	   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
	   HAL_Delay(200);
```



Na pasta **Src** gerada pelo STM32CubeMX/CubeIDE, esses arquivos possuem funções bem definidas dentro do projeto:

| Arquivo                 | Função                                                                                                                                                                                                                          |
| ----------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **main.c**              | Arquivo principal da aplicação. Contém a função `main()`, inicialização do HAL, configuração dos periféricos gerados pelo CubeMX e o laço principal `while(1)` onde normalmente o usuário desenvolve sua aplicação.             |
| **stm32c0xx_hal_msp.c** | Contém as funções **MSP (MCU Support Package)**. Aqui são configurados recursos de baixo nível dos periféricos, como habilitação de clocks, configuração de GPIOs, DMA, interrupções NVIC e pinos utilizados pelos periféricos. |
| **stm32c0xx_it.c**      | Arquivo das **rotinas de interrupção (Interrupt Handlers)**. Contém funções como `SysTick_Handler()`, `USART_IRQHandler()`, `TIM_IRQHandler()`, entre outras, executadas automaticamente quando ocorre uma interrupção.         |
| **syscalls.c**          | Implementa chamadas de sistema utilizadas pela biblioteca padrão C. Permite funções como `printf()`, `malloc()`, acesso a UART para saída padrão, entre outras. Faz a ponte entre a biblioteca C e o hardware embarcado.        |
| **sysmem.c**            | Gerencia a memória dinâmica do sistema. Implementa funções relacionadas à alocação de memória (`malloc`, `free`) e controle do heap utilizado pela biblioteca C.                                                                |
| **system_stm32c0xx.c**  | Arquivo de inicialização do microcontrolador. Configura o clock do sistema, variáveis globais do CMSIS e contém a função `SystemInit()`, executada logo após o reset, antes da função `main()`.                                 |


