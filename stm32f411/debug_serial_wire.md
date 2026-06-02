# Debug do código

<img width="1032" height="319" alt="image" src="https://github.com/user-attachments/assets/d57eea73-4b91-4508-a158-e9645ca1877f" />



Ao habilitar **Serial Wire (SWD)** no STM32F411, você não está apenas permitindo a gravação do programa. Você passa a ter acesso a um conjunto muito poderoso de recursos de **debug em tempo real** através do ST-Link.

## Recursos disponíveis com SWD

### 1. Breakpoints

Permite parar a execução em uma linha específica.

Exemplo:

```c
HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
```

Você coloca um breakpoint nesta linha e o processador para exatamente antes dela ser executada.

---

### 2. Execução passo a passo

Você pode executar:

* Step Into (F5)
* Step Over (F6)
* Step Return (F7)

Por exemplo:

```c
Temperatura = LerSensor();
```

É possível entrar dentro da função e observar cada instrução sendo executada.

---

### 3. Visualização de variáveis

Durante a execução é possível observar:

```c
uint32_t contador;
float temperatura;
uint16_t adc;
```

em tempo real.

Exemplo:

```text
contador = 1250
adc = 2048
temperatura = 25.7
```

---

### 4. Alterar variáveis durante a execução

Você pode modificar:

```c
velocidadePWM = 50;
```

para

```c
velocidadePWM = 90;
```

sem recompilar.

Muito útil para testes de controle.

---

### 5. Visualização de registradores

É possível observar:

```text
R0
R1
R2
...
PC
SP
LR
```

e também os registradores dos periféricos.

Exemplo:

```text
TIM3_CNT
TIM3_PSC
TIM3_ARR
GPIOA_ODR
ADC1_DR
USART2_SR
```

---

### 6. Visualização de memória

Você pode abrir:

```text
Memory Browser
```

e visualizar:

```text
RAM
Flash
Registradores
```

Exemplo:

```text
0x20000000
```

para observar a SRAM.

---

### 7. Call Stack

Mostra como o programa chegou ao ponto atual.

Exemplo:

```text
main()
 └─ ControleMotor()
     └─ AtualizaPWM()
```

---

### 8. Observação de periféricos

Uma das funções mais interessantes para ensinar STM32.

Durante o debug:

```text
Peripherals
```

Você pode abrir:

```text
TIM3
GPIOA
USART2
ADC1
DMA1
```

e ver os registradores mudando em tempo real.

---

## Exemplo com TIM3

Se estiver ensinando timers, é possível observar:

```text
TIM3
 ├─ CNT
 ├─ PSC
 ├─ ARR
 └─ SR
```

e visualizar:

```text
CNT
0
1
2
3
...
499
0
1
2
```

em funcionamento.

Isso ajuda muito os alunos a entenderem como o contador realmente opera.

---

## Exemplo com PWM

Pode-se observar:

```text
TIM3_CCR1
```

mudando:

```text
100
200
300
400
```

e relacionar diretamente ao duty cycle.

---

## Exemplo com ADC

Durante a leitura:

```c
adc = HAL_ADC_GetValue(&hadc1);
```

você observa:

```text
ADC1_DR = 2048
```

e a variável:

```text
adc = 2048
```

ao mesmo tempo.

---

## Limitações do ST-Link V2

Com SWD usando o ST-Link V2 você possui:

✅ Gravação da Flash
✅ Breakpoints
✅ Watch Variables
✅ Step-by-Step
✅ Registradores
✅ Memória
✅ Periféricos
✅ Call Stack

Normalmente também há suporte a:

✅ SWV (Serial Wire Viewer)

Porém muitos clones do ST-Link V2 **não possuem o pino SWO conectado**, então o recurso pode não funcionar.

---

## Recursos avançados (dependem do SWO)

Se seu ST-Link e sua placa suportarem SWO, você pode usar:

### printf sem UART

Exemplo:

```c
printf("Temperatura = %.2f\n", temperatura);
```

aparecendo diretamente no CubeIDE.

---

### Contador de ciclos

Medir exatamente quantos ciclos uma função consome.

---

### Trace de eventos

Visualizar:

```text
Interrupção TIM3
Interrupção USART2
Interrupção ADC1
```

em sequência temporal.

---

<img width="684" height="660" alt="image" src="https://github.com/user-attachments/assets/9cda0a8d-1927-4016-9cbf-06eba2a8dac2" />

## Para a Black Pill STM32F411

Os recursos que mais valem a pena explorar nas aulas são:

1. Breakpoints.
2. Watch Variables.
3. Visualização dos registradores GPIO.
4. Visualização dos registradores TIM3.
5. Observação do contador CNT em tempo real.
6. Debug de interrupções (`HAL_TIM_PeriodElapsedCallback()`).
7. Visualização do ADC.
8. Visualização da UART.

Esses recursos já transformam completamente a forma de ensinar microcontroladores, pois os alunos deixam de ver o STM32 como uma "caixa preta" e passam a enxergar o que acontece internamente no hardware.
