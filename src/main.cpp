#include <Arduino.h>

int distances[] = {15, 120, 35, 8, 200, 18, 75, 100};
int totalSpaces = 8;
bool occupied[8];
int freeSpaces;
float occupiedSpaces = 0;
float closestDistance = distances[0];
int carNum = distances[0];

void setup() {
    Serial.begin(115200);
    
    for (int i = 0; i < totalSpaces; i++)
    {
        if (distances[i] <= 20)
        {
            occupied[i] = true;
            Serial.print("Space ");
            Serial.print(i);
            Serial.print(" : ");
            Serial.println("true");
            occupiedSpaces++;
        } else{
            occupied[i] = false;
            Serial.print("Space ");
            Serial.print(i);
            Serial.print(" : ");
            Serial.println("false");
            freeSpaces++;
        }
    }
            Serial.print("Occupied Space ");
            Serial.print(" : ");
            Serial.println(occupiedSpaces);
            Serial.print("Free Space ");
            Serial.print(" : ");
            Serial.println(freeSpaces);
            

    for (int i = 1; i < totalSpaces; i++)
    {
        if (distances[i] < closestDistance)
        {
            closestDistance = distances[i];
            carNum = i;
        }
        
    }
        Serial.print("Closest Car ");
        Serial.print(" : ");
        Serial.println(closestDistance);
    
        Serial.print("Parking Space ");
        Serial.print(" : ");
        Serial.println(carNum);
    
        int percentage = (occupiedSpaces / totalSpaces) * 100;
    
    Serial.print("Parking Occupancy ");
    Serial.print(" : ");
    Serial.println(percentage);
    
    Serial.print("Free Spaces ");
    Serial.print(" : ");
    Serial.println(freeSpaces);

    if (freeSpaces == 0)
    {
        Serial.print("Parking Lot ");
        Serial.print(" : ");
        Serial.println("FULL");
    } else if (freeSpaces >= 1 && freeSpaces <= 5)
    {
        Serial.print("Parking Lot ");
        Serial.print(" : ");
        Serial.println("HALF FULL");
    }else if (freeSpaces >= 6 && freeSpaces <= 8)
    {
        Serial.print("Parking Lot ");
        Serial.print(" : ");
        Serial.println("OCCUPIED");
    }
    
    
}
void loop() {

}