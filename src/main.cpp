#include <Arduino.h>

int sensorValues[] = {420, 650, 710, 600};
int thresholds[]   = {300, 700, 760, 550};
bool alarms[4];
String state;

void setup() {
    Serial.begin(115200);
    
    for (int i = 0; i < 4; i++)
    {
        if (sensorValues[i] > thresholds[i])
        {
            alarms[i] =  true;
        }else
        {
            alarms[i] = false;
        }
        if (alarms[i] == true)
        {
            state = "ALARM";
        }else
        {
            state = "SAFE";
        }
        Serial.print("Sensor" );
        Serial.print(i);
        Serial.print(": ");
        Serial.println(state);
    }  
}
void loop() {
}