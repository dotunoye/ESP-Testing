#include <Arduino.h>

int sensorValues[] = {420, 310, 860, 790};
int sensorCount = 4;

void setup() {
    Serial.begin(115200);
    int   highest = sensorValues[0];
    int   sensorIndex = 0;

    for (int i = 1; i < sensorCount; i++)
    {
        if (sensorValues[i] > highest)
        {
            highest = sensorValues[i];
            sensorIndex = i;
        }
    }
        Serial.print("The higest value and index is ");
        Serial.print(highest);
        Serial.print(" & ");
        Serial.println(sensorIndex);
}
void loop() {
}