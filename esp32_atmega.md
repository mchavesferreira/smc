

Programas para comunicação entre um o microcontrolador ATmega328P e outro para o ESP32, que permitem a comunicação entre os dois através da UART. O ATmega328P informa o status de 4 pinos de entrada e 4 pinos de saída para o ESP32, que mostra essas informações em uma página HTML. Certifique-se de conectar corretamente os pinos RX e TX entre os dois microcontroladores.

ATmega328P (enviando status para o ESP32):

```java
#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3); // RX, TX

const int inputPin1 = 4;
const int inputPin2 = 5;
const int inputPin3 = 6;
const int inputPin4 = 7;

const int outputPin1 = 8;
const int outputPin2 = 9;
const int outputPin3 = 10;
const int outputPin4 = 11;

void setup() {
  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);
  pinMode(inputPin3, INPUT);
  pinMode(inputPin4, INPUT);

  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);
  pinMode(outputPin3, OUTPUT);
  pinMode(outputPin4, OUTPUT);

  Serial.begin(9600);
  espSerial.begin(9600);
}

void loop() {
  int inputStatus1 = digitalRead(inputPin1);
  int inputStatus2 = digitalRead(inputPin2);
  int inputStatus3 = digitalRead(inputPin3);
  int inputStatus4 = digitalRead(inputPin4);

  digitalWrite(outputPin1, HIGH);
  digitalWrite(outputPin2, LOW);
  digitalWrite(outputPin3, HIGH);
  digitalWrite(outputPin4, LOW);

  String message = String(inputStatus1) + ";" + String(inputStatus2) + ";" + String(inputStatus3) + ";" + String(inputStatus4);
  espSerial.println(message);

  delay(1000);
}
```

Código para ESP32

```java

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "NOME_REDE_WIFI";
const char* password = "SENHA_REDE_WIFI";

AsyncWebServer server(80);

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String inputStatus = Serial.readStringUntil('\n');
    inputStatus.trim();

    String html = "<html><body>";
    html += "<h1>Status dos pinos:</h1>";
    html += "<p>Pino 1: " + inputStatus.substring(0, 1) + "</p>";
    html += "<p>Pino 2: " + inputStatus.substring(2, 3) + "</p>";
    html += "<p>Pino 3: " + inputStatus.substring(4, 5) + "</p>";
    html += "<p>Pino 4: " + inputStatus.substring(6, 7) + "</p>";
    html += "</body></html>";

    request->send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
}

```

Código para Atmega228P
