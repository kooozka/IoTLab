#include <LiquidCrystal_I2C.h>

#define RED_BUTTON 2
#define GREEN_BUTTON 4

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte smile[8] = {
  B10101,
  B00000,
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
};

void initButtons() {
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

#define DEBOUNCE_PERIOD 10UL

bool isGreenButtonPressed() {
static int debounced_button_state = HIGH;
static int previous_reading = HIGH;
static unsigned long last_change_time = 0UL;
bool isPressed = false;

int current_reading = digitalRead(GREEN_BUTTON);

if (previous_reading != current_reading) {
last_change_time = millis();
}

if (millis() - last_change_time > DEBOUNCE_PERIOD) {
  if (current_reading != debounced_button_state)
  {
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
static int debounced_button_state = HIGH;
static int previous_reading = HIGH;
static unsigned long last_change_time = 0UL;
bool isPressed = false;

int current_reading = digitalRead(RED_BUTTON);

if (previous_reading != current_reading) {
last_change_time = millis();
}

if (millis() - last_change_time > DEBOUNCE_PERIOD) {
  if (current_reading != debounced_button_state)
  {
    if (debounced_button_state == HIGH && current_reading == LOW) {
      isPressed = true;
    }
  debounced_button_state = current_reading;
  }
}

previous_reading = current_reading;

return isPressed;
}


void setup(){
  initButtons();
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, smile);

  lcd.setCursor(15,0);
  lcd.write(byte(0));
}

bool stopped = false;
bool reset = false;
unsigned long lastStopTime = 0UL;
unsigned long timePassed = 0UL; 

void loop(){
  if (!stopped && isGreenButtonPressed()) {
    lastStopTime = millis();
    stopped = true;
  }
  if (stopped && isGreenButtonPressed()) {
    if (!reset){
      timePassed += millis() - lastStopTime;
    } else {
      timePassed = millis();
      reset = false;
    }
      stopped = false;
  }
  if (!stopped) {
    lcd.setCursor(0, 0);
    lcd.print(millis()/1000 - timePassed/1000);
    lcd.print("s.");
  }
  if (isRedButtonPressed()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    timePassed = millis();
    lcd.print(millis()/1000 - timePassed/1000);
    lcd.print("s.");
    stopped = true;
    reset = true;
  }
}
