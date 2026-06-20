#include<Arduino.h>

const int ledPin = 4;
const int buzzerPin = 16;
const int buttonPin = 17;
const int firePin = 33;

unsigned long previousLed = 0;
unsigned long previousBuzzer = 0;
unsigned long previousFire = 0;
unsigned long previousSerial = 0;

unsigned long ledInterval = 0;
unsigned long buzzerInterval = 500;
unsigned long fireInterval = 100;
unsigned long serialInterval = 1000;

int fireValue = 0;
bool ledState = HIGH;

void fireSensorRead (){
    fireValue = analogRead(firePin);
}

void blinkLed (){
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
}

enum State {
    NORMAL,
    ALARM,
    SILENT
};

State currentState = NORMAL;

void updateState (){
    switch (currentState)
    {
    case NORMAL:
        if (fireValue <= 2000)
        {
            currentState = ALARM;
        }
        break;
    
    case ALARM:
        if (digitalRead(buttonPin) == LOW)
        {
            currentState = SILENT;
        }else if (fireValue > 2000)
        {
            currentState = NORMAL;
        }
        
        break;

    case SILENT:
        if (fireValue > 2000)
        {
            currentState = NORMAL;
        }
        break;
    }

    }

void runState (){
    switch (currentState)
    {
    case NORMAL:
        digitalWrite(buzzerPin, LOW);
        ledInterval = 1000;
        break;
    
    case ALARM:
        digitalWrite(buzzerPin, HIGH);
        ledInterval = 200;
        break;

    case SILENT:
        digitalWrite(buzzerPin, LOW);
        digitalWrite(ledPin, HIGH);
        break;
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(firePin, INPUT);
}
void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousFire >= fireInterval)
    {
        previousFire = currentMillis;
        fireSensorRead();
    }

    updateState();

    runState();

    if (currentMillis - previousLed >= ledInterval)
    {
        previousLed = currentMillis;
        blinkLed();
    }
    
    if (currentMillis - previousSerial >= serialInterval)
    {
        previousSerial = currentMillis;
        Serial.print("The value is:");
        Serial.println(fireValue);
    }
    
}