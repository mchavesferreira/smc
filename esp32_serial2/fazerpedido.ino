#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "index.h"  //Web page header file

WebServer server(80);
int i = 0;

// LED na porta 27
const int ledPin = 19;
const int ledPin2 = 4;

// Comunicação Serial
const int serialBaudRate = 115200;
const int serialDataTimeout = 1000;  // Tempo de espera para receber dados via serial (1 segundo)

// Enter your SSID and PASSWORD
const char* ssid = "ifsp-ibge-1";
const char* password = "ifspcatanduva";

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

//===============================================================
// This routine is executed when you open its IP in a browser
//===============================================================
void handleRoot() {
  String s = MAIN_page; // Read HTML contents
  s.replace("__MSG__", mensagemPedido); // Replace placeholder with the value of 'mensagemPedido'
  server.send(200, "text/html", s); // Send web page
}

String sabor = "";
String tamanho = "";
String calda = "";


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
  Serial.print("Fazendo pedido ");
  Serial.println("==Sabor:");

    Serial.println(sabor);
       Serial.println("==Tamanho: ");
      Serial.println(tamanho);
         
 
      Serial.println(calda);
             Serial.println("===Calda: ");
// enviar para serial 2 as escolhas
Serial2.println(sabor);
Serial2.println(tamanho);
Serial2.println(calda);

  server.send(200, "text/plain", "Informação 1 enviada para o Arduino!");

  etapaFimprocesso = false;
  display.display();
  delay(1000); // Aguardar 1 segundo
  digitalWrite(ledPin, LOW); // Desligar o LED
  
  Serial2.println("S"); // Enviar mensagem "chegou" via comunicação serial para o Arduino Uno
 Serial.print("enviando S ");
  server.send(200, "text/plain", "Pedido realizado com sucesso!");
}

void handlecancelarPedido() {
  Serial2.println("N"); // Enviar mensagem "chegou" via comunicação serial para o Arduino Uno
 digitalWrite(ledPin2, HIGH); // Ligar o LED na porta 27
 delay(1000);
  digitalWrite(ledPin2, LOW); // Ligar o LED na porta 27

}

//===============================================================
// Setup
//===============================================================

void setup(void) {
  Serial.begin(serialBaudRate);
  Serial.setTimeout(serialDataTimeout);
  Serial2.begin(9600);
  
  Serial.println();
  Serial.println("Booting Sketch...");

  WiFi.mode(WIFI_STA); // Connect to your wifi
  WiFi.begin(ssid, password);

  Serial.println("Connecting to ");
  Serial.print(ssid);

  // Wait for WiFi to connect
  while(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.print(".");
  }

  // If connection successful, show IP address in serial monitor
  Serial.println("");
  Serial.print("Conectado em SSID: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // IP address assigned to your ESP

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
  server.begin(); // Start the webserver
Serial.println("HTTP server started");
}

//===============================================================
// Loop
//===============================================================

void loop(void) {
if (Serial.available()) {
// Ler dados da comunicação serial e retransmitir para o Arduino Uno
char data = Serial.read();
Serial2.write(data);
}

if (Serial2.available()) {
// Ler dados do Arduino Uno e retransmitir para a comunicação serial
char data = Serial2.read();
Serial.write(data);
// Verificar se a mensagem recebida é "chegou"
if (data == 'G') {
etapaSorvete = true; // Ativar a etapa sorvete
}
if (data == 'U') {
etapaMotor = true; // Ativar a etapa agitação
}
if (data == 'T') {
etapaCobertura = true; // Ativar a etapa cobertura
}
if (data == 'L') {
etapaPronto = true; // Ativar a etapa pedido pronto
}
if (data == 'F') {
etapaFimprocesso = true; // Ativar a etapa Final
}
if (data == 'C') {
pedidoCancelado = true; // Ativar a etapa sorvete
}
}
 

// Verificar o estado da etapa sorvete e exibir no display OLED


display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println("Aguardando pedido...");


if (etapaSorvete) {
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println("Etapa Sorvete");
} 

if (etapaMotor) {
  etapaSorvete = false;
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println("Agitando...");
}
if (etapaCobertura) {
   etapaMotor = false;
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println("Etapa Calda");
}
if (etapaPronto) {
  etapaCobertura = false;
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println("Pedido pronto");
}
if (etapaFimprocesso) {
  etapaPronto = false;
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println("Fim do processo");
delay(2000);
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println("Aguardando novo pedido...");
}

if(pedidoCancelado){
  display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println("pedido cancelado");
delay(2000);
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println("Aguardando novo pedido...");
}

display.display();

server.handleClient();
delay(1);
}


