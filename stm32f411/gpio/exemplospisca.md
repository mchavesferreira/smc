
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

