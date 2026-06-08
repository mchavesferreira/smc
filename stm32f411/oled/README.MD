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

# Leitura AD

## Introdução ao Conversor Analógico-Digital no STM32F411

Em sistemas embarcados, muitos dispositivos, como sensores, potenciômetros e transdutores, geram sinais analógicos que precisam ser convertidos em valores digitais para serem processados pelo microcontrolador. Essa função é realizada pelo ADC, ou Conversor Analógico-Digital.

O STM32F411 possui um ADC do tipo SAR (*Successive Approximation Register*) com resolução de 12 bits, permitindo representar a tensão medida por valores de 0 a 4095. Considerando uma referência de 3,3 V, uma entrada de 0 V resulta em valor próximo de 0, enquanto uma entrada próxima de 3,3 V resulta em valor próximo de 4095.

O ADC pode ler diferentes canais analógicos por meio de uma seleção interna semelhante a um multiplexador. As conversões podem ocorrer em modo simples, contínuo ou em sequência de canais (*scan mode*). Também é possível iniciar conversões por software ou por eventos gerados por temporizadores.

Quando associado ao DMA, o ADC transfere os dados convertidos diretamente para a memória, reduzindo a carga da CPU. Assim, o ADC do STM32F411 permite medir grandezas físicas e utilizá-las em aplicações de monitoramento, controle e aquisição de dados.

<img src=../imagens/sar.png>

A figura apresenta a estrutura básica de um conversor ADC do tipo SAR, usado para transformar uma tensão analógica em um valor digital.
O sinal de entrada passa primeiro pelo bloco SHA (*Sample-and-Hold*), responsável por amostrar a tensão e mantê-la estável durante o tempo necessário para a conversão.
Em seguida, o comparador verifica a diferença entre a tensão amostrada e a tensão gerada internamente pelo DAC. A lógica SAR ajusta esse valor passo a passo, por aproximações sucessivas, até encontrar o número digital que melhor representa a tensão de entrada.
A temporização controla os instantes de amostragem, comparação e atualização dos blocos internos, garantindo que a conversão ocorra de forma ordenada e precisa.

Para uma descrição completa de todos os modos disponíveis, recomenda-se consultar a nota de aplicação <a href=https://www.st.com/content/ccc/resource/technical/document/application_note/c4/63/a9/f4/ae/f2/48/5d/CD00258017.pdf/files/CD00258017.pdf/jcr:content/translations/en.CD00258017.pdf>AN3116 da STMicroelectronics</a>.


### Características do ADC

Conjunto de parâmetros que define como o conversor analógico-digital mede, converte e representa uma tensão analógica em valor digital.

### Resolução

Quantidade de bits usada na conversão, determinando quantos níveis digitais o ADC consegue representar.

### Taxa de amostragem

Quantidade de leituras ou conversões que o ADC consegue realizar por segundo, geralmente expressa em amostras por segundo.

### Tensão de referência

Tensão máxima usada como base de comparação para converter a entrada analógica em valor digital.

### Resolução de tensão

Menor variação de tensão que o ADC consegue distinguir entre dois níveis digitais consecutivos.

Segue revisado, com uma linha para cada conceito:

# Polling, Interrupção e DMA

Ao trabalhar com leituras ADC, podem ser escolhidos três métodos principais para obter o resultado da conversão:

## Polling

O microcontrolador inicia a conversão ADC e fica aguardando até que o resultado esteja disponível.

## Interrupção

O microcontrolador inicia a conversão ADC e continua executando outras tarefas, sendo avisado por uma interrupção quando a leitura termina.

## DMA

O ADC transfere automaticamente os dados convertidos para a memória, sem exigir intervenção constante da CPU.



## exemplos de código


### Método Polling

Altere a frequência de clock com o cristal externo em 48MHZ

Configure AD para o canal :  Analog > ADC selecione "IN7", mantenha as configurações padrões

Hailibite o TIM3 e configure para gerar uma interrução a cada um segundo, utilizando preescalaer em 48000-1 e contador em 1000-1

<img src=../imagens/tim3.png>
<BR><BR>
<img src=../imagens/in7.png>


### codigo para leitura AD com temporizador tim3

```java
  ssd1306_Init();
  char buff[64];
  volatile uint32_t leitura_ad=0;  // variavel ad

  HAL_TIM_Base_Start(&htim3);  // temporizador

  while (1)
  {

	  if(__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE)){
	  	  	    __HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);
                // ADC COM POLLING
	  	  	    HAL_ADC_Start(&hadc1);
	  	  	    HAL_ADC_PollForConversion(&hadc1, 100); // aguarda a conversao ser concluida
	  	  	    leitura_ad=HAL_ADC_GetValue(&hadc1);
	  	  	    HAL_ADC_Stop(&hadc1);

	  		    ssd1306_Fill(Black);
	  		    ssd1306_SetCursor(4, 22);
	  		    ssd1306_WriteString("Leitura AD", Font_16x15, White);
	  		    ssd1306_SetCursor(4, 44);
	  		    sprintf(buff, "%lu ", (unsigned long)leitura_ad);

	  		    ssd1306_WriteString(buff, Font_11x18, White);
	  		    ssd1306_UpdateScreen();
	  	  	  }
```

### Método ADC por interrução

Considere as configurações realizadas no método polling, habilitando o método interrupção. Vá em ANALOG> ADC > NVIC Setting e habilite a interrupção

Como de costume, precisamos definir a rotina de serviço de interrupção (ISR) conectada à interrupção do ADC, atribuir a prioridade de interrupção desejada e habilitar a IRQ correspondente. Como todos os outros periféricos da HAL, precisamos chamar a função HAL_ADC_IRQHandler() da ISR do ADC e implementar a rotina de retorno de chamada HAL_ADC_ConvCpltCallback(), que é chamada automaticamente pela HAL quando uma conversão termina. Finalmente, todas as interrupções relacionadas ao ADC são habilitadas iniciando o ADC usando a função HAL_ADC_Start_IT().


```java
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	char msg[20];
	uint16_t rawValue;
	float temp;
	rawValue = HAL_ADC_GetValue(&hadc1);
	temp = ((float)rawValue) / 4095 * 3300;
	temp = ((temp - 760.0) / 2.5) + 25;
	sprintf(msg, "rawValue: %hu\r\n", rawValue);
	HAL_UART_Transmit(&huart2, (uint8_t*) msg, strlen(msg), HAL_MAX_DELAY);
	sprintf(msg, "Temperature: %f\r\n", temp);
	HAL_UART_Transmit(&huart2, (uint8_t*) msg, strlen(msg), HAL_MAX_DELAY);
}


int main(void) {
	HAL_Init();
	Nucleo_BSP_Init();
	/* Initialize all configured peripherals */
	MX_ADC1_Init();
	HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(ADC_IRQn);
	HAL_ADC_Start_IT(&hadc1);
	while (1);
		}
		void ADC_IRQHandler(void) {
		HAL_ADC_IRQHandler(&hadc1);
		}
}

```

### Método Conversão AD em modo DMA

No **STM32F411**, a conversão do **ADC em modo DMA** funciona assim: o ADC faz as leituras analógicas e o **DMA copia automaticamente os valores convertidos para um vetor na RAM**, sem a CPU precisar buscar cada amostra manualmente.

Esse modo é muito útil quando você quer:

```text
ler continuamente um canal analógico
ler vários canais ADC em sequência
usar um timer para amostrar em frequência fixa
reduzir o uso da CPU
```

### Ideia principal

Em vez de fazer:

```c
HAL_ADC_Start(&hadc1);
HAL_ADC_PollForConversion(&hadc1, timeout);
valor = HAL_ADC_GetValue(&hadc1);
```

você usa:

```c
HAL_ADC_Start_DMA(&hadc1, buffer_adc, tamanho);
```

A partir daí, o ADC converte e o DMA grava os resultados no vetor:

```c
uint32_t buffer_adc[4];
```

Por exemplo, se você estiver lendo 4 canais, o DMA pode preencher:

```text
buffer_adc[0] -> canal 1
buffer_adc[1] -> canal 2
buffer_adc[2] -> canal 3
buffer_adc[3] -> canal 4
```

### Passos para usar ADC com DMA no STM32F411

Primeiro você configura o **ADC1** no CubeMX. No STM32F411, normalmente usa-se o **ADC1**, porque ele é o conversor ADC principal disponível nessa família.

Depois, configure o ADC conforme o tipo de leitura:

```text
Scan Conversion Mode: Enabled, se usar vários canais
Continuous Conversion Mode: Enabled, se quiser conversão contínua
DMA Continuous Requests: Enabled
Data Alignment: Right
Resolution: 12 bits
```

Depois você configura o **DMA** associado ao ADC1. No STM32F411, o ADC1 usa normalmente:

```text
DMA2
Stream 0
Channel 0
```

O DMA pode ser configurado como:

```text
Mode: Circular
Peripheral to Memory
Peripheral increment: Disabled
Memory increment: Enabled
Data width: Half Word ou Word
```

O modo **Circular** é importante quando você quer que o ADC fique convertendo continuamente e preenchendo o mesmo buffer em ciclo.

### Ligação entre ADC e DMA

No código HAL, o DMA precisa ser ligado ao ADC com a macro:

```c
__HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);
```

Quando você usa CubeMX/CubeIDE, isso geralmente é gerado automaticamente dentro da função:

```c
HAL_ADC_MspInit()
```

### Iniciando a conversão

Depois da inicialização do sistema, GPIO, DMA e ADC, você inicia assim:

```c
uint32_t adc_buffer[1];

HAL_ADC_Start_DMA(&hadc1, adc_buffer, 1);
```

Para vários canais:

```c
uint32_t adc_buffer[3];

HAL_ADC_Start_DMA(&hadc1, adc_buffer, 3);
```

Nesse caso, o tamanho passado deve corresponder ao número de conversões da sequência ADC.

### Callback de fim de conversão

Quando o DMA termina de preencher o buffer, a HAL pode chamar:

```c
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
        // dados novos disponíveis em adc_buffer
    }
}
```

Se o DMA estiver em modo circular, essa função será chamada repetidamente a cada ciclo completo do buffer.

### Resumo prático para STM32F411

Para usar ADC com DMA no STM32F411:

```text
1. Configure o ADC1.
2. Ative DMA Continuous Requests.
3. Configure o DMA2 Stream 0 Channel 0 para ADC1.
4. Use modo Circular se quiser leitura contínua.
5. Inicie com HAL_ADC_Start_DMA().
6. Leia os valores no vetor preenchido pelo DMA.
7. Use HAL_ADC_ConvCpltCallback() se quiser tratar o fim da conversão.
```

Exemplo simples:

```c
uint32_t adc_buffer[1];

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_ADC1_Init();

    HAL_ADC_Start_DMA(&hadc1, adc_buffer, 1);

    while (1)
    {
        // adc_buffer[0] contém o valor atual do ADC
    }
}
```


# Referências
<a href=https://www.st.com/resource/en/reference_manual/rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf> Reference Manual STM32F411<a/>

<a href=https://www.st.com/resource/en/application_note/cd00211314.pdf>How to optimize the ADC accuracy </a>




