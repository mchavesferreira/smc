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
´´´ java
	   HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);	// Inverte a saída do LED1
	   HAL_Delay(100);	
´´´
    /* USER CODE END WHILE */





