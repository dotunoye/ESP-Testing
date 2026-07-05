#include<Arduino.h>
#include <ESP32Servo.h>

int xAxis = 32;
int yAxis = 35;
int SW = 33;
int servoPin = 4;

Servo myServo;

void setup (){
    Serial.begin(115200);
    pinMode(SW, INPUT_PULLUP);

    myServo.attach(servoPin);
    digitalWrite(2, HIGH);
}

void loop(){

    int xValue = analogRead(xAxis);
    int yValue = analogRead(yAxis);

    int buttonState = digitalRead(SW);

    int mapX = map(xValue, 0, 4095, 0, 180);
    int mapY = map(yValue, 0, 4095, 180, 0);

     Serial.print("X: "); Serial.print(mapX);
    Serial.print(" | Y: "); Serial.print(mapY);
    Serial.print(" | Button: "); Serial.println(buttonState);
    myServo.write(mapX);
    delay(50);
    if (buttonState == LOW)
    {
        digitalWrite(2, HIGH);
    }else
    {
        digitalWrite(2, LOW);
    }
    
    
}