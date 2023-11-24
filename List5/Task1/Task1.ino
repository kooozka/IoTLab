#include <LiquidCrystal_I2C.h>

#define LED_RED 6
#define LED_BLUE 3

#define ENCODER1 A2
#define ENCODER2 A3

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLCD() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void setup()
{
    initLCD();
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(ENCODER1, INPUT_PULLUP);
    pinMode(ENCODER2, INPUT_PULLUP);
}

void loop()
{
    digitalWrite(LED_RED, digitalRead(ENCODER1));
    digitalWrite(LED_BLUE, digitalRead(ENCODER2));
}
