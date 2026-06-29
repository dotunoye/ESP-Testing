#include<Arduino.h>

int ledPin = 4;
int buttonPin = 16;

void setup (){
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
}

enum State {
    ON,
    OFF
};

State currentState = ON;

void updateState (){
    switch (currentState)
    {
    case ON:
       if (digitalRead(buttonPin) == LOW)
       {
        currentState = OFF;
        delay(250);
       }
        break;
    
    case OFF:
        if (digitalRead(buttonPin) == LOW)
        {
            currentState = ON;
            delay(250);
        }
        break;
    }
}
    
void runState (){
    switch (currentState)
    {
    case ON:
        digitalWrite(ledPin, HIGH);
        break;
    
    case OFF:
    digitalWrite(ledPin, LOW);
        break;
    }
}

void loop(){
    Serial.print("Startt");
    updateState();
    runState();
}