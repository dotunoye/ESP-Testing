#include<Arduino.h>

int ledPin = 4;
int buttonPin = 16;
unsigned long interval = 500;
unsigned long previousMillis = 0;
bool ledState = false;

enum State {
    ON,
    OFF
};

State currentState = OFF;

void assignState (){
    switch (currentState)
    {
    case ON:
        if (digitalRead(buttonPin) == LOW)
        {
            currentState = OFF;
        }
        break;
    
    case OFF:
    if (digitalRead(buttonPin) == LOW)
    {
        currentState = ON;
    }
        break;
    }
}

void executeState (unsigned long currentMilli){
    switch (currentState)
    {
    case ON:
        if (currentMilli - previousMillis >= interval)
        {
            previousMillis = currentMilli;
            ledState = !ledState;
            digitalWrite(ledPin, ledState);
            delay(250);
        }  
        break;
    
    case OFF:
        digitalWrite(ledPin, LOW);
        delay(250);
        break;
    }
}
void setup (){
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop(){
    unsigned long currentMillis = millis();
    assignState();
    executeState(currentMillis);
    
}