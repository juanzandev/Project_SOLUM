#include <Arduino.h>
#include <SDI12.h>
#include <SD.h>
#include <SPI.h>

// NOTES
// Project Title: SOLUM
// Name: Juan P. Zanguitu
// City/Province/Country: 30 de Agosto, Buenos Aires, Argentina
// College Student living in Nebraska, USA. Attending Mid-Plains Community College
File file;
#define SERIAL_BAUD 115200 // The baud rate for the output serial port
#define DATA_PIN 7		   // The pin of the SDI-12 data bus
#define POWER_PIN -1	   // The sensor power pin (or -1 if not switching power)

// Define the SDI-12 bus
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

// converts allowable address characters '0'-'9', 'a'-'z', 'A'-'Z',
// to a decimal number between 0 and 61 (inclusive) to cover the 62 possible addresses
byte charToDec(char i)
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
void sdi12_sensor_name(char i)
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
void printBufferToScreen()
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
void printInfo(char i)
{
	String command = "";
	command += (char)i;
	command += "I!";
	mySDI12.sendCommand(command);
	// Serial.print(">>>");
	// Serial.println(command);
	delay(30);
	printBufferToScreen();
}

void takeMeasurement(char i)
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
	int numMeasurements = sdiResponse.substring(4, 5).toInt();

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
	while (!mySDI12.available() > 1)
		;		// wait for acknowlegement
	delay(300); // let the data transfer
	printBufferToScreen();
	mySDI12.clearBuffer();
}

// this checks for activity at a particular address
// expects a char, '0'-'9', 'a'-'z', or 'A'-'Z'
boolean checkActive(char i)
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
			printBufferToScreen();
			mySDI12.clearBuffer();
			return true;
		}
	}
	mySDI12.clearBuffer();
	return false;
}

// this quickly checks if the address has already been taken by an active sensor
boolean isTaken(byte i)
{
	i = charToDec(i);					  // e.g. convert '0' to 0, 'a' to 10, 'Z' to 61.
	byte j = i / 8;						  // byte #
	byte k = i % 8;						  // bit #
	return addressRegister[j] & (1 << k); // return bit status
}

// this sets the bit in the proper location within the addressRegister
// to record that the sensor is active and the address is taken.
boolean setTaken(byte i)
{
	boolean initStatus = isTaken(i);
	i = charToDec(i); // e.g. convert '0' to 0, 'a' to 10, 'Z' to 61.
	byte j = i / 8;	  // byte #
	byte k = i % 8;	  // bit #
	addressRegister[j] |= (1 << k);
	return !initStatus; // return false if already taken
}

void setup()
{
	Serial.begin(SERIAL_BAUD);
	while (!Serial)
		;
	
	// INITIALIZES, CREATES A FILE IN THE SD CARD, WRITES THE TITLE FOR EACH OF THE
	// DATA TYPES THAT WILL BE WRITTEN IN THE FILE, AND CLOSES THE FILE.
	Serial.println("Initializing SD Card...");

	if (!SD.begin(4))
	{
		Serial.println("SD Card Failed!");
		while (true)
			;
	}
	Serial.println("Initialize Successful!");
	if (!SD.exists("sdi12.csv"))
	{
		file = SD.open("sdi12.csv", FILE_WRITE);
		file.println("Time,CSV,ST,SP,SBEC,SPWEC,");
	}
	else
	{
		file = SD.open("sdi12.csv", FILE_WRITE);
	}

	file.close();

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
		if (checkActive(i))
		{
			numSensors++;
			setTaken(i);
		} // scan address space 0-9
	/*
			See if there are any active sensors.
	 */
	boolean found = false;

	for (byte i = 0; i < 62; i++)
	{
		if (isTaken(i))
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

	Serial.println("");
	Serial.println();
	Serial.println("Time Elapsed (s), Sensor Address and ID, Volumentric Water Contect, Soil Temperature C, Soil Permitivity, Soil bulk EC in uS/cm, Soil pore water EC in us/cm.");
	Serial.println("-------------------------------------------------------------------------------");
}
int display_name = 0;
void loop()
{
	// only if the file where the data is stored will the sensor take measurements

	if (SD.exists("sdi12.csv"))
	{
		file = SD.open("sdi12.csv", FILE_WRITE);
		if (!SD.begin(4))
		{
			Serial.println("Initialize SD Failed!");
			while (true)
				;
		}
	}
	// prints measurements on the serial monitor
	for (char i = '0'; i <= '9'; i++)
		if (isTaken(i))
		{
			Serial.print(millis() / 1000);
			Serial.print(",\t");
			if (display_name == 0)
			{
				sdi12_sensor_name(i);
				display_name++;
			}
			takeMeasurement(i);
			Serial.println();
		}

	delay(5000); // wait ten seconds between measurement attempts.
}
