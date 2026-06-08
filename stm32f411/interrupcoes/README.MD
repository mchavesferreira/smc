# INTERRUPÇÕES

## NVIC (Nested Vectored Interrupt Controller)

O NVIC é o controlador de interrupções integrado ao núcleo ARM Cortex-M4 do STM32F411. Sua função é gerenciar todas as interrupções do sistema de forma rápida e eficiente, permitindo que eventos importantes sejam atendidos imediatamente sem a necessidade de o programa principal ficar verificando constantemente o estado dos periféricos.

O NVIC do STM32F411 suporta até 62 interrupções externas mascaráveis, além das 16 exceções internas do Cortex-M4, e permite definir 16 níveis de prioridade. Quando uma interrupção ocorre, o hardware identifica automaticamente qual rotina deve ser executada através da tabela de vetores, salva o contexto do processador e transfere o controle para a função de tratamento (ISR).

## Mapeamento das Funções Alternativas (Alternate Functions - AF) dos pinos GPIO
A tabela Alternate Function Mapping informa qual valor AF (AF0 a AF15) deve ser programado nos registradores AFRL/AFRH para conectar um periférico interno a um determinado pino GPIO. Por exemplo, AF7 conecta os periféricos USART1 e USART2, AF5 conecta SPI1 e SPI2, e AF4 conecta os módulos I²C. Ao configurar um pino para função alternativa, o registrador MODER deve ser ajustado para o modo Alternate Function e o registrador AFR deve receber o número AF correspondente ao periférico desejado. Isso permite que um mesmo pino físico desempenhe diferentes funções conforme a necessidade da aplicação.


## Multi-AHB matrix 
<img width="710" height="175" alt="image" src="https://github.com/user-attachments/assets/70ee6e86-39b6-4775-bcf8-77ca769c835d" />

A Bus Matrix AHB do STM32F411 é uma estrutura interna de interconexão de 32 bits que liga os mestres (CPU e controladores DMA) aos escravos (Flash, SRAM e periféricos). Ela funciona como um sistema inteligente de roteamento de dados, permitindo múltiplos acessos simultâneos aos recursos do microcontrolador, reduzindo gargalos e aumentando o desempenho quando diversos periféricos operam ao mesmo tempo.
<img width="1480" height="924" alt="image" src="https://github.com/user-attachments/assets/6ec84e67-ff57-44d5-a58a-e78983849bd9" />


### O **Batch Acquisition Mode (BAM)** 

É uma técnica de economia de energia utilizada em aplicações de aquisição de dados. Durante esse modo, o processador praticamente "dorme", enquanto o DMA continua coletando informações dos sensores e armazenando-as diretamente na SRAM. Como a CPU, a Flash e diversos periféricos permanecem desligados ou com seus clocks interrompidos, o consumo de energia é significativamente reduzido.


<img width="1048" height="682" alt="image" src="https://github.com/user-attachments/assets/029e54ca-7ce9-4c97-8c7b-59a45eec25b6" />

#### Exemplo do Modo de Aquisição em Lote (Batch Acquisition Mode - BAM)

Os dados são transferidos através do **DMA** das interfaces de comunicação para a **SRAM interna**, enquanto o restante do microcontrolador é colocado em modo de baixo consumo de energia.

* O código é executado a partir da **RAM** antes do desligamento da memória Flash.
* A memória **Flash** é colocada em modo de desligamento (*Power Down*) e o clock da interface Flash (**ART™ Accelerator**) é interrompido.
* Os clocks permanecem habilitados apenas para as interfaces realmente necessárias.
* O núcleo do microcontrolador (**MCU Core**) é colocado em modo de espera (*Sleep Mode*), com o clock do processador interrompido aguardando uma interrupção.
* Apenas os canais DMA necessários permanecem habilitados e em funcionamento.

