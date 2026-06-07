# utilizando oled no stm32

### Baixar a biblioteca deste repositorio

https://github.com/afiskon/stm32-ssd1306

Descompacte, e copie  arquivos da pasta SSD1306 para a pasta SRC de seu projeto. 

<img width="206" height="287" alt="image" src="https://github.com/user-attachments/assets/c8dc1510-0b66-41e4-b5e7-08ee51b2dad9" />

Renomei o arquivo ssd1306_conf_template.h para ssd1306_conf.h e altere o script
```java
// Choose a microcontroller family
//#define STM32F0
//#define STM32F1
#define STM32F4
```

Altere o codigo para realizar os teste de recursos do display


```java
  MX_GPIO_Init();
  MX_I2C1_Init();
  ssd1306_Init();

  while (1)
  {
	 	    ssd1306_TestAll();
	        HAL_Delay(1000);    
  }

}
```
## Monte o circuito

Monte e grave o arquivo compilado em seu STM32f411
```java
PB7<>SDA
PB6<>SCL
```

<img width="756" height="398" alt="image" src="https://github.com/user-attachments/assets/50c20462-6862-4481-b244-c8f4280930b7" />


### Display com numeros e letras

```java

  ssd1306_Init();
  char buff[64];
  volatile uint32_t time=0;

  while (1)
  {
	    ssd1306_Fill(Black);
	    ssd1306_SetCursor(4, 4);
	    ssd1306_WriteString("IFSP Catanduva", Font_6x8, White);
	    ssd1306_SetCursor(4, 24);
	    ssd1306_WriteString("Temperatura", Font_16x15, White);
	    ssd1306_SetCursor(4, 44);
	    //snprintf(buff, sizeof(buff), "%lu seg", (unsigned long)time);
	    sprintf(buff, "%lu s", (unsigned long)time);
	    ssd1306_WriteString(buff, Font_11x18, White);
	    ssd1306_UpdateScreen();
	    HAL_Delay(1000);
	    time++;
  }
```

