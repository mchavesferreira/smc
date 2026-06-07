# utilizando oled no stm32

Baixar a biblioteca deste repositorio e criar um pasta lib no stm32IDE

https://github.com/afiskon/stm32-ssd1306

Copie estes arquivos para a pasta SRC de seu projeto

<img width="206" height="287" alt="image" src="https://github.com/user-attachments/assets/c8dc1510-0b66-41e4-b5e7-08ee51b2dad9" />

Altere o codigo para realizar os teste de recursos do display


´´´java
  MX_GPIO_Init();
  MX_I2C1_Init();
  ssd1306_Init();

  while (1)
  {
	 	    ssd1306_TestAll();
	        HAL_Delay(1000);    
  }

}
´´´
