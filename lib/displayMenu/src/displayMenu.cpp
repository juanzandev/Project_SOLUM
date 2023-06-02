#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 20
#define LCD_ROWS 4

void displayMenu(String menu_name)
{
    File file;
    LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

    // Initialize LCD
    lcd.init();
    lcd.backlight();

    // Open CSV file
    file = SD.open("menus.csv");
    if (!file)
    {
        Serial.println("Error opening menus.csv");
        lcd.setCursor(0, 0);
        lcd.print("Error opening");
        lcd.setCursor(0, 1);
        lcd.print("menus.csv");
        while (1)
            ;
    }

    // Find the line for the target menu
    String targetMenu = menu_name; // Replace this with your target menu

    while (file.available())
    {
        String line = file.readStringUntil('\n');
        int firstCommaIndex = line.indexOf(',');
        String menuName = line.substring(0, firstCommaIndex);

        if (menuName == targetMenu)
        {
            // Found the target menu, now parse and display the items
            int fromIndex = firstCommaIndex + 1;
            for (int row = 0; row < LCD_ROWS; row++)
            {
                int nextCommaIndex = line.indexOf(',', fromIndex);
                if (nextCommaIndex == -1)
                    nextCommaIndex = line.length(); // no more commas
                String item = line.substring(fromIndex, nextCommaIndex);

                // Remove any trailing newline or carriage return characters
                item.trim();

                // Print the item to LCD
                lcd.setCursor(0, row);
                lcd.print(item);
                fromIndex = nextCommaIndex + 1;
            }
            break;
        }
    }
    file.close();
}
