/// versao 11/06/2025
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "index.h"  // pagina web
#include "funcoes.h"  //variaveis e funcoes wifi

WebServer server(80);
// Variaveis
int i = 0;
const int ledPin = 19;
const int ledPin2 = 4;
unsigned long tempoAtual;
// Comunicação Serial
const int serialBaudRate = 115200;
const int serialDataTimeout = 1000;  // Tempo de espera para receber dados via serial (1 segundo)

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_ADDRESS);

// Variáveis para controle do estado da etapa sorvete
bool etapaSorvete = false;
bool etapaMotor = false;
bool etapaCobertura = false;
bool etapaPronto = false;
bool etapaFimprocesso = false;
bool pedidoCancelado = false;

String mensagemPedido = ""; // Variável para armazenar a mensagem do pedido finalizado
String sabor = "";
String tamanho = "";
String calda = "";

//===============================================================
// funcoes respondem a pagina web
//===============================================================
void handleRoot() {
  String s = MAIN_page; // Read HTML contents
  s.replace("__MSG__", mensagemPedido); // Replace placeholder with the value of 'mensagemPedido'
  server.send(200, "text/html", s); // Send web page
}

void handleFazerPedido() {
  sabor = server.arg("sabor");
  tamanho = server.arg("tamanho");
  calda = server.arg("calda");
  digitalWrite(ledPin, HIGH); // Ligar o LED na porta 27
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Fazendo pedido...");
  Serial.println("Fazendo pedido ");
  Serial.print("==Sabor:");
  Serial.println(sabor);
  Serial.print("==Tamanho: ");
  Serial.println(tamanho);
  Serial.print("==Calda: ");
  Serial.println(calda);
  // enviar para UNO serial 2 as escolhas acompanhando as letras de inicio PSxTxCx
  Serial2.print("PS");
  Serial2.print(sabor);
  Serial2.print("T");
  Serial2.print(tamanho);
  Serial2.print("C");
  Serial2.println(calda);
  server.send(200, "text/plain", "Informação 1 enviada para o Arduino!");
  etapaFimprocesso = false;
  display.display();
  delay(1000); // Aguardar 1 segundo
  server.send(200, "text/plain", "Pedido realizado com sucesso!");
}

void handlecancelarPedido() {
    Serial.print("Cancelar Pedido");
    // enviar para serial 2 as escolhas
    Serial2.print("CS");   // comunica com UNO para suspender pedido
    server.send(200, "text/plain", "Cancelando pedido!");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("cancelando pedido...");
    display.display();
}

void handlemsgoled() {
   server.send(200, "text/html", mensagemPedido); // atualiza o status no display webpage
}

//===============================================================
// Setup
//===============================================================

void setup(void) {
  Serial.begin(serialBaudRate);
  Serial.setTimeout(serialDataTimeout);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println("Setup inicial... ");
  setup_wifi();   // script para conexao wifi

  pinMode(ledPin, OUTPUT); // Configure the LED pin 27 as output
  pinMode(ledPin2, OUTPUT); // Configure the LED pin 27 as output

  // Inicialização do display OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();

  server.on("/", handleRoot); // Main root page
  server.on("/fazerpedido", handleFazerPedido); // Handle the request for fazer pedido
  server.on("/cancelarpedido", handlecancelarPedido); // Handle the request for cancelar pedido
  server.on("/msgoled", handlemsgoled);
  server.begin(); // Start the webserver
  Serial.println("HTTP server started");
  tempoAtual = millis(); // Captura o tempo atual
}

//===============================================================
// Loop
//===============================================================

void loop(void) {
  // Reconnect WiFi if not connected
  while (WiFi.status() != WL_CONNECTED) {
      setup_wifi();
  }  
  
  if (Serial.available()) {
      // Ler dados da comunicação serial e retransmitir para o Arduino Uno
      char data = Serial.read();
      if (data == 'Y') {   Serial.println(" DIGITOU Y ");  }
      Serial2.write(data);
      }

  if (Serial2.available()) {
      // Ler dados do Arduino Uno e retransmitir para a comunicação serial
      char datauno = Serial2.read();
      Serial.write(datauno);
  
    if (datauno == 'Y') {   Serial.println(" recebeu do uno Y ");   } // Verificar se a mensagem recebida é "chegou"   
    if (datauno == 'G') {  etapaSorvete = true;  } // Ativar flag  etapa sorvete
    if (datauno == 'U') {  etapaMotor = true;    } // Ativar a etapa agitação
    if (datauno == 'T') {  etapaCobertura = true; }    // Ativar a etapa agitação
    if (datauno == 'L') {  etapaPronto = true;    }     // Ativar a etapa pedido pronto
    if (datauno == 'F') {  etapaFimprocesso = true;   }      // Ativar a etapa Final
    if (datauno == 'C') {  pedidoCancelado = true;   }     // Ativar a etapa sorvete
    }
 
    // Verificar o estado da etapa sorvete e exibir no display OLED
    // Captura o tempo atual
    if (( tempoAtual - millis())>300) {    // atualiza o display a cada 300ms
        tempoAtual = millis();
         display.clearDisplay();
         display.setTextSize(1);
         display.setTextColor(SSD1306_WHITE);
         display.setCursor(0, 0);
         if ( !etapaSorvete || !etapaMotor || !etapaCobertura || !etapaPronto )  {
             display.println("Aguardando pedido...");
             mensagemPedido="Aguardando pedido...";   }
         if (etapaSorvete) {   
             display.println("Etapa Sorvete");   
             mensagemPedido="Etapa Sorvete";    } 
         if (etapaMotor) {  
             etapaSorvete = false;   
             display.println("Agitando...");
             mensagemPedido="Agitando...";     }
         if (etapaCobertura) {
              etapaMotor = false;
              display.println("Etapa Calda");   }
         if (etapaPronto) {
              etapaCobertura = false;
              display.println("Pedido pronto");  }
         if (etapaFimprocesso) {
              etapaPronto = false;
              display.println("Fim do processo");
              delay(2000);
              display.println("Aguardando novo pedido...");   } 
         if(pedidoCancelado){
              display.println("pedido cancelado");
              pedidoCancelado = false;
              delay(2000);    }
         display.display();
       }   // fim atualizacao oled
       server.handleClient();
       delay(1);
}
