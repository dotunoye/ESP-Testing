#include <Arduino.h>

float batteryVoltages[] = {12.4, 11.3, 12.9, 10.5, 11.9, 12.0};
bool needReplacement [6];
int batteryCount = 6;
String status[6];
int lowCount = 0;


void setup() {
    Serial.begin(115200);
    float lowestVolt = batteryVoltages[0];
    int batteryIndex = 0;

    for (int i = 0; i < batteryCount; i++)
    {
        if (batteryVoltages[i] < 11.5)
        {
            status[i] = "LOW";
            lowCount ++;
        }else
        {
            status[i] = "OK";
        }
        Serial.print("Battery ");
        Serial.print(i);
        Serial.print(" : ");
        Serial.println(status[i]); 
        
    }
    Serial.print("Total LOW Batteries: ");
    Serial.println(lowCount);

    for (int i = 1; i < batteryCount; i++)
    {
        if (batteryVoltages[i] < lowestVolt)
        {
            lowestVolt = batteryVoltages[i];
            batteryIndex = i;
        }
    }
        Serial.print("Lowest Voltage: ");
        Serial.println(lowestVolt);
        Serial.print("Battery Index: ");
        Serial.println(batteryIndex); 
    
        for (int i = 0; i < batteryCount; i++)
        {
            needReplacement[i] = batteryVoltages[i] < 11.5;

           if (needReplacement[i])
           {                  
            Serial.print("Battery ");
            Serial.print(i);
            Serial.print(" : ");
            Serial.println("REPLACE");
        }else
        {
            Serial.print("Battery ");
            Serial.print(i);
            Serial.print(" : ");
            Serial.println("KEEP");
        }
    
    }
}
void loop() {

}