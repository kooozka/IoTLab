#include "RGBLedControl.h"

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

RGBLedControl rgbLed(LED_RED, LED_GREEN, LED_BLUE);

void setup() {
}

void loop() {
  // Ustawianie koloru na podstawie nazwy
  rgbLed.setColor("RED");
  delay(1000);

  rgbLed.setColor("GREEN");
  delay(1000);

  rgbLed.setColor("BLUE");
  delay(1000);

  // Ustawianie koloru na podstawie komponentów RGB
  rgbLed.setColor(255, 255, 0);  // Yellow
  delay(1000);

  rgbLed.setColor("cyan");
  delay(1000);

  // Domyślny kolor w przypadku nieznanego nazwanego koloru
  rgbLed.setColor("UNKNOWN_COLOR");
  delay(1000);
}
