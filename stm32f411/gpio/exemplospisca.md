
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




