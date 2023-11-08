#define POTENTIOMETER A0

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
}

void loop()
{
    int sensorValue = analogRead(POTENTIOMETER);
    Serial.println(sensorValue);

    delay(100);
}
