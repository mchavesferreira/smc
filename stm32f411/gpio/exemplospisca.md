
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


## pisca sem delay

Objetivo é piscar um LED, conectado ao PC6, a cada 0,5s (500ms) utilizando a criação de atraso com o Timer 3.

    Clock do sistema: interno 48 MHz
	
    Prescaler escolhido para o exemplo: 48000 - 1
	
    contador: 500-1

Clock = 48 MHz

48.000.000 Hz
     ↓
Prescaler = 48000
     ↓
1000 Hz
     ↓
1 ms por contagem
     ↓
ARR = 500
     ↓
500 ms
     ↓
Evento Update
     ↓
Toggle LED

<img width="1026" height="776" alt="image" src="https://github.com/user-attachments/assets/f39b4cea-acda-4084-b942-58793ac3ebaa" />


```java
MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim3);
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
## Gerando uma interrupção com timer

Mantenhas as mesmas configurações de preescaler e o contador, habilitando a interrupção em NVIC.

Esta abordagem de interrução é útil para lidar com eventos assíncronos e em tempo real.

<img width="721" height="205" alt="image" src="https://github.com/user-attachments/assets/2372cb82-e4ff-45f3-83eb-b44b49481fb8" />

Retire o codigo de comparação em while(1){  } acrescente a seguinte função depois de main

```java
/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim3)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);	// Inverte saída do LED1 quando ocorre a interrupção (a cada 0,25s)
	}
}

/* USER CODE END 4 */

```
