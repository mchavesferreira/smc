#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
//#include <String.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const char* ssid = "ifsp-ibge-1"; // Insira o nome da sua rede Wi-Fi
const char* password = "ifspcatanduva"; // Insira a senha da sua rede Wi-Fi

ESP8266WebServer server(80);
SoftwareSerial espSerial(D6, D7); // RX, TX

String info1 = "";
String info2 = "";
String info3 = "";
String info4 = "";
String info5 = "";
//String buttonState = "OFF";
int tempo, estado = 0, st = 0;
char env;

void pagina() {
  String message = "<html><head>";
  message += "<style>";
  message += ".info-title { color: #ffffff; }";
  message += "</style>";
  message += "<style>";
  message += ".info-box {";
  message += "  width: 200px;";
  message += "  height: 100px;";
  message += "  background-color: #000000;";
  message += "  color: #00ff00;";
  message += "  padding: 10px;";
  message += "  margin-bottom: 10px;";
  message += "  font-family: 'Courier New', monospace;";
  message += "  font-size: 14px;";
  message += "  line-height: 1.4;";
  message += "  border: 2px solid #00ff00;";
  message += "  border-radius: 5px;";
  message += "  overflow: auto;";
  message += "  box-shadow: 0 0 10px rgba(0, 255, 0, 0.3);";
  message += "  background-image: linear-gradient(#000000 50%, #0d0d0d 50%);";
  message += "  background-size: 100% 2px;";
  message += "}";
  message += "</style>";
  message += "<style>body { background-color: #f2f2f2; }</style>";
  message += "</head><body>";
  message += "<style>body h1{ text-align: center; color:#FF1493; font-size:40px;margin-top: 10px;text-decoration: underline;}</style>";
  message += "<div style='display: flex; align-items: center; justify-content: center;'>";
  message += "<p><h1><b>Spray Dryer</b></h1></p>";
  message += "<img src='https://blog.globesystems.com.br/wp-content/uploads/2021/04/processos-spray-dryer.png' width='300' height='200' style='margin-right: 10px;'>";
  message += "<div id='infoContainer'></div>";
  message += "</div>";
  message += "<style>body h8{text-align: left; color: black; margin-top: 50px; font-size:30px;margin-bottom: 15px;text-decoration: underline;}</style>";
  message += "<style>body h2{text-align: left; color: black; margin-top: 20px; font-size:20px; margin-bottom: 15px;display: inline;}</style>";
  message += "<p><b><h8>Painel de controle:</h8></b></p>";
  message += "<input type='submit' value='start'style='font-size: 24px; color: black; background-color:#00ff00;font-weight: bold;' onclick='inicio();'>";
  message += "<p><b><h8>Config. do produto:</h8></b></p>";
  message += "<p><h2>  Tipo de produto:  </h2>";
  message += "<select id='info1' name='info1'>";
  message += "<option value='P0'></option>";
  message += "<option value='P1'>Ovo</option>";
  message += "<option value='P2'>Cafe</option>";
  message += "<option value='P3'>Leite</option>";
  message += "<option value='P4'>Outro</option>";
  message += "</select>";
  message += "<input type='submit' value='Enter' style='background-color:#000080; color: white; font-weight: bold;' onclick='enviarInfo1();'>";
  message += "<style>body h3{text-align: center; color: black; margin-top: 20px; font-size:20px;margin-bottom: 15px;display: inline;}</style>";
  message += "<h3>  Deseja utilizar o ajuste padrao?  </h3>";
  message += "<select id='info2' name='info2'>";
  message += "<option value='0'></option>";
  message += "<option value='Y'>Sim</option>";
  message += "<option value='N'>Nao</option>";
  message += "</select>";
  message += "<input type='submit' value='Enter'style='background-color:#000080; color: white; font-weight: bold;'onclick='enviarInfo2();'></p>";
  message += "<p><b><h8>Config. da maquina:</h8></b></p>";
  message += "<style>body h4{text-align: left; color: blue; margin-top: 20px; font-size:20px;margin-bottom: 15px;display: inline;}</style>";
  message += "<p><h4>  Nivel(L): </h4>";
  message += "<input type='text' id='info3' name='info3'>";
  message += "<input type='submit' value='Enter'style='background-color:#000080; color: white; font-weight: bold;'onclick='enviarInfo3();'>";
  message += "<style>body h5{text-align: center; color: red; font-size:20px;display: inline;margin-bottom: 20px; margin-top: 30px;}</style>";
  message += "<h5>  Temperatura(oC):  </h5>";
  message += "<input type='text' id='info4' name='info4'>";
  message += "<input type='submit' value='Enter'style='background-color:#000080; color: white; font-weight: bold;'onclick='enviarInfo4();'>";
  message += "<style>body h6{text-align:right; color: green; margin-top: 20px;  font-size:20px;margin-bottom: 15px;display: inline;}</style>";
  message += "<h6>  Rotacao(rpm):  </h6>";
  message += "<input type='text' id='info5' name='info5'>";
  message += "<input type='submit' value='Enter'style='background-color:#000080; color: white; font-weight: bold;'onclick='enviarInfo5();'></p>";
  message += "<p><b><h8>Sensores:</h8></b></p>";
  message += "<p><h2>  Deslig. motor:  </h2>";
  message += "<input type='submit' value='Desligar'style='font-size: 24px; color: White; background-color: #ff0000;font-weight: bold;' onclick='motor();'>";
  message += "<h3>  Produto final:  </h3>";
  message += "<input type='submit' value='Acionar'style='font-size: 24px; color: black; background-color: #ffff00;font-weight: bold;' onclick='final();'>";
  message += "</form>";
  message += "<script>";
  message += "function enviarInfo1() {";
  message += "  var info1 = document.getElementById('info1').value;";
  message += "  var info1Text = document.getElementById('info1').options[document.getElementById('info1').selectedIndex].text;"; // Obtém o texto correspondente ao valor selecionado
  message += "  if (info1 !== '') {";
  message += "    var infoBox = document.getElementById('infoBox');";
  message += "    if (infoBox) {";
  message += "      var title = infoBox.querySelector('.info-title');"; // Obtém o título existente
  message += "      var content = infoBox.querySelector('.info-content');"; // Obtém o conteúdo existente
  message += "      title.textContent = 'real time update';"; // Atualiza o título
  message += "      content.textContent = 'Produto: ' + info1Text;"; // Atualiza o conteúdo com o texto correspondente
  message += "      enviarInfo('/enviarinfo1', 'info1=' + encodeURIComponent(info1));";
  message += "    } else {";
  message += "      enviarInfo('/enviarinfo1', 'info1=' + encodeURIComponent(info1));";
  message += "      infoBox = document.createElement('div');";
  message += "      infoBox.id = 'infoBox';";
  message += "      infoBox.className = 'info-box';";
  message += "      var title = document.createElement('h2');"; // Cria o elemento de título
  message += "      title.className = 'info-title';"; // Define a classe para o título
  message += "      title.textContent = 'real time update';"; // Define o texto do título
  message += "      var content = document.createElement('p');"; // Cria o elemento de conteúdo
  message += "      content.className = 'info-content';"; // Define a classe para o conteúdo
  message += "      content.textContent = 'Produto: ' + info1Text;"; // Define o texto do conteúdo com o texto correspondente
  message += "      infoBox.appendChild(title);"; // Adiciona o título ao infoBox
  message += "      infoBox.appendChild(content);"; // Adiciona o conteúdo ao infoBox
  message += "      document.getElementById('infoContainer').appendChild(infoBox);";
  message += "    }";
  message += "  }";
  message += "  document.getElementById('info1').value = '';";
  message += "}";
  message += "function enviarInfo2() {";
  message += "  var info2 = document.getElementById('info2').value;";
  message += "  var info2Text = document.getElementById('info2').options[document.getElementById('info2').selectedIndex].text;"; // Obtém o texto correspondente ao valor selecionado
  message += "  if (info2 !== '') {";
  message += "    var infoBox = document.getElementById('infoBox');";
  message += "    if (infoBox) {";
  message += "      var title = infoBox.querySelector('.info-title');"; // Obtém o título existente
  message += "      var content = infoBox.querySelector('.info-content');"; // Obtém o conteúdo existente
  message += "      title.textContent = 'real time update';"; // Atualiza o título
  message += "      content.textContent = 'Ajuste: ' + info2Text;"; // Atualiza o conteúdo com o texto correspondente
  message += "      enviarInfo('/enviarinfo2', 'info2=' + encodeURIComponent(info2));";
  message += "    } else {";
  message += "      enviarInfo('/enviarinfo2', 'info2=' + encodeURIComponent(info2));";
  message += "      infoBox = document.createElement('div');";
  message += "      infoBox.id = 'infoBox';";
  message += "      infoBox.className = 'info-box';";
  message += "      var title = document.createElement('h2');"; // Cria o elemento de título
  message += "      title.className = 'info-title';"; // Define a classe para o título
  message += "      title.textContent = 'real time update';"; // Define o texto do título
  message += "      var content = document.createElement('p');"; // Cria o elemento de conteúdo
  message += "      content.className = 'info-content';"; // Define a classe para o conteúdo
  message += "      content.textContent = 'Ajuste: ' + info2Text;"; // Define o texto do conteúdo com o texto correspondente
  message += "      infoBox.appendChild(title);"; // Adiciona o título ao infoBox
  message += "      infoBox.appendChild(content);"; // Adiciona o conteúdo ao infoBox
  message += "      document.getElementById('infoContainer').appendChild(infoBox);";
  message += "    }";
  message += "  }";
  message += "  document.getElementById('info2').value = '';";
  message += "}";
  message += "function enviarInfo3() {";
  message += "  var info3 = document.getElementById('info3').value;";
  message += "  if (info3 !== '') {";
  message += "    var infoBox = document.getElementById('infoBox');";
  message += "    if (infoBox) {";
  message += "      var title = infoBox.querySelector('.info-title');"; // Obtém o título existente
  message += "      var content = infoBox.querySelector('.info-content');"; // Obtém o conteúdo existente
  message += "      title.textContent = 'real time update';"; // Atualiza o título
  message += "      content.textContent = 'Nivel: ' + info3 + 'L';"; // Atualiza o conteúdo
  message += "      enviarInfo('/enviarinfo3', 'info3=NI' + encodeURIComponent(info3));";
  message += "    } else {";
  message += "      enviarInfo('/enviarinfo3', 'info3=NI' + encodeURIComponent(info3));";
  message += "      infoBox = document.createElement('div');";
  message += "      infoBox.id = 'infoBox';";
  message += "      infoBox.className = 'info-box';";
  message += "      var title = document.createElement('h2');"; // Cria o elemento de título
  message += "      title.className = 'info-title';"; // Define a classe para o título
  message += "      title.textContent = 'real time update';"; // Define o texto do título
  message += "      var content = document.createElement('p');"; // Cria o elemento de conteúdo
  message += "      content.className = 'info-content';"; // Define a classe para o conteúdo
  message += "      content.textContent = 'Nivel: ' + info3 + 'L';"; // Define o texto do conteúdo
  message += "      infoBox.appendChild(title);"; // Adiciona o título ao infoBox
  message += "      infoBox.appendChild(content);"; // Adiciona o conteúdo ao infoBox
  message += "      document.getElementById('infoContainer').appendChild(infoBox);";
  message += "    }";
  message += "  }";
  message += "  document.getElementById('info3').value = '';";
  message += "}";
  message += "function enviarInfo4() {";
  message += "  var info4 = document.getElementById('info4').value;";
  message += "  if (info4 !== '') {";
  message += "    var infoBox = document.getElementById('infoBox');";
  message += "    if (infoBox) {";
  message += "      var title = infoBox.querySelector('.info-title');"; // Obtém o título existente
  message += "      var content = infoBox.querySelector('.info-content');"; // Obtém o conteúdo existente
  message += "      title.textContent = 'real time update';"; // Atualiza o título
  message += "      content.textContent = 'Temp: ' + info4 + 'oC';"; // Atualiza o conteúdo
  message += "      enviarInfo('/enviarinfo4', 'info4=T' + encodeURIComponent(info4));";
  message += "    } else {";
  message += "      enviarInfo('/enviarinfo4', 'info4=T' + encodeURIComponent(info4));";
  message += "      infoBox = document.createElement('div');";
  message += "      infoBox.id = 'infoBox';";
  message += "      infoBox.className = 'info-box';";
  message += "      var title = document.createElement('h2');"; // Cria o elemento de título
  message += "      title.className = 'info-title';"; // Define a classe para o título
  message += "      title.textContent = 'real time update';"; // Define o texto do título
  message += "      var content = document.createElement('p');"; // Cria o elemento de conteúdo
  message += "      content.className = 'info-content';"; // Define a classe para o conteúdo
  message += "      content.textContent = 'Temp: ' + info4 + 'oC';"; // Define o texto do conteúdo
  message += "      infoBox.appendChild(title);"; // Adiciona o título ao infoBox
  message += "      infoBox.appendChild(content);"; // Adiciona o conteúdo ao infoBox
  message += "      document.getElementById('infoContainer').appendChild(infoBox);";
  message += "    }";
  message += "  }";
  message += "  document.getElementById('info4').value = '';";
  message += "}";
  message += "function enviarInfo5() {";
  message += "  var info5 = document.getElementById('info5').value;";
  message += "  if (info5 !== '') {";
  message += "    var infoBox = document.getElementById('infoBox');";
  message += "    if (infoBox) {";
  message += "      var title = infoBox.querySelector('.info-title');"; // Obtém o título existente
  message += "      var content = infoBox.querySelector('.info-content');"; // Obtém o conteúdo existente
  message += "      title.textContent = 'real time update';"; // Atualiza o título
  message += "      content.textContent = 'Rot: ' + info5 + 'rpm';"; // Atualiza o conteúdo
  message += "      enviarInfo('/enviarinfo5', 'info5=R' + encodeURIComponent(info5));";
  message += "    } else {";
  message += "      enviarInfo('/enviarinfo5', 'info5=R' + encodeURIComponent(info5));";
  message += "      infoBox = document.createElement('div');";
  message += "      infoBox.id = 'infoBox';";
  message += "      infoBox.className = 'info-box';";
  message += "      var title = document.createElement('h2');"; // Cria o elemento de título
  message += "      title.className = 'info-title';"; // Define a classe para o título
  message += "      title.textContent = 'real time update';"; // Define o texto do título
  message += "      var content = document.createElement('p');"; // Cria o elemento de conteúdo
  message += "      content.className = 'info-content';"; // Define a classe para o conteúdo
  message += "      content.textContent = 'Rot: ' + info5 + 'rpm';"; // Define o texto do conteúdo
  message += "      infoBox.appendChild(title);"; // Adiciona o título ao infoBox
  message += "      infoBox.appendChild(content);"; // Adiciona o conteúdo ao infoBox
  message += "      document.getElementById('infoContainer').appendChild(infoBox);";
  message += "    }";
  message += "  }";
  message += "  document.getElementById('info5').value = '';";
  message += "}";
  message += "function enviarInfo(url, data) {";
  message += "  var xhttp = new XMLHttpRequest();";
  message += "  xhttp.open('POST', url, true);";
  message += "  xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');";
  message += "  xhttp.send(data);";
  message += "}";
  message += "function inicio() {";
  message += "  var frase = 'Ligando...';"; // Definir a nova frase
  message += "  var infoBox = document.getElementById('infoBox');";
  message += "  if (infoBox) {";
  message += "    var title = infoBox.querySelector('.info-title');";
  message += "    var content = infoBox.querySelector('.info-content');";
  message += "    title.textContent = 'real time update';"; // Atualizar o título
  message += "    content.textContent = frase;"; // Atualizar o conteúdo com a nova frase
  message += "  } else {";
  message += "    infoBox = document.createElement('div');";
  message += "    infoBox.id = 'infoBox';";
  message += "    infoBox.className = 'info-box';";
  message += "    var title = document.createElement('h2');";
  message += "    title.className = 'info-title';";
  message += "    title.textContent = 'real time update';"; // Definir o título
  message += "    var content = document.createElement('p');";
  message += "    content.className = 'info-content';";
  message += "    content.textContent = frase;"; // Definir o conteúdo com a nova frase
  message += "    infoBox.appendChild(title);";
  message += "    infoBox.appendChild(content);";
  message += "    document.getElementById('infoContainer').appendChild(infoBox);";
  message += "  }";
  message += "  setTimeout(function() {";
  message += "    var novaFrase = 'Escolha o Produto';"; // Definir a nova frase após 2 segundos
  message += "    var content = infoBox.querySelector('.info-content');";
  message += "    content.textContent = novaFrase;"; // Atualizar o conteúdo com a nova frase após 2 segundos
  message += "  }, 2000);"; // Tempo em milissegundos (2 segundos = 2000 milissegundos)
  message += "  var xhttp = new XMLHttpRequest();";
  message += "  xhttp.open('GET', '/start', true);";
  message += "  xhttp.send();";
  message += "}";
  message += "function motor() {";
  message += "  var frase = 'Desligando Motor...';"; // Definir a nova frase
  message += "  var infoBox = document.getElementById('infoBox');";
  message += "  if (infoBox) {";
  message += "    var title = infoBox.querySelector('.info-title');";
  message += "    var content = infoBox.querySelector('.info-content');";
  message += "    title.textContent = 'real time update';"; // Atualizar o título
  message += "    content.textContent = frase;"; // Atualizar o conteúdo com a nova frase
  message += "  } else {";
  message += "    infoBox = document.createElement('div');";
  message += "    infoBox.id = 'infoBox';";
  message += "    infoBox.className = 'info-box';";
  message += "    var title = document.createElement('h2');";
  message += "    title.className = 'info-title';";
  message += "    title.textContent = 'real time update';"; // Definir o título
  message += "    var content = document.createElement('p');";
  message += "    content.className = 'info-content';";
  message += "    content.textContent = frase;"; // Definir o conteúdo com a nova frase
  message += "    infoBox.appendChild(title);";
  message += "    infoBox.appendChild(content);";
  message += "    document.getElementById('infoContainer').appendChild(infoBox);";
  message += "  }";
  message += "  setTimeout(function() {";
  message += "    var novaFrase = 'Produto Final...';"; // Definir a nova frase após 2 segundos
  message += "    var content = infoBox.querySelector('.info-content');";
  message += "    content.textContent = novaFrase;"; // Atualizar o conteúdo com a nova frase após 2 segundos
  message += "  }, 2000);"; // Tempo em milissegundos (2 segundos = 2000 milissegundos)
  message += "  var xhttp = new XMLHttpRequest();";
  message += "  xhttp.open('GET', '/Desligar', true);";
  message += "  xhttp.send();";
  message += "}";
  message += "function final() {";
  message += "  var frase = 'Reiniciando...';"; // Definir a nova frase
  message += "  var infoBox = document.getElementById('infoBox');";
  message += "  if (infoBox) {";
  message += "    var title = infoBox.querySelector('.info-title');";
  message += "    var content = infoBox.querySelector('.info-content');";
  message += "    title.textContent = 'real time update';"; // Atualizar o título
  message += "    content.textContent = frase;"; // Atualizar o conteúdo com a nova frase
  message += "  } else {";
  message += "    infoBox = document.createElement('div');";
  message += "    infoBox.id = 'infoBox';";
  message += "    infoBox.className = 'info-box';";
  message += "    var title = document.createElement('h2');";
  message += "    title.className = 'info-title';";
  message += "    title.textContent = 'real time update';"; // Definir o título
  message += "    var content = document.createElement('p');";
  message += "    content.className = 'info-content';";
  message += "    content.textContent = frase;"; // Definir o conteúdo com a nova frase
  message += "    infoBox.appendChild(title);";
  message += "    infoBox.appendChild(content);";
  message += "    document.getElementById('infoContainer').appendChild(infoBox);";
  message += "  }";
  message += "  setTimeout(function() {";
  message += "    infoBox.parentNode.removeChild(infoBox);"; // Remove o elemento infoBox do DOM
  message += "  }, 3000);";
  message += "  var xhttp = new XMLHttpRequest();";
  message += "  xhttp.open('GET', '/FIM', true);";
  message += "  xhttp.send();";
  message += "}";
  message += "</script>";
  message += "</body></html>";
  server.send(200, "text/html", message);
}
void handleinicio() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(28, 10);
  display.setTextSize(1);
  display.println("Escolha");
  display.setCursor(40, 20);
  display.println("dos");
  display.setCursor(28, 30);
  display.println("produtos");
  display.display();
  espSerial.println("S");
  server.send(200, "text/plain", "Dados enviados");
}
void handlemotor() {
  display.stopscroll();
  espSerial.println("DM");
  server.send(200, "text/plain", "Dados enviados");
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(28, 10);
  display.setTextSize(1);
  display.println("Desligando");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(28, 10);
  display.setTextSize(1);
  display.println("Produto");
  display.setCursor(28, 20);
  display.println("Final");
  display.display();
}
void handlefinal() {
  espSerial.println("PF");
  server.send(200, "text/plain", "Dados enviados");
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Reiniciando");
  display.println("................");
  display.display();
  display.startscrollright(0x01, 0x01);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(24, 23);
  display.setTextSize(2);
  display.println("Spray");
  display.println("");
  display.setCursor(24, 40);
  display.println("Drayer");
  display.display();
}
void handleSendInfo1() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(28, 10);
  display.setTextSize(1);
  display.println("Etapa do ajuste");
  display.display();
  info1 = server.arg("info1");
  espSerial.println(info1);
  server.send(200, "text/plain", "Informação 1 enviada para o Arduino!");
}

void handleSendInfo2() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(28, 10);
  display.setTextSize(1);
  display.println("Escolha");
  display.setCursor(40, 20);
  display.println("do");
  display.setCursor(28, 30);
  display.println("Nivel");
  display.display();
  info2 = server.arg("info2");
  espSerial.println(info2);
  server.send(200, "text/plain", "Informação 2 enviada para o Arduino!");
  if (info2 == "Y") {
    estado = 1;
  }
  else
  {
    estado = 0;
  }
}
void handleSendInfo3() {
  if (estado == 1)
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Em processo");
    display.println("................");
    display.setTextSize(1);
    display.display();
    display.startscrollright(0x01, 0x01);
    delay(1000);
    display.stopscroll();
  }
  else
  {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(28, 10);
    display.setTextSize(1);
    display.println("Escolha");
    display.setCursor(40, 20);
    display.println("da");
    display.setCursor(28, 30);
    display.println("Temperatura");
    display.display();

  }
  info3 = server.arg("info3");
  espSerial.println(info3);
  server.send(200, "text/plain", "Informação 3 enviada para o Arduino!");
}

void handleSendInfo4() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(28, 10);
  display.setTextSize(1);
  display.println("Escolha");
  display.setCursor(40, 20);
  display.println("da");
  display.setCursor(28, 30);
  display.println("Rotacao");
  display.display();
  info4 = server.arg("info4");
  espSerial.println(info4);
  server.send(200, "text/plain", "Informação 4 enviada para o Arduino!");
}
void handleSendInfo5() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Em processo");
  display.println("................");
  display.setTextSize(1);
  display.display();
  display.startscrollright(0x01, 0x01);
  delay(1000);
  display.stopscroll();
  info5 = server.arg("info5");
  espSerial.println(info5);
  server.send(200, "text/plain", "Informação 5 enviada para o Arduino!");
}

void setup() {

  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();
  espSerial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi com sucesso!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  display.setTextColor(WHITE);
  display.setCursor(24, 23);
  display.setTextSize(2);
  display.println("Spray");
  display.println("");
  display.setCursor(24, 40);
  display.println("Drayer");
  display.display();
  server.on("/", pagina);
  server.on("/start", handleinicio);
  server.on("/enviarinfo1", handleSendInfo1);
  server.on("/enviarinfo2", handleSendInfo2);
  server.on("/enviarinfo3", handleSendInfo3);
  server.on("/enviarinfo4", handleSendInfo4);
  server.on("/enviarinfo5", handleSendInfo5);
  server.on("/Desligar", handlemotor);
  server.on("/FIM", handlefinal);
  server.begin();
}

void loop() {
  server.handleClient();

}
