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

// Variáveis para controle do estado da etapa 

char etapasUNO=0;
 
String mensagemPedido = ""; // Variável para armazenar a mensagem do pedido finalizado
String Cafe = "";
String tamanho = "";
String Leite = "";
String Cha = "";

//===============================================================
// funcoes respondem a pagina web
//===============================================================
void handleRoot() {
  String s = MAIN_page; // Read HTML contents
  s.replace("__MSG__", mensagemPedido); // Replace placeholder with the value of 'mensagemPedido'
  server.send(200, "text/html", s); // Send web page
}

void handleFazerPedido() {
  Cafe = server.arg("cafe");
  tamanho = server.arg("tamanho");
  Cha = server.arg("cha");
  Leite= server.arg("leite");
  digitalWrite(ledPin, HIGH); // Ligar o LED na porta 27
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Fazendo pedido...");
  Serial.println("Fazendo pedido ");
  Serial.print("==Cafe:");
  Serial.println(Cafe);
  Serial.print("==Tamanho: ");
  Serial.println(tamanho);
  Serial.print("==Cha: ");
  Serial.println(Cha);
  Serial.print("==Leite: ");
  Serial.println(Leite);
  // enviar para UNO serial 2 as escolhas acompanhando as letras de inicio PSxTxCx
  Serial2.print("PC");
  Serial2.print(Cafe);
  Serial2.print("T");
  Serial2.print(tamanho);
  Serial2.print("C");
  Serial2.print(Cha);
   Serial2.print("L");
  Serial2.println(Leite);
  server.send(200, "text/plain", "Informação 1 enviada para o Arduino!");
      display.setCursor(0, 10);
    display.println("fazendo pedido...");
    display.display();
  delay(1000); // Aguardar 1 segundo
  server.send(200, "text/plain", "Pedido realizado com sucesso!");
}

void handlecancelarPedido() {
    Serial.print("Cancelar Pedido");
    // enviar para serial 2 as escolhas
    Serial2.print("PR0000000");   // comunica com UNO para suspender pedido
     Serial2.print("\n");
    server.send(200, "text/plain", "Cancelando pedido!");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
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

    // Inicialização do display OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
   display.setCursor(0, 10);
    display.println("procurando redes...");
    display.display();
  
  setup_wifi();   // script para conexao wifi
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 30);
  display.println(WiFi.localIP());
  display.display();
 delay(3000);
  pinMode(ledPin, OUTPUT); // Configure the LED pin 27 as output
  pinMode(ledPin2, OUTPUT); // Configure the LED pin 27 as output

   /// handle são a resposta requisicao da pagina
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
    //  if (data == 'Y') {   Serial.println(" DIGITOU Y ");  }
      Serial2.write(data);
      }

  if (Serial2.available()) {
      // Ler dados do Arduino Uno e retransmitir para a comunicação serial
      char datauno = Serial2.read();
      Serial.write(datauno);
  
    if (datauno == 'I') {  etapasUNO=0;  Serial.println("Estado Inicial");   } // Verificar se a mensagem recebida é "chegou"   
    if (datauno == 'O') {  etapasUNO=1;  } //   
    if (datauno == 'Q') {  etapasUNO=2;  } // 
    if (datauno == 'R') {  etapasUNO=3;   } // 
    if (datauno == 'S') {  etapasUNO=4; }    // 

    if (datauno == 'T') {  etapasUNO=5; }    // 
    if (datauno == 'U') {  etapasUNO=6;    }     // Ativar a etapa pedido pronto
    if (datauno == 'V') {  etapasUNO=7;    }      // etapa Fimprocess
    if (datauno == 'C') {  etapasUNO=8;   }     // Ativar pedidoCancelado
    }
 
    // Verificar o estado da etapa sorvete e exibir no display OLED
    // Captura o tempo atual
    if (( tempoAtual - millis())>300) {    // atualiza o display a cada 300ms
        tempoAtual = millis();
         display.clearDisplay();
         display.setTextSize(1);
         display.setTextColor(SSD1306_WHITE);
         display.setCursor(0, 0);
         if ( etapasUNO==0 )  {
             display.println("Aguardando pedido...");
             mensagemPedido="Aguardando pedido...";   }
         if ( etapasUNO==1) {   
             display.println("Inicio de processo ....");   
             mensagemPedido="Inicio de processo ....";    } 
         if ( etapasUNO==2) {   
             display.println("Enchendo Agua");   
             mensagemPedido="Enchendo Agua";    } 
         if (etapasUNO==3) {  
             display.println("Cafe...");
             mensagemPedido="Cafe...";     }
        if (etapasUNO==4) {   
             display.println("Leite...");
             mensagemPedido="Leite...";     }
         if (etapasUNO==5) {
              mensagemPedido="Cha...";     
              display.println("Etapa Cha");   }
         if (etapasUNO==6) {
              mensagemPedido="Finalizando...";  
              display.println("Finalizando pedido");  }
         if (etapasUNO==7) {
              mensagemPedido="Reinicializando...";  
              display.println("Reinicializando");
             } 
         if(etapasUNO==8){
            mensagemPedido="Pedido cancelado...";  
              display.println("pedido cancelado");
                }
         display.display();
       }   // fim atualizacao oled
       server.handleClient();
       delay(1);
}
