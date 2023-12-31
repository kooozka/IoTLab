#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define RED_BUTTON 2
#define GREEN_BUTTON 4

void initLCD() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void initButtons() {
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
}


void setup() {
  initLCD();
  initButtons();
  Serial.begin(9600);
  while (!Serial) { /* just wait */
  }
}

void loop() {
  String str = String(digitalRead(RED_BUTTON)) + " " + String(digitalRead(GREEN_BUTTON));
  Serial.println(str);
}
