#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3
#define RED_BUTTON 2
#define GREEN_BUTTON 4
int led[] = {LED_RED, LED_GREEN, LED_BLUE};
void initRGB() {
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, LOW);

pinMode(LED_RED, OUTPUT);
digitalWrite(LED_RED, HIGH);

pinMode(LED_GREEN, OUTPUT);
digitalWrite(LED_GREEN, LOW);

pinMode(LED_BLUE, OUTPUT);
digitalWrite(LED_BLUE, LOW);
}

void initButtons() {
pinMode(RED_BUTTON, INPUT_PULLUP);
pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

#define DEBOUNCE_PERIOD 10UL

bool isGreenButtonReleased() {
  static int debounced_button_state = LOW;
  static int previous_reading = LOW;
  static unsigned long last_change_time = 0UL;
  bool isReleased = false;

  int current_reading = digitalRead(GREEN_BUTTON);

  if (previous_reading != current_reading) {
    last_change_time = millis();
  }

  if (millis() - last_change_time > DEBOUNCE_PERIOD) {
    if (current_reading != debounced_button_state)
    {
      if (debounced_button_state == LOW && current_reading == HIGH) {
        isReleased = true;
      }
    debounced_button_state = current_reading;
    }
  }

  previous_reading = current_reading;

  return isReleased;
}

bool isRedButtonReleased() {
  static int debounced_button_state = LOW;
  static int previous_reading = LOW;
  static unsigned long last_change_time = 0UL;
  bool isReleased = false;

  int current_reading = digitalRead(RED_BUTTON);

  if (previous_reading != current_reading) {
    last_change_time = millis();
  }

  if (millis() - last_change_time > DEBOUNCE_PERIOD) {
    if (current_reading != debounced_button_state)
    {
      if (debounced_button_state == LOW && current_reading == HIGH) {
        isReleased = true;
      }
    debounced_button_state = current_reading;
    }
  }

  previous_reading = current_reading;

  return isReleased;
}


void setup() {
  initRGB();
  initButtons();
}

int led_index = 2;

void loop() {
  if (isGreenButtonReleased() || isRedButtonReleased()) {
    digitalWrite(led[led_index], LOW);
    led_index = ++led_index % 3;
    digitalWrite(led[led_index], HIGH);
  }
}
