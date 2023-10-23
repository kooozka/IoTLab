#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

int state = LOW;

void initRGB() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);

  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);

  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, LOW);
}

void initButtons() {
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void changeColor() {
  if (digitalRead(LED_RED) == HIGH) {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
  }
  else if (digitalRead(LED_GREEN) == HIGH) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, HIGH);
  }
  else if (digitalRead(LED_BLUE) == HIGH) {
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, HIGH);
  }
  delay(100);
}

void setup() {
  initRGB();
  initButtons();
}

void loop() {
  if (state == HIGH){
    if (digitalRead(GREEN_BUTTON) == LOW) {
      changeColor();
    }
    if (digitalRead(RED_BUTTON) == LOW) {
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      state = LOW;
    }
  }
  else {
    if (digitalRead(RED_BUTTON) == LOW) {
      digitalWrite(LED_RED, HIGH);
      state = HIGH;
    }
  }
  delay(100);
}
