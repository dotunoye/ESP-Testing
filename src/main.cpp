#include <Arduino.h>

int ledPins[5] = {4, 16, 5, 18, 19};
unsigned long previousMillis = 0;
unsigned long interval = 300;
int currentLed = 0;

void setup() {
    Serial.begin(115200);

    for (int i = 0; i < 5; i++)
    {
        pinMode(ledPins[i], OUTPUT);
    }
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
        {
            previousMillis = currentMillis;
            for (int i = 0; i < 5; i++)
            {
                digitalWrite(ledPins[i], LOW);
            }
            digitalWrite(ledPins[currentLed], HIGH);
           currentLed = (currentLed + 1) % 5;           
        }
}