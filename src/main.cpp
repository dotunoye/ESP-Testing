#include <Arduino.h>

int whiteLed = 4;
int redLed = 16;
int rgbLed1 = 17; /*Blue*/
int rgbLed2 = 5;  /*Green*/
int rgbLed3 = 18; /*Red*/

int buttonWhite = 27;
int buttonRed = 26;
int buttonRgb = 25;

bool redLedState = false;
bool whiteLedState = false;

unsigned long redMillis = 0;
unsigned long whiteMillis = 0;
unsigned long redInterval = 250;
unsigned long whiteInterval = 700;
unsigned long rgbMillis = 0;
unsigned long rgbInterval = 500;


enum redState {
    R_ON,
    R_OFF,
    R_BLINK,
};

redState redCurrent = R_OFF;

bool lastRedState = HIGH;

void assignRed (){
    bool redRead = digitalRead(buttonRed);
    bool redPressed = (redRead == LOW && lastRedState == HIGH);
   if (redPressed) {
        delay(50); // Wait out the physical bouncing
        lastRedState = LOW; // Force the memory to sync cleanly with the press
    } else {
        lastRedState = redRead; // Otherwise track normally
    }
    switch (redCurrent)
    {
    case R_OFF:
        if (redPressed)
        {
            redCurrent = R_ON;
        }
        break;
    case R_ON:
        if (redPressed)
        {
            redCurrent = R_BLINK;
        }
        break;
    case R_BLINK:
        if (redPressed)
        {
            redCurrent = R_OFF;
        }
    }
}

void executeRed(unsigned long currentMilli){
    switch (redCurrent)
    {
    case R_OFF:
        digitalWrite(redLed, LOW);
        break;
    case R_ON:
        digitalWrite(redLed, HIGH);
        break;
    case R_BLINK:
        if (currentMilli - redMillis >= redInterval)
        {
            redMillis = currentMilli;
            redLedState = !redLedState;
            digitalWrite(redLed, redLedState);
        }
        break;
    }
}
void setup() {
    Serial.begin(115200);
    pinMode(whiteLed, OUTPUT);
    pinMode(redLed, OUTPUT);
    pinMode(rgbLed1, OUTPUT);
    pinMode(rgbLed2, OUTPUT);
    pinMode(rgbLed3, OUTPUT);
    
    pinMode(buttonRed, INPUT_PULLUP);
    pinMode(buttonWhite, INPUT_PULLUP);
    pinMode(buttonRgb, INPUT_PULLUP);

    Serial.println("--- 9-State Advanced Master Controller Online ---");
}

void loop() {
    unsigned long currentMillis = millis();
    assignRed();
    executeRed(currentMillis);
}