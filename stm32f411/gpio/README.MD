# 1. Instrodução aos GPIO


## Registradores de controle do GPIO

rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics-1.pdf (cap. 8, p.146)

### Descrição funcional dos GPIOs

Sujeito às características específicas de hardware de cada porta de E/S listadas no datasheet, cada bit das portas de entrada/saída de propósito geral (**GPIO**) pode ser configurado individualmente por software em vários modos:

* Entrada flutuante
* Entrada com pull-up
* Entrada com pull-down
* Analógico
* Saída open-drain com capacidade de pull-up ou pull-down
* Saída push-pull com capacidade de pull-up ou pull-down
* Função alternativa push-pull com capacidade de pull-up ou pull-down
* Função alternativa open-drain com capacidade de pull-up ou pull-down

<img width="1135" height="644" alt="image" src="https://github.com/user-attachments/assets/58aa660a-fa2f-4068-bc52-89017be0c768" />


### MODER (Mode Register)

O registrador **MODER** define o modo de operação de cada pino da porta GPIO. Cada pino utiliza dois bits para determinar sua função, podendo ser configurado como **entrada digital (Input)**, **saída digital (Output)**, **função alternativa (Alternate Function)** ou **modo analógico (Analog)**. No STM32F411, esse registrador é normalmente o primeiro a ser configurado, pois determina como o hardware interno irá conectar o pino aos circuitos de entrada, saída, periféricos ou conversores analógicos.

### OTYPER (Output Type Register)

O registrador **OTYPER** define o tipo de saída utilizado quando o pino está configurado como saída digital ou função alternativa. Cada pino possui um bit que permite selecionar entre **Push-Pull** (empurra para nível alto e baixo através dos transistores internos) ou **Open-Drain** (apenas força nível baixo, exigindo um resistor pull-up externo ou interno para gerar nível alto). O modo Push-Pull é o mais comum para LEDs e acionamentos gerais, enquanto Open-Drain é amplamente utilizado em barramentos como o I²C.

### OSPEEDR (Output Speed Register)

O registrador **OSPEEDR** controla a velocidade de comutação dos transistores de saída do GPIO. Cada pino possui dois bits que permitem selecionar níveis de velocidade como **Low Speed**, **Medium Speed**, **High Speed** ou **Very High Speed**. Embora seja frequentemente interpretado como frequência, esse registrador controla principalmente a taxa de subida e descida dos sinais elétricos. Velocidades mais altas permitem sinais mais rápidos, porém aumentam consumo de energia, ruído eletromagnético (EMI) e possibilidade de interferências.

### PUPDR (Pull-Up/Pull-Down Register)

O registrador **PUPDR** habilita ou desabilita os resistores internos de polarização dos pinos GPIO. Cada pino pode ser configurado como **sem resistor (No Pull)**, **Pull-Up** (ligado internamente ao VDD) ou **Pull-Down** (ligado internamente ao GND). Esses resistores são importantes para evitar estados indefinidos ("flutuantes") em entradas digitais quando nenhum sinal externo está conectado. Por exemplo, um botão ligado ao GND normalmente utiliza Pull-Up interno, mantendo a entrada em nível lógico alto enquanto o botão não é pressionado.

### Resumo Prático

| Registrador | Função Principal                                                      |
| ----------- | --------------------------------------------------------------------- |
| **MODER**   | Define se o pino será Entrada, Saída, Função Alternativa ou Analógico |
| **OTYPER**  | Define o tipo de saída: Push-Pull ou Open-Drain                       |
| **OSPEEDR** | Ajusta a velocidade de comutação dos sinais de saída                  |
| **PUPDR**   | Configura resistores internos Pull-Up ou Pull-Down                    |

Uma forma simples de lembrar é:

**MODER → O que o pino faz**
**OTYPER → Como ele gera a saída**
**OSPEEDR → Quão rápido ele muda de estado**
**PUPDR → Como ele se comporta quando ninguém está acionando o pino**

Esses quatro registradores são os principais responsáveis pela configuração elétrica e funcional dos GPIOs do STM32F411.

# 2. Prática Códigos para uso com GPIO


# Exemplos de códigos

<img width="640" height="505" alt="image" src="https://github.com/user-attachments/assets/87d7d7ff-730e-44f1-b2d8-64887cd7cd5a" />

Configure os pinos:

LED1 > PC13  output

Button > PC14 input pull_up

## Alternando um pino de saída (LED)
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



## Imprimindo na UART1
main:
```java
	const uint8_t msg[] = "Hello Franzininho C0\r\n";
```
while:
```java
HAL_UART_Transmit(&huart1, msg, (sizeof(msg)-1), 1000);	// Transmite mensagem serial pela UART
```

## Lendo botão
acrescente o button  com pull-up

while:
```java
 if (!HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin))	// Se o botão estiver pressionado...
	  {
		  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);	// ...Acende o LED1
	  }
	  else
	  {
		  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);	// Senão, apaga o LED1
	  }
```


## Pisca com Timer

Objetivo é piscar um LED, conectado ao PC6, a cada 0,5s (500ms) utilizando a criação de atraso com o Timer 3.

    Clock do sistema: interno 48 MHz
	
    Prescaler escolhido para o exemplo: 48000 - 1
	
    contador: 500-1



<img width="1026" height="776" alt="image" src="https://github.com/user-attachments/assets/f39b4cea-acda-4084-b942-58793ac3ebaa" />


```java
MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  if(__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE)){
	  	    __HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);
	  	    HAL_GPIO_TogglePin(GPIOC, LED1_Pin);
	  	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

```
  HAL_TIM_Base_Start_IT(&htim3) é usada para iniciar a contagem do timer, e dentro do loop principal, o código verifica se a flag de atualização do timer foi acionada, indicando que timer atingiu o período deseado, então o código limpa a flag e alterna o estado do led.
  

## Gerando uma interrupção com timer

Mantenhas as mesmas configurações de preescaler e o contador, habilitando a interrupção em NVIC.

Esta abordagem de interrução é útil para lidar com eventos assíncronos e em tempo real.

<img width="721" height="205" alt="image" src="https://github.com/user-attachments/assets/2372cb82-e4ff-45f3-83eb-b44b49481fb8" />

Altere o codigo e acrescente a função callback seguinte depois de main
```java
/* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  }

}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim3)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);	// Inverte saída do LED1 quando ocorre a interrupção (a cada 0,25s)
	}
}


```

Nesta configuração

HAL_TIM_Base_Start_IT(&htim3); é usada para iniciar o timer com interrupção e é adicionada uma função de callback void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)


## Interrupção externa

Adaptado de: https://github.com/Franzininho/Franzininho-C0-Com-STM32CubeIDE-Artigos/tree/master/InterrupcaoExterna

```java
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t msg_subida[] = "Borda subida identificada. \r\n";
uint8_t msg_descida[] = "Borda descida identificada.\r\n";
/* USER CODE END PV */
```

Fora do main()
```java
/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)	// Função de callback para tratamento da interrupção externa (descida)
{
	if(GPIO_Pin == GPIO_PIN_8)
	{
		HAL_UART_Transmit(&huart1, msg_descida, (sizeof(msg_descida)-1), 1000);	// Transmite mensagem serial pela UART
	}
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)	// Função de callback para tratamento da interrupção externa (subida)
{
	if(GPIO_Pin == GPIO_PIN_8)
	{
		HAL_UART_Transmit(&huart1, msg_subida, (sizeof(msg_subida)-1), 1000);	// Transmite mensagem serial pela UART
	}
}
```

