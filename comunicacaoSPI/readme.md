# Interface de Comunicação SPI no ATmega328P

A interface SPI (*Serial Peripheral Interface*) é um protocolo de comunicação síncrona que opera em modo *full-duplex*, permitindo transmissão e recepção de dados simultaneamente. No microcontrolador ATmega328P, essa comunicação é realizada por meio de quatro sinais principais:

* **MOSI** (*Master Output Slave Input*): linha utilizada para envio de dados do mestre para o escravo;
* **MISO** (*Master Input Slave Output*): linha responsável pelo envio de dados do escravo para o mestre;
* **SCLK** (*Serial Clock*): sinal de clock gerado pelo dispositivo mestre para sincronizar a comunicação;
* **SS** (*Slave Select*): sinal utilizado para selecionar o dispositivo escravo desejado.

Quando configurado como **escravo**, o ATmega328P recebe o sinal de clock do dispositivo mestre. Já no modo **mestre**, o microcontrolador gera o clock de sincronismo e utiliza um pino de controle para habilitar cada periférico conectado ao barramento SPI.

A comunicação SPI é amplamente empregada em diversos dispositivos eletrônicos, como conversores analógico-digitais, memórias Flash, cartões SD, relógios de tempo real e displays gráficos.

A figura a seguir representa a comunicação SPI entre dois dispositivos, enquanto outra configuração comum consiste em um mestre conectado a múltiplos escravos. Nesse caso, cada periférico possui um sinal **SS** independente, permitindo ao mestre selecionar individualmente o dispositivo com o qual deseja se comunicar.

figura: Comunicação entre o dispositivo mestre (master) e o escravo (slave) utilizando o protocolo SPI

<img width="789" height="582" alt="image" src="https://github.com/user-attachments/assets/a63edac4-a917-4b2f-af1d-d71eeca13370" />

figura: Comunicação entre um dispositivo mestre e três escravos utilizando a interface de comunicação SPI. 


<img width="776" height="216" alt="image" src="https://github.com/user-attachments/assets/449df24a-6cfe-4991-a0ba-3863be30fc48" />

<img width="600" height="194" alt="SPI-Communication-Module-Block-Diagram-600x194" src="https://github.com/user-attachments/assets/1357f394-5533-47b7-9b59-b6ab7c8fab00" />

<img width="845" height="187" alt="SPI-Working-Data-Transfer" src="https://github.com/user-attachments/assets/1f260eb9-f9e7-4dc1-a158-0be369c76068" />







