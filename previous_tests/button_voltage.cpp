#include <Arduino.h>
const int BUTTON_PIN = A0;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    int buttonVoltage = analogRead(BUTTON_PIN);

    if (buttonVoltage < 50)
    {
        Serial.println("No button pressed");
    }
    else if (buttonVoltage < 670)
    {
        Serial.println("Back button pressed");
    }
    else if (buttonVoltage < 720)
    {
        Serial.println("Button 1 pressed");
    }
    else if (buttonVoltage < 790)
    {
        Serial.println("Button 2 pressed");
    }
    else if (buttonVoltage < 895)
    {
        Serial.println("Button 3 pressed");
    }
    else
    {
        Serial.println("Button 4 pressed");
    }
    // Serial.println(buttonVoltage);

    /*
    Readings
    47k Resistor = 640
    39k Resistor = 704
    27k Resistor = 770
    22K Resistor = 803
    12k Resistor = 888
    4.7k Resistor = 950
    2.2k Resistor = 978
    1k Resistor = 990


    */
    // Serial.println(analogRead(buttonVoltage));
    delay(150);
}