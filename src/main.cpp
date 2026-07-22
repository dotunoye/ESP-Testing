#include <Arduino.h>

struct FireSensor
{
    int gpio;
    int threshold;
    bool status;
    int uniqueID;
    String location;
};

FireSensor sensors[3];

int fireCount = 0;
void setup() {
    Serial.begin(115200);
    
    sensors[0].gpio = 1;
    sensors[0].location = "Top Right corner";
    sensors[0].status = false;
    sensors[0].threshold = 100;
    sensors[0].uniqueID = 55;

    sensors[1].gpio = 2;
    sensors[1].location = "Top left corner";
    sensors[1].status = true;
    sensors[1].threshold = 50;
    sensors[1].uniqueID = 205;

    sensors[2].gpio = 3;
    sensors[2].location = "Bottom Right corner";
    sensors[2].status = false;
    sensors[2].threshold = 90;
    sensors[2].uniqueID = 35;
    
    for (int i = 0; i < 3; i++)
    {
        
        sensors[i];
        Serial.print("===================SENSOR ");
        Serial.print(i);
        Serial.println("===================");
        Serial.print("GPIO ");
        Serial.println(sensors[i].gpio);
        Serial.print("Threshold ");
        Serial.println(sensors[i].threshold);
        Serial.print("Status ");
        if (sensors[i].status)
        {
            Serial.println("FIRE");
            fireCount++;
        }else
        {
            Serial.println("SAFE");
        }
        Serial.print("ID ");
        Serial.println(sensors[i].uniqueID);
        Serial.print("Location ");
        Serial.println(sensors[i].location);

    }

        Serial.print("Total Active Fire Sensor ");
        Serial.print(": ");
        Serial.println(fireCount);
    

}
void loop() {
}