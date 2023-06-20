#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

// Initialize the I2C interface at address 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);
RTC_DS3231 rtc;

void setup()
{
    lcd.init();
    lcd.backlight(); // Turn on the backlight

    if (!rtc.begin())
    {
        lcd.print("Couldn't find RTC");
        while (1)
            ;
    }

    if (rtc.lostPower())
    {
        lcd.print("RTC lost power");
        // This will set the RTC to the date this sketch was compiled
    }
    // rtc.adjust(DateTime(2023, 6, 20, 15, 16, 00));
}

void loop()
{
    DateTime now = rtc.now();

    lcd.setCursor(0, 0);
    lcd.print("Current Date & Time: ");
    char date_str[20];
    char time_str[10];

    // Format the date and time with leading zeros
    sprintf(date_str, "%04d/%02d/%02d", now.year(), now.month(), now.day());
    sprintf(time_str, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    lcd.setCursor(0, 2);
    lcd.print(date_str);
    lcd.print(' ');
    lcd.print(time_str);
    delay(1000);
}
