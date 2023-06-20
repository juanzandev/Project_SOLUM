#include <Arduino.h>
#include <SdFat.h>
SdFat SD;
File file;

void setup()
{
    Serial.begin(115200);

    // Initialize SD card
    if (!SD.begin(4))
    {
        Serial.println("SD card initialization failed");
        while (1)
            ;
    }

    // Open the CSV file
    file = SD.open("test.csv");
    if (!file)
    {
        Serial.println("Error opening test.csv");
        while (1)
            ;
    }

    // Read and print the file contents line by line
    while (file.available())
    {
        String line = file.readStringUntil('\n');
        Serial.println(line);
    }

    // Close the file
    file.close();
}

void loop()
{
    // Your code here
}
