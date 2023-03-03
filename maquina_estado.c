// Definindo os pinos de entrada e saída
#define SENSOR_PIN  A0
#define BUTTON_PIN  2
#define LED_PIN     3
#define RELAY_PIN   4

// Definindo os estados possíveis da máquina de estados
typedef enum {
  STATE_IDLE,
  STATE_WAITING_BUTTON_PRESS,
  STATE_WAITING_SENSOR_TRIGGER,
  STATE_LIGHT_ON,
  STATE_LIGHT_OFF
} State;

// Inicializando a variável que irá armazenar o estado atual
State currentState = STATE_IDLE;

// Inicializando as variáveis que irão armazenar os valores lidos das entradas
int sensorValue = 0;
bool buttonPressed = false;

// Função para ler o valor do sensor analógico
int readSensorValue() {
  return analogRead(SENSOR_PIN);
}

// Função para ler o estado do botão
bool readButtonState() {
  return digitalRead(BUTTON_PIN) == HIGH;
}

// Função para ligar ou desligar o relé
void setRelay(bool state) {
  digitalWrite(RELAY_PIN, state ? HIGH : LOW);
}

// Função para ligar ou desligar o LED
void setLed(bool state) {
  digitalWrite(LED_PIN, state ? HIGH : LOW);
}

// Função que atualiza o estado da máquina de estados com base nas entradas
void updateState() {
  switch (currentState) {
    case STATE_IDLE:
      if (buttonPressed) {
        currentState = STATE_WAITING_SENSOR_TRIGGER;
      }
      break;
    case STATE_WAITING_BUTTON_PRESS:
      if (!buttonPressed) {
        currentState = STATE_IDLE;
      }
      break;
    case STATE_WAITING_SENSOR_TRIGGER:
      sensorValue = readSensorValue();
      if (sensorValue > 500) {
        currentState = STATE_LIGHT_ON;
      }
      break;
    case STATE_LIGHT_ON:
      setRelay(true);
      setLed(true);
      if (!buttonPressed) {
        currentState = STATE_LIGHT_OFF;
      }
      break;
    case STATE_LIGHT_OFF:
      setRelay(false);
      setLed(false);
      if (buttonPressed) {
        currentState = STATE_WAITING_BUTTON_PRESS;
      }
      break;
  }
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  // Atualiza o estado do botão
  buttonPressed = readButtonState();

  // Atualiza o estado da máquina de estados
  updateState();

  // Aguarda um curto período para evitar processamento excessivo
  delay(100);
}
