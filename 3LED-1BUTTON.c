// Define pin numbers
const int buttonPin = 7;
const int led1 = 8;
const int led2 = 9;
const int led3 = 10;

// Variables to track button states
bool led1State = false;
bool led2State = false;
bool led3State = false;

unsigned long lastPressTime = 0;
unsigned long lastReleaseTime = 0;
int pressCount = 0;
bool buttonPressed = false;
bool longPressDetected = false;
const int debounceDelay = 50;
const int longPressTime = 1000;
const int doublePressTime = 300;

void setup() {
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
}

void loop() {
    int buttonState = digitalRead(buttonPin);
    unsigned long currentTime = millis();

    if (buttonState == LOW) {
        if (!buttonPressed) {
            delay(debounceDelay);  // Debounce delay
            buttonPressed = true;
            lastPressTime = currentTime;
            pressCount++;
            longPressDetected = false;
        }
        if (buttonPressed && (currentTime - lastPressTime >= longPressTime) && !longPressDetected) {
            led2State = !led2State;
            digitalWrite(led2, led2State);
            pressCount = 0;
            longPressDetected = true;
        }
    } else {
        if (buttonPressed) {
            delay(debounceDelay);  // Debounce delay
            buttonPressed = false;
            lastReleaseTime = currentTime;
        }
    }

    // Check for double press
    if (pressCount == 2 && (currentTime - lastReleaseTime < doublePressTime)) {
        led3State = !led3State;
        digitalWrite(led3, led3State);
        pressCount = 0;
    }
    
    // Check for single press (after timeout for double press detection)
    if (pressCount == 1 && (currentTime - lastReleaseTime >= doublePressTime) && !longPressDetected) {
        led1State = !led1State;
        digitalWrite(led1, led1State);
        pressCount = 0;
    }
}