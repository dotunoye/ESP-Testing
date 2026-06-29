#include<Arduino.h>

int echoPin = 4;
int trigPin = 16;
int whitePin = 17;
int redPin = 5;
int buzzerPin = 18;
int buttonPin = 19;

float distance = 0;
bool whiteState = HIGH;
bool redState = HIGH;
bool buzzerState = HIGH;

unsigned long previousTrig = 0;
unsigned long previousWhite = 0;
unsigned long previousRed = 0;
unsigned long previousBuzzer = 0;
unsigned long previousSerial = 0;

unsigned long trigInterval = 1;
unsigned long whiteInterval = 1000;
unsigned long redInterval = 200;
unsigned long buzzerInterval = 500;
unsigned long serialInterval = 500;

enum State {
    IDLE,
    APPROACHING,
    TOO_CLOSE
};

State currentState = IDLE;

void updateState(){
    switch (currentState)
    {
    case IDLE:
        if (distance < 25)
        {
            currentState = APPROACHING;
        }
        break;   
    case APPROACHING:
        if (distance < 10)
        {
            currentState = TOO_CLOSE;
        }else if (distance >= 25)
        {
            currentState = IDLE;
            }
        
        break;
    case TOO_CLOSE:
        if (distance >= 25)
        {
            currentState = IDLE;
        }else if (digitalRead(buttonPin) == HIGH)
        {
            currentState = IDLE;
        }        
    }
}

void runState (){
    switch (currentState)
    {
    case IDLE:
        digitalWrite(whitePin, HIGH);
        digitalWrite(redPin, LOW);
        digitalWrite(buzzerPin, LOW);
        whiteInterval = 0;
        redInterval = 0;
        buzzerInterval = 0;
        break;
    
    case APPROACHING:
        whiteInterval = 500;
        buzzerInterval = 1000;
        digitalWrite(redPin, HIGH);
        break;
    case TOO_CLOSE:
        digitalWrite(whitePin, LOW);
        redInterval = 250;
        buzzerInterval = 200;
        break;
    }

}

void redLight (){
    redState = !redState;
    digitalWrite(redPin, redState);
}
void whiteLight (){
    whiteState = !whiteState;
    digitalWrite(whitePin, whiteState);
}
void buzzerUpdate (){
    buzzerState = !buzzerState;
    digitalWrite(buzzerPin, buzzerState);
}

void setup() {
    Serial.begin(115200);
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(whitePin, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
}
void loop() {
    unsigned long currentMillis = millis();

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034/2;

    updateState();
    runState();

    if (currentMillis - previousWhite >= whiteInterval)
    {
        previousWhite = currentMillis;
        whiteLight();
    }

    if (currentMillis - previousRed >= redInterval)
    {
        previousRed = currentMillis;
        redLight();
    }
    
    if (currentMillis - previousBuzzer >= buzzerInterval)
    {
        previousBuzzer = currentMillis;
        buzzerUpdate();
    }
    
    if (currentMillis - previousSerial >= serialInterval)
    {
        previousSerial = currentMillis;
        Serial.print("The distance is: ");
        Serial.println(distance);
    }
    


}