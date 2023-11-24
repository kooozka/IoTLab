#include <util/atomic.h>
#include <LiquidCrystal_I2C.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define ENCODER1 A2
#define ENCODER2 A3

#define DEBOUNCING_PERIOD 100
#define DEBOUNCE_PERIOD 10UL

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLCD() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void printResults(int val) 
{
  char buffer[40];
  sprintf(buffer, "Intensity: %3d", val);
  lcd.setCursor(2, 0);
  lcd.print(buffer);
}

void menu(int val) {
  if (val == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Red diod");
    lcd.setCursor(1, 1);
    lcd.print("Green diod");
  } else if (val == 1) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Red diod");
    lcd.setCursor(0, 1);
    lcd.print(">Green diod");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(">Blue diod");
  }
}

void setup() {
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);

  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);

  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, LOW);

  pinMode(ENCODER1, INPUT_PULLUP);
  pinMode(ENCODER2, INPUT_PULLUP);

  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);

  initLCD();
  menu(0);

  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT10);
}

bool isButtonPressed(int buttonPin) 
{
  static int debounced_button_state = HIGH;
  static int previous_reading = HIGH;
  static unsigned long last_change_time = 0UL;
  bool isPressed = false;

  int current_reading = digitalRead(buttonPin);

  if (previous_reading != current_reading) 
  {
    last_change_time = millis();
  }

  if (millis() - last_change_time > DEBOUNCE_PERIOD) {
    if (current_reading != debounced_button_state) {
      if (debounced_button_state == HIGH && current_reading == LOW) {
        isPressed = true;
      }
      debounced_button_state = current_reading;
    }
  }

  previous_reading = current_reading;

  return isPressed;
}

bool isRedButtonPressed() {
  return isButtonPressed(RED_BUTTON);
}

bool isGreenButtonPressed() {
  return isButtonPressed(GREEN_BUTTON);
}

void changeIntensity(int diod, int val) {
  printResults(val);
  analogWrite(diod, val);
}

int diodByOption(int option)
{
  int diodPins[] = {LED_RED, LED_GREEN, LED_BLUE};
  return diodPins[option];
}

int redValue = 0;
int greenValue = 0;
int blueValue = 0;
int colors[] = {redValue, greenValue, blueValue};

int colorByOption(int option) {
  return colors[option];
}

void increaseColorValue(int option) {
  colors[option] += 15;
}

void decreaseColorValue(int option) {
  colors[option] -= 15;
}


volatile int encoder1 = HIGH;
volatile int encoder2 = HIGH;
volatile unsigned long encoderTimestamp = 0UL;
ISR(PCINT1_vect) {
  encoder1 = digitalRead(ENCODER1);
  encoder2 = digitalRead(ENCODER2);
  encoderTimestamp = millis();
}

/*volatile*/ bool menuMode = true;
int chosen_option;
int encoderValue = 0;
int lastEn1 = LOW;
unsigned long lastChangeTimestamp = 0UL;

void loop() {
  int en1, en2;
  unsigned long timestamp;

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    en1 = encoder1;
    en2 = encoder2;
    timestamp = encoderTimestamp;
  }

  if (menuMode) 
  {
    if (en1 == LOW && timestamp > lastChangeTimestamp + DEBOUNCING_PERIOD) {
      if (en2 == HIGH) {
        if (encoderValue < 2)
          encoderValue += 1;
      } else {
        if (encoderValue > 0)
          encoderValue -= 1;
      }
      lastChangeTimestamp = timestamp;

      menu(encoderValue);
    }
    //lastEn1 = en1;
    if (isGreenButtonPressed()) {
      menuMode = false;
      chosen_option = encoderValue;
      lcd.clear();
      encoderValue = 0;
      changeIntensity(diodByOption(chosen_option), colorByOption(chosen_option));
    }
  } 
  if (!menuMode)
  {
    if (en1 == LOW && timestamp > lastChangeTimestamp + DEBOUNCING_PERIOD) 
    {
      if (en2 == HIGH) 
      {
        if (colorByOption(chosen_option) < 255)
          increaseColorValue(chosen_option);
      } 
      else 
      {
        if (colorByOption(chosen_option) > 0)
          decreaseColorValue(chosen_option);
      }
      lastChangeTimestamp = timestamp;

      changeIntensity(diodByOption(chosen_option), colorByOption(chosen_option));
    }
    //lastEn1 = en1;
    if (isRedButtonPressed()) {
      menuMode = true;
      lcd.clear();
      encoderValue = 0;
      menu(encoderValue); 
    }
  }
}
