

Código para ESP32

Código para o primeiro programa
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
