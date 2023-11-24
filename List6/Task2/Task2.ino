#include "RGBLedControl.h"
#include <LiquidCrystal_I2C.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

LiquidCrystal_I2C lcd(0x27, 16, 2);

RGBLedControl rgbLed(LED_RED, LED_GREEN, LED_BLUE);

void initLCD() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void setup() {
  initLCD();
}

void loop() {
  rgbLed.setColor("RED");
  delay(1000);

  rgbLed.setColor("GREEN");
  delay(1000);

  rgbLed.setColor("BLUE");
  delay(1000);

  rgbLed.setColor(255, 255, 0);
  delay(1000);

  rgbLed.setColor("cyan");
  delay(1000);

  rgbLed.setColor("UNKNOWN_COLOR");
  delay(1000);
}
