#include <Arduino.h>
#include <SPI.h>
#include <SdFat.h>
#include <LiquidCrystal_I2C.h>
#include <avr/pgmspace.h>

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 20
#define LCD_ROWS 4
File file;
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
SdFat SD;
void displayMenu(String menu_name)
{
    // Initialize LCD
    lcd.init();
    lcd.backlight();
    if (!SD.begin(4))
    {
        Serial.println("SD card initialization failed");
        while (1)
            ;
    }
    Serial.println("Card initialized.");
    // Open the CSV file
    file = SD.open("test.csv", FILE_READ);
    if (!file)
    {
        Serial.println("Error opening test.csv");
        while (1)
            ;
    }
    Serial.println("test.csv opened");
    while (file.available())
    {
        String line = file.readStringUntil('\n');
        Serial.println("Line: ");
        Serial.println(line);
        int firstCommaIndex = line.indexOf(',');
        Serial.print("First comma index: ");
        Serial.println(firstCommaIndex);
        String menuName = line.substring(0, firstCommaIndex);
        Serial.print("menu_name: ");
        Serial.println(menu_name);
        Serial.print("menuName: ");
        Serial.println(menuName);

        if (menu_name.equalsIgnoreCase(menuName))
        {
            Serial.println("Equal");
        }
        else
        {
            Serial.println("Not Equal");
        }
        if (menu_name.equalsIgnoreCase(menuName))
        {
            int fromIndex = firstCommaIndex + 1;
            for (int row = 0; row < LCD_ROWS; row++)
            {
                int nextCommaIndex = line.indexOf(',', fromIndex);
                if (nextCommaIndex == -1)
                {
                    nextCommaIndex = line.length();
                }
                Serial.println(row);
                String item = line.substring(fromIndex, nextCommaIndex);
                item.trim();
                Serial.println(item);

                lcd.setCursor(0, row);
                lcd.print(item);
                fromIndex = nextCommaIndex + 1;
            }
            break;
        }
    }
    file.close();
    SD.end();
}
