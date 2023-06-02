#include <Arduino.h>

// The pin the button is connected to
const int buttonPin = 2;

void setup()
{
    // Set up the button pin as an input with the internal pull-up enabled
    pinMode(buttonPin, INPUT_PULLUP);

    // Start the Serial Monitor
    Serial.begin(115200);
}

void loop()
{
    // Read the state of the button
    int buttonState = digitalRead(buttonPin);

    // If the button is pressed, buttonState will be LOW
    if (buttonState == LOW)
    {
        Serial.println("Button is pressed");
    }
    else
    {
        Serial.println("Button is not pressed");
    }

    // Small delay to avoid flooding the Serial Monitor
    delay(100);
}