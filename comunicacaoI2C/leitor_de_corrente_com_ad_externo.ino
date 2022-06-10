#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <LiquidCrystal.h>

/*config LCD */
#define LCD_RS 8                                  // definição dos pinos do LCD
#define LCD_E 9
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/*config ADS1115*/
#define ADC_16BIT_MAX 65536                      //ADC_COUNTS? possibilidades/niveis de acordo com a resoluçaõ                             // define a tensão RMS da rede(valor lido com multimetro)
Adafruit_ADS1115 ads;                            //cria instancia do conversor analogico digital ADC

const float fator = 100;                         //100A/50mV
const float multiplicador = 0.125F;                    

void setup() {
 Serial.begin(9600);
 lcd.begin(16, 2);                               // configura LCD 16 colunas x 2 linhas
 lcd.clear();                                    // limpa tela do LCD
  
 ads.setGain (GAIN_ONE);                         // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
 ads.begin();                        
  
 lcd.setCursor(0,0);                              // seleciona coluna 0, linha 0
 lcd.print("Irms(A)=");                           // mostra texto
} 
 
void loop() { 
  float Irms = getI();
   
  lcd.setCursor(9,0);                                    // seleciona coluna 9, linha 0
  lcd.print(Irms);                                       // mostra valor da corrente  
  Serial.print("Differential: "); Serial.println(Irms);
  delay(1000);                                           // atraso de 1 segundo
}

float getI(){
  double tensao;
  double corrente;
  double sum = 0.0;
  long tempo = millis();
  int counter = 0;
 
  while((millis()-tempo) <1000){
    tensao = (ads.readADC_Differential_0_1())*multiplicador;
    corrente = tensao*fator;
    corrente /=1000.0;

    sum+= sq(corrente);
    counter = counter+1;
  }
  corrente = (sqrt(sum/counter));
  return corrente;  
}
