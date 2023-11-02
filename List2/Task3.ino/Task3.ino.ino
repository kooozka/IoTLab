#define LED_RED 6
#define LED_GREEN 5 
#define LED_BLUE 3



void initLeds() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, HIGH);

  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);

  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, LOW);
}

void changeColor(int color, int prev_color) {
  for (int i = 0; i <= 255; i++) {
    analogWrite(color, i);
    analogWrite(prev_color, 255 - i);
    delay(10);
  }
}

void setup() {
  initLeds();
  analogWrite(LED_RED, 255);
}

void loop() {
  changeColor(LED_RED, LED_BLUE);
  delay(1000);
  changeColor(LED_GREEN, LED_RED);
  delay(1000);
  changeColor(LED_BLUE, LED_GREEN);
  delay(1000);
}
