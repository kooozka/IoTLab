#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLCD() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void initRGB() 
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
}

OneWire oneWire(A1);
DallasTemperature tempSensors(&oneWire);

float minTemperature = 125.0;
float maxTemperature = -55.0;

void checkTemperatureOut(float temperatureOut) {
  if (temperatureOut > maxTemperature) {
    maxTemperature = temperatureOut;
  }
  else if (temperatureOut < minTemperature) {
    minTemperature = temperatureOut;
  }
  Serial.println("Max temp: " + String(maxTemperature) + " | Min temp: " + String(minTemperature));
}

void updateTemperatures() {
  tempSensors.requestTemperatures();
  float tempIn = tempSensors.getTempCByIndex(1);
  float tempOut = tempSensors.getTempCByIndex(0);

  checkTemperatureOut(tempOut);

  char buffer[40];
  sprintf(buffer, "Temp  IN%8s", String(tempIn, 4).c_str());
  lcd.setCursor(0, 0);
  lcd.print(buffer);
  sprintf(buffer, "Temp OUT%8s", String(tempOut, 4).c_str());
  lcd.setCursor(0, 1);
  lcd.print(buffer);

  changeColor(tempOut);
}

void changeColor(float temperatureOut) {
  const float comfortZoneMin = 19.0;
  const float comfortZoneMax = 25.0;

  if (temperatureOut < comfortZoneMin) {
    analogWrite(LED_BLUE, 255);
  }
  else if (temperatureOut > comfortZoneMax) {
    analogWrite(LED_RED, 255);
  }
  else {
    analogWrite(LED_GREEN, 255);
  }
}



void setup()
{
    tempSensors.begin();
    initLCD();
    initRGB();
    Serial.begin(9600);
    while (!Serial){}
}

void loop()
{
    updateTemperatures();
    delay(3000);
}
