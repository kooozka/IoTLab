#define LED_GREEN 5

#define RED_BUTTON 2
#define GREEN_BUTTON 4

int value = 128;

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  analogWrite(LED_GREEN, value);
}

void loop() {
  if (digitalRead(GREEN_BUTTON) == LOW) {
    if (value < 255){
      value += 1;
    }
  }
  if (digitalRead(RED_BUTTON) == LOW) {
    if (value > 0) {
      value -= 1;
    }
  }
  analogWrite(LED_GREEN, value);
  delay(10);
}
