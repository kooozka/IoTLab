#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

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

void setup() {
  initLCD();
  initRGB();
  Serial.begin(9600);

  while (!Serial)
  {
  }

}

int values[3] = {-1,-1,-1};
int lastSeparator = 0;
int index = 0;
void loop()
{
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');
    for (int i = 0; i < command.length(); i++) {
      if (command.charAt(i) == ':') {
        int level = 0;
        String levelString = command.substring(lastSeparator, i);
        levelString.trim();
        levelString.toUpperCase();
        if (levelString == "OFF"){
          level = 0;
        } else {
          level = levelString.toInt();
          if (level > 255) {
            level = 255;
          }
          else if(level <=0) {
            level = -1;
          }
        }
        values[index] = level;
        lastSeparator = i + 1;
        index++;
      }
    }
    values[2] = command.substring(lastSeparator, command.length()).toInt();
    lastSeparator = 0;
    index = 0;
    if (values[0] == -1 || values[1] == -1 || values[2] == -1) {
        Serial.println(String("Unknown command: '") + command + "'. {redValue}:{greenValue}:{blueValue}.");
    } else {
      analogWrite(LED_RED, values[0]);
      analogWrite(LED_GREEN, values[1]);
      analogWrite(LED_BLUE, values[2]);
      for (int i = 0; i < 3; i++) {
        values[i] = -1;
      }
    }
  }
}
