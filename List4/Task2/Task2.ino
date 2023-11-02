#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3


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
  initRGB();
  Serial.begin(9600);

  while (!Serial)
  {
  }

}

void loop()
{
  static int level = 0;

  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();

    level = command.substring(1).toInt();
    if (level > 255) {
      level = 255;
    }
    else if(level < 0) {
      level = 0;
    }

    if (command.startsWith("r")) 
    {
      analogWrite(LED_RED, level);
    }
    else if (command.startsWith("g"))
    {
      analogWrite(LED_GREEN, level);
    }
    else if (command.startsWith("b"))
    {
      analogWrite(LED_BLUE, level);
    }
    else
      Serial.println(String("Unknown comman: '") + command + "'");
  }
}
