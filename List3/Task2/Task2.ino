#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3
#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define INTERVAL_RED 900UL
#define INTERVAL_GREEN 1000UL
#define INTERVAL_BLUE 1100UL

int led[] = {LED_RED, LED_GREEN, LED_BLUE};
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

void changeLedState(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}

void setup(){
  initRGB();
  initButtons();
}

void changeRed() {
  static unsigned long lastRedChange = 0UL;
  if (millis() - lastRedChange >= INTERVAL_RED) {
    changeLedState(LED_RED);
    lastRedChange = millis();
  }
}

void changeGreen() {
  static unsigned long lastGreenChange = 0UL;
  if (millis() - lastGreenChange >= INTERVAL_GREEN) {
    changeLedState(LED_GREEN);
    lastGreenChange = millis();
  }
}

void changeBlue() {
  static unsigned long lastBlueChange = 0UL;
  if (millis() - lastBlueChange >= INTERVAL_BLUE) {
    changeLedState(LED_BLUE);
    lastBlueChange = millis();
  }
}

void loop(){
  changeRed();
  changeGreen();
  changeBlue();
}
