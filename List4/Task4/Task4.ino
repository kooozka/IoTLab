#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define POTENTIOMETER A0

void initLCD() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void setup() {
  initLCD();
  Serial.begin(9600);
  while (!Serial){
  }
}

void loop()
{
    int sensorValue = analogRead(POTENTIOMETER);
    Serial.println(sensorValue);
}
