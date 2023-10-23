#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3
#define DELAY 300

void changeColor(int red, int green, int blue) {
  analogWrite(LED_RED, red);
  analogWrite(LED_GREEN, green);
  analogWrite(LED_BLUE, blue);
  delay(DELAY);
}

void setup() {
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);

  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);

  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, LOW);
}

void loop() {
  changeColor(255, 0, 0);
  changeColor(255,255,0);
  changeColor(0, 255, 0);
  changeColor(0, 255, 255);
  changeColor(0, 0, 255);
  changeColor(255, 0, 255);
}
