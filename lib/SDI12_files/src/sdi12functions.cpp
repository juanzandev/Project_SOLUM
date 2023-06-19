#include <Arduino.h>
#include <SDI12.h>
#include <SdFat.h>
#include <sdi12functions.h>

File file;

#define DATA_PIN 7   // The pin of the SDI-12 data bus
#define POWER_PIN -1 // The sensor power pin (or -1 if not switching power)

SDI12 mySDI12(DATA_PIN);

// keeps track of active addresses
// each bit represents an address:
// 1 is active (taken), 0 is inactive (available)
// setTaken('A') will set the proper bit for sensor 'A'
byte addressRegister[8] = {
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000};

uint8_t numSensors = 0;

void sdi12_start()
{
    Serial.println("Opening SDI-12 bus...");
    mySDI12.begin();
    delay(500); // allow things to settle

    // // Power the sensors;
    // if(POWER_PIN > 0){
    //   Serial.println("Powering up sensors...");
    //   pinMode(POWER_PIN, OUTPUT);
    //   digitalWrite(POWER_PIN, HIGH);
    //   delay(200);
    // }

    Serial.println("Scanning all addresses, please wait...");
    /*
            Quickly Scan the Address Space
     */

    for (byte i = '0'; i <= '9'; i++)
        if (sdi12_checkActive(i))
        {
            numSensors++;
            sdi12_setTaken(i);
        } // scan address space 0-9
    /*
            See if there are any active sensors.
     */
    boolean found = false;

    for (byte i = 0; i < 62; i++)
    {
        if (sdi12_isTaken(i))
        {
            found = true;
            Serial.print("First address found:  ");
            // Serial.println(decToChar(i));
            Serial.print("Total number of sensors found:  ");
            Serial.println(numSensors);
            break;
        }
    }

    if (!found)
    {
        Serial.println("No sensors found, please check connections and restart the Arduino.");
        while (true)
            ;
    } // stop here
}

void sdi12_measurement()
{
    int display_name = 0;
    for (char i = '0'; i <= '9'; i++)
        if (sdi12_isTaken(i))
        {
            Serial.print(millis() / 1000);
            Serial.print(",\t");
            if (display_name == 0)
            {
                sdi12_sensorName(i);
                display_name++;
            }
            sdi12_takeMeasurement(i);
            Serial.println();
        }
}
// converts allowable address characters '0'-'9', 'a'-'z', 'A'-'Z',
// to a decimal number between 0 and 61 (inclusive) to cover the 62 possible addresses
byte sdi12_charToDec(char i)
{
    if ((i >= '0') && (i <= '9'))
        return i - '0';
    if ((i >= 'a') && (i <= 'z'))
        return i - 'a' + 10;
    if ((i >= 'A') && (i <= 'Z'))
        return i - 'A' + 37;
    else
        return i;
}
void sdi12_sensorName(char i)
{
    String command = "";
    command += (char)i;
    command += "I!";
    mySDI12.sendCommand(command);
    // Serial.print(">>>");
    // Serial.println(command);
    delay(30);
    String name = mySDI12.readString();
    if (file)
    {
        file.println("Sensor name: " + name);
    }
    file.close();
}
void sdi12_printBufferToScreen()
{
    String buffer = "";
    mySDI12.read(); // consume address
    int counter = 0;
    while (mySDI12.available())
    {
        char c = mySDI12.read();
        // Volumentric water content %, Soil Temperature degrees C, Soil Permitivity, Soil Bulk EC in uS/cm

        if (c == '+')
        {
            if (counter > 0)
            {
                buffer += ',';
            }

            counter++;
        }
        else if ((c != '\n') && (c != '\r'))
        {
            buffer += c;
        }
        delay(50);
    }
    // prints measurements into the CSV file
    if (file)
    {
        file.println((String(millis() / 1000)) + "," + buffer);
        file.close();
    }
    Serial.print(buffer);
}

// gets identification information from a sensor, and prints it to the serial port
// expects a character between '0'-'9', 'a'-'z', or 'A'-'Z'.
void sdi12_printInfo(char i)
{
    String command = "";
    command += (char)i;
    command += "I!";
    mySDI12.sendCommand(command);
    // Serial.print(">>>");
    // Serial.println(command);
    delay(30);
    sdi12_printBufferToScreen();
}

void sdi12_takeMeasurement(char i)
{
    String command = "";
    command += i;
    command += "M!"; // SDI-12 measurement command format  [address]['M'][!]
    mySDI12.sendCommand(command);
    delay(30);

    // wait for acknowlegement with format [address][ttt (3 char, seconds)][number of measurments available, 0-9]
    String sdiResponse = "";
    delay(30);
    while (mySDI12.available()) // build response string
    {
        char c = mySDI12.read();
        if ((c != '\n') && (c != '\r'))
        {
            sdiResponse += c;
            delay(5);
        }
    }
    mySDI12.clearBuffer();

    // find out how long we have to wait (in seconds).
    uint8_t wait = 0;
    wait = sdiResponse.substring(1, 4).toInt();

    // Set up the number of results to expect
    // int numMeasurements = sdiResponse.substring(4, 5).toInt();

    unsigned long timerStart = millis();
    while ((millis() - timerStart) < (1000 * wait))
    {
        if (mySDI12.available()) // sensor can interrupt us to let us know it is done early
        {
            mySDI12.clearBuffer();
            break;
        }
    }
    // Wait for anything else and clear it out
    delay(30);
    mySDI12.clearBuffer();

    // in this example we will only take the 'DO' measurement
    command = "";
    command += i;
    command += "D0!"; // SDI-12 command to get data [address][D][dataOption][!]
    mySDI12.sendCommand(command);
    while ((!mySDI12.available()) > 1)
        ;       // wait for acknowlegement
    delay(300); // let the data transfer
    sdi12_printBufferToScreen();
    mySDI12.clearBuffer();
}

// this checks for activity at a particular address
// expects a char, '0'-'9', 'a'-'z', or 'A'-'Z'
boolean sdi12_checkActive(char i)
{

    String myCommand = "";
    myCommand = "";
    myCommand += (char)i; // sends basic 'acknowledge' command [address][!]
    myCommand += "!";

    for (int j = 0; j < 3; j++)
    { // goes through three rapid contact attempts
        mySDI12.sendCommand(myCommand);
        delay(30);
        if (mySDI12.available())
        { // If we here anything, assume we have an active sensor
            sdi12_printBufferToScreen();
            mySDI12.clearBuffer();
            return true;
        }
    }
    mySDI12.clearBuffer();
    return false;
}

// this quickly checks if the address has already been taken by an active sensor
boolean sdi12_isTaken(byte i)
{
    i = sdi12_charToDec(i);               // e.g. convert '0' to 0, 'a' to 10, 'Z' to 61.
    byte j = i / 8;                       // byte #
    byte k = i % 8;                       // bit #
    return addressRegister[j] & (1 << k); // return bit status
}

// this sets the bit in the proper location within the addressRegister
// to record that the sensor is active and the address is taken.
boolean sdi12_setTaken(byte i)
{
    boolean initStatus = sdi12_isTaken(i);
    i = sdi12_charToDec(i); // e.g. convert '0' to 0, 'a' to 10, 'Z' to 61.
    byte j = i / 8;         // byte #
    byte k = i % 8;         // bit #
    addressRegister[j] |= (1 << k);
    return !initStatus; // return false if already taken
}