# DMA (Direct Memory Access)

### O STM32F411CE possui 2 controladores DMA, com 8 streams por controlador e 7 channels por stream.

### Observação: dois channels no mesmo stream não podem ser usados ao mesmo tempo.

O DMA, ou **Direct Memory Access**, permite transferir dados entre periféricos e memória, memória e periféricos, ou até mesmo entre regiões de memória, sem que a CPU precise executar diretamente cada operação de cópia. Isso é muito útil em aplicações com ADC, USART, SPI, I2C e outros periféricos, pois reduz a carga de processamento do microcontrolador.

### Funções disponíveis para o usuário

```C
void DMA_Init(DMA_Config DMA);
void DMA_Interrupt(DMA_Config DMA);
void DMA_Enable(DMA_Config DMA);
```

### Cada função requer que uma struct seja passada com as configurações definidas pelo usuário. Os membros da estrutura são:

```C
typedef struct DMA_Config
{
	DMA_Stream_TypeDef *DMA_Stream;
	uint8_t channel;
	uint32_t *source_address;
	uint32_t *destination_address;
	uint8_t priority_level;
	uint8_t memory_size;
	uint8_t peripheral_size;
	uint8_t circular_mode;
	uint8_t direction;
	uint8_t packet_length;
	uint8_t interrupt_priority;
	uint8_t transfer_complete_interrupt;
	uint8_t half_transfer_interrupt;
	uint8_t transfer_error_interrupt;
	uint8_t direct_mode_error_interrupt;
}DMA_Config;
```

### Para ajudar o usuário a inserir os valores corretos nos membros da estrutura, as seguintes constantes são declaradas:

```C
#define DMA_Peripheral_To_Memory 0
#define DMA_Memory_To_Peripheral 1
#define DMA_Memory_To_Memory     2

#define Enable 1
#define Disable 0

#define DMA_Priority_Low           0
#define DMA_Priority_Medium        1
#define DMA_Priority_High          2
#define DMA_Priority_Very_High     3

#define DMA_memory_size_8	0
#define DMA_memory_size_16	1
#define DMA_memory_size_32	2

#define DMA_peripheral_size_8	0
#define DMA_peripheral_size_16	1
#define DMA_peripheral_size_32	2
```

### Um exemplo de declaração da estrutura é apresentado abaixo:

```C
DMA_Config DMA_I2S1;
```

### Exemplo simplificado:

```C
int data1,data2;

DMA_Config DMA;

DMA.DMA_Stream = DMA2_Stream2;
DMA.channel = 3;
DMA.circular_mode = Enable;
DMA.destination_address = &data1;
DMA.source_address = &data2;
DMA.direction = DMA_Memory_To_Memory;
DMA.memory_size = DMA_memory_size_8;
DMA.peripheral_size = DMA_peripheral_size_8;
DMA.packet_length = 100;
DMA_Init(DMA);
```

### Explicação do exemplo

Neste exemplo, é criada uma configuração chamada `DMA`, usando a estrutura `DMA_Config`.

A configuração seleciona o `DMA2_Stream2` e o `channel 3`. O modo circular é habilitado com `Enable`, indicando que a transferência pode ser repetida continuamente, dependendo da configuração interna da função `DMA_Init`.

Os campos `source_address` e `destination_address` indicam, respectivamente, o endereço de origem e o endereço de destino dos dados. Neste caso, o exemplo configura uma transferência do tipo `DMA_Memory_To_Memory`, ou seja, de uma região de memória para outra.

Os campos `memory_size` e `peripheral_size` foram definidos como 8 bits, usando as constantes `DMA_memory_size_8` e `DMA_peripheral_size_8`. O campo `packet_length` define a quantidade de dados que será transferida.

Por fim, a função `DMA_Init(DMA)` é chamada para aplicar a configuração definida na estrutura.

Fontes:

https://github.com/embeddedalpha/STM32F411CEU6/blob/main/DMA/README.md

