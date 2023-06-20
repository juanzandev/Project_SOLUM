#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
    lcd.init(); // initialize the lcd
    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Hello, I am Juan");
    lcd.setCursor(0, 1);
    lcd.print("Zanguitu and this");
    lcd.setCursor(0, 2);
    lcd.print("is project SOLUM");
    lcd.setCursor(0, 3);
    lcd.print("2023");
}

void loop()
{
}
