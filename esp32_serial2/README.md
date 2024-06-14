# ESP32 IOT

 
## Aplicações de Internet das Coisas com ESP32
- [Webserver](#Webserver)
- [Criando comunicação para IOT](#Criando-comunicação-para-IOT)
	- [Acess-Point](#Acess-Point)
	- [Oled](#display-oled)
- [Residencial e IOT](#Residencial-e-IOT)

	
## Webserver
<BR>01- Criando um web server para controle e exibição de dados (Dashboard)<BR>
	
 <BR> <img src=https://github.com/mchavesferreira/mcr/blob/main/esp32_iot/imagens/webserver.png>
	
<BR>Um servidor Web é um programa que usa HTTP (Hypertext Transfer Protocol) para servir os arquivos que formam páginas da Web aos usuários, em resposta às suas solicitações (métodos GET ou POST), que são encaminhadas pelos clientes HTTP de seus computadores ou smartphones.
<BR>Para implementar uma pagina web no Esp32, existem duas maneiras de fazer: 
	<BR><b>-Web Server</b> - o servidor web primeiro se conectar ao seu roteador WiFi; ou
	<BR><b>-Acess Point</b> - tornar o Esp32 como ponto de acesso.
<BR>A ideia do Access Point (AP) é criar um ponto de acesso, uma rede WiFi, com nome e senha personalizadas para podermos criar uma rede local e comunicar com o ESP32. 
<BR>O access point é uma opção em locais onde não existe uma rede WiFi para conectar o ESP32, ou então existe, mas ela é instável ou inacessível.

O Esp32 disponiliza 4 modos diferentes de Wifi:

Modo estação:  utilizado para conectar o Esp32 à uma rede WiFi existente. 

Modo SOFTAP (acess point): Este é o modo utilizado para criar apenas o ponto de acesso. Por padrão, o IP do NodeMcu será 192.168.4.1. 

Modo STATIONAP: Neste modo o Esp32 é capaz de trabalhar no modo de estação e no modo SOFTAP.

Modo nulo: Este modo coloca o WiFi do Esp32 em um estado de baixo consumo, como se o módulo do WiFi ficasse desligado.

<P><b>Criando paginas html</B></p>
Todos os servidores web possuem uma página web a ser atendida. Primeiro faça uma página web usando HTML e teste-a no seu computador.
Você pode testar uma pagina web em seu navegador, utilizando bloco de notas para escrever o código HTML. Salve como index.htm e abra em seu browser.
	
	
```ruby
	<HTML>
	<HEAD>
		<TITLE>Minha primeira pagina web</TITLE>
	</HEAD>
<BODY>
	<CENTER>
		<B>Olá mundo.... </B>
	</CENTER>	
</BODY>
</HTML>
```

<a href=https://www.w3schools.com/htmL/default.asp>Guia de elementos html</a>. A w3schools disponiliza um vasto tutorial de formatação de elementos em Html e outras formatações para criação de paginas html.



<P><P>
  <b>Exemplo Modo Estação</b><BR>
 <img src=https://github.com/mchavesferreira/mcr/blob/main/esp32_iot/imagens/station.png>
  <BR><a href=https://github.com/mchavesferreira/mcr/blob/main/esp32_iot/webserver/webserver.ino>Codigo .ino estação</a>

<P><P>
  <b>Exemplo Acess-Point Wifi</b><BR>
  <img src=https://github.com/mchavesferreira/mcr/blob/main/esp32_iot/imagens/acesspoint.png>
  <BR><a href=https://github.com/mchavesferreira/mcr/blob/main/esp32_iot/acess_point/acess_point.ino>Codigo .ino acess point</a>
<p></p>
 <P> Observe o exemplo a seguir que cria um codigo html a partir utilizando o esp32 como servidor para controlar dois leds. </P>
<a href=acess_point/exemplo_botao.html target=_blank>html de resposta</a><P></P>

  <BR><a href=https://github.com/mchavesferreira/mcr/tree/main/esp32_iot/acesshtml>Codigo .ino e pagina web em index.h</a>

### Webserver com atualização sem recarga da pagina
  <img src=https://raw.githubusercontent.com/mchavesferreira/mcr/main/esp32_iot/webserverajax/montagem.png><BR>
  <img src=https://raw.githubusercontent.com/mchavesferreira/mcr/main/esp32_iot/webserverajax/circuito1.jpg><BR>
 Este exemplo mostra em um pagina web o valor de status ou leitura de pinos do Esp32 sem recarga da pagina.<P>
 <img src=https://raw.githubusercontent.com/mchavesferreira/mcr/main/esp32_iot/webserverajax/status.jpg><BR>
<BR>Salve os arquivos: webserver2.ino e index.h em uma pasta. Modifique senha e login de wifi.<BR>


   <BR><a href=https://github.com/mchavesferreira/mcr/tree/main/esp32_iot/webserverajax>Codigo webAjax </a> <BR>


<BR>
 O valores são substituidos nos "ID" a cada intervalo de tempo, buscando a String de uma url no próprio microcontrolador.


 ## ESP32 2 portas seriais

A porta serial 2 (UART2) do ESP32 pode ser configurada para usar vários pinos diferentes, já que os pinos UART são mapeáveis. Isso oferece flexibilidade para o design de hardware. Os pinos padrão para UART2 são:

    TX: GPIO17
    RX: GPIO16

No entanto, você pode remapear esses pinos para qualquer GPIO que seja capaz de suportar as funções UART.

Aqui está um exemplo de como configurar a porta serial 2 (UART2) usando a biblioteca HardwareSerial no Arduino IDE:

```ruby
 #include <HardwareSerial.h>

HardwareSerial Serial2(2);

void setup() {
  // Inicializa UART2 com 115200 baud rate
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  Serial2.println("UART2 initialized");
}

void loop() {
  if (Serial2.available()) {
    int data = Serial2.read();
    Serial2.print("Received: ");
    Serial2.println(data);
  }
```

![esp32_ligacao](https://github.com/mchavesferreira/smc/assets/63993080/ca737840-d948-4b4c-94e3-9a2036756f26)



### Projeto 2 

Exemplos para trabalho:

https://github.com/mchavesferreira/smc/blob/main/esp32_serial2/



 
