#include <Arduino.h>
const int BUTTON_PIN = A0;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    int buttonVoltage = analogRead(BUTTON_PIN);
    // Serial.println(buttonVoltage);

    if (buttonVoltage < 50)
    {
        Serial.println("No button pressed");
    }
    else if (buttonVoltage < 220)
    {
        Serial.println("Back button pressed");
    }
    else if (buttonVoltage < 350)
    {
        Serial.println("Button 1 pressed");
    }
    else if (buttonVoltage < 500)
    {
        Serial.println("Button 2 pressed");
    }
    else if (buttonVoltage < 600)
    {
        Serial.println("Button 3 pressed");
    }
    else if (buttonVoltage < 710)
    {
        Serial.println("Button 4 pressed");
    }
    else
    {
        Serial.println("Next button pressed");
    }
    // Serial.println(buttonVoltage);

    /*
    Readings
    390k Resistor = 196
    180k Resistor = 355
    120k Resistor = 415
    47k Resistor = 640
    39k Resistor = 704
    27k Resistor = 770
    22K Resistor = 803
    15k Resistor = 794
    12k Resistor = 888
    4.7k Resistor = 950
    2.2k Resistor = 978
    1k Resistor = 990


    */
    // Serial.println(analogRead(buttonVoltage));
    delay(200);
}