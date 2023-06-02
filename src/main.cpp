#include <Arduino.h>
#include <SDI12.h>
#include <SD.h>
#include <SPI.h>
#include <sdi12functions.h>
#include <StackArray.h>
#include <show_menu.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <displayMenu.h>

#define SERIAL_BAUD 115200 // The baud rate for the output serial port
#define CS_PIN 4		   // Change this to match your SD card CS pin
const int buttons = A0;
enum Menu
{
	MAIN_MENU,
	SENSOR_CATEGORIES,
	SENSOR_LIST,
	SENSOR_CONFIG,
	SENSOR_SUPPORTED,
	ADD_SENSOR_OPTIONS,
	ADD_SENSOR_STEPS,
	ADDING_SENSOR,
	SENSOR_ADD_SUCCESS,
	SENSOR_ADD_FAIL,
	SENSOR_ACTIVE,
	SENSOR_REMOVE_CONFIRM,
	SENSOR_REMOVE_SUCCESS,
	SENSOR_REMOVE_FAIL,
	SETTINGS_MENU,
	BATTERY_MENU,
	BATTERY_SAVING_CONFIRM,
	BATTERY_SAVING_ACTIVE,
	PROFILE_MENU,
	PROFILE_SAVING,
	PROFILE_SAVE,
	PROFILE_DELETE_CONFIRM,
	PROFILE_DELETE,
	PROFILE_OPTIONS_MENU,
	PROFILE_LIST,
	PROFILE_SELECT,
	PROFILE_EXPORT,
	PROFILE_EXPORT_SUCCESS,
	PROFILE_FOUND_LIST,
	PROFILE_FOUND_SINGLE,
	PROFILE_FOUND_CONFIRMATION,
	PROFILE_IMPORT,
	CONNECTIVITY_MENU,
	NODE_CONNECT_MENU,
	NODE_SEARCH,
	NODE_FOUND_LIST,
	NODE_PAIR_MENU,
	NODE_LOCATION_REQUEST,
	NODE_PAIR_CONFIRMATION,
	NODE_PAIR_RESULT,
	STATION_CONNECT_MENU,
	STATION_CONNECT_SEARCH,
	STATION_FOUND,
	STATION_CONNECT,
	STATION_CONNECT_SUCCESS,
	STATION_PAIRED,
	STATION_DISCONNECT_CONFIRM,
	STATION_DISCONNECT_SUCCESS,
	STATION_OPTIONS_MENU,
	CHIP_MENU,
	CHIP_INTERNET_CHECK,
	CHIP_INTERNET_RESULT
};
const char *menuNames[] = {
	"MAIN_MENU",
	"SENSOR_CATEGORIES",
	"SENSOR_LIST",
	"SENSOR_CONFIG",
	"SENSOR_SUPPORTED",
	"ADD_SENSOR_OPTIONS",
	"ADD_SENSOR_STEPS",
	"ADDING_SENSOR",
	"SENSOR_ADD_SUCCESS",
	"SENSOR_ADD_FAIL",
	"SENSOR_ACTIVE",
	"SENSOR_REMOVE_CONFIRM",
	"SENSOR_REMOVE_SUCCESS",
	"SENSOR_REMOVE_FAIL",
	"SETTINGS_MENU",
	"BATTERY_MENU",
	"BATTERY_SAVING_CONFIRM",
	"BATTERY_SAVING_ACTIVE",
	"PROFILE_MENU",
	"PROFILE_SAVING",
	"PROFILE_SAVE",
	"PROFILE_DELETE_CONFIRM",
	"PROFILE_DELETE",
	"PROFILE_OPTIONS_MENU",
	"PROFILE_LIST",
	"PROFILE_SELECT",
	"PROFILE_EXPORT",
	"PROFILE_EXPORT_SUCCESS",
	"PROFILE_FOUND_LIST",
	"PROFILE_FOUND_SINGLE",
	"PROFILE_FOUND_CONFIRMATION",
	"PROFILE_IMPORT",
	"CONNECTIVITY_MENU",
	"NODE_CONNECT_MENU",
	"NODE_SEARCH",
	"NODE_FOUND_LIST",
	"NODE_PAIR_MENU",
	"NODE_LOCATION_REQUEST",
	"NODE_PAIR_CONFIRMATION",
	"NODE_PAIR_RESULT",
	"STATION_CONNECT_MENU",
	"STATION_CONNECT_SEARCH",
	"STATION_FOUND",
	"STATION_CONNECT",
	"STATION_CONNECT_SUCCESS",
	"STATION_PAIRED",
	"STATION_DISCONNECT_CONFIRM",
	"STATION_DISCONNECT_SUCCESS",
	"STATION_OPTIONS_MENU",
	"CHIP_MENU",
	"CHIP_INTERNET_CHECK",
	"CHIP_INTERNET_RESULT"
	};

Menu currentMenu = MAIN_MENU;

StackArray<Menu> menuStack;

char waitForUserInput()
{

	while (Serial.available() == 0)
	{
		int buttonVoltage = analogRead(buttons);
		if (buttonVoltage > 50)
		{
			if (buttonVoltage < 650)
			{
				return 'q';
			}
			else if (buttonVoltage < 740)
			{
				return '1';
			}
			else if (buttonVoltage < 810)
			{
				return '2';
			}
			else if (buttonVoltage < 895)
			{
				return '3';
			}
			else
			{
				return '4';
			}
		}
	}
	return Serial.read();
}
void handleUserInput(char input)
{
	char userInput = input;
	Serial.print("handleUserInput: ");
	Serial.println(userInput);
	switch (userInput)
	{
	case '1':
		switch (currentMenu)
		{
		case MAIN_MENU:
			currentMenu = SENSOR_LIST;
			menuStack.push(SENSOR_LIST);
			break;
		default:
			break;
		}
		break;
	case 'q':
		if (menuStack.peek() != MAIN_MENU)
		{
			menuStack.pop();
			currentMenu = menuStack.peek();
			break;
		}
		break;
	default:
		break;
	}
}
void flushSerialBuffer()
{
	while (Serial.available() > 0)
	{
		Serial.read();
	}
}
int main(void)
{
	init();
#if defined(USBCON)
	USBDevice.attach();
#endif

	Serial.begin(SERIAL_BAUD);
	while (!Serial)
		;
	menuStack.push(MAIN_MENU);
	if (!SD.begin(CS_PIN))
	{
		Serial.println("Card failed, or not present");
		while (1)
			;
	}
	Serial.println("Card initialized.");
	while (true)
	{
		const char *menuName = menuNames[currentMenu];
		displayMenu(menuName);
		char userInput;
		userInput = waitForUserInput();
		flushSerialBuffer();
		Serial.print("waitForUserInput: ");
		Serial.println(userInput);
		handleUserInput(userInput);
	}
}
// PSEUDO CODE
/*
(MENU) - PSEUDO CODE
NOTE: Pluses (+) represent a 4x20 lcd screen. Extra resources at Project_SOLUM/menu_files/
Menu:

Main Screen
	Sections:
		+Sensor List
		+Add sensor
		+Remove sensor
		+Settings
Sensor List:
	Sections:
		+Sensors...
			On Action (Select):
				Sensor menu:
					Sections:
						+Information: Displays general information about the sensor such as measurement type,
						communication protocol, energy consumption, cable number and colors
						+Configuration: Lets the user set the measurement frequency and the upload frequency to the station
						+Measurement type: Detailed measurement type
						+Take measurement: Takes measurement and displays it on the screen

Add sensor
	Sections:
		+Sensor list
			On Action (Select):
				Measurement Type List
					+Soil Moisture
					+Soil Temperature
					+Wind Speed
					+Water Table
						On Action (Select Button x):
							Sensor List...
								+[Supported Sensor] 1
									On Action (Select Button x):
										+Information: 	Displays general information about the sensor such as measurement type,
														communication protocol, energy consumption, cable number and colors
										+Set Up Instructions
											On Action (Select Button 1):
												+Step 1:.......
													+Step 2:......
														+Step 3:.....
										+Add Sensor
											On Action (Select Button 2):
												+Adding sensor
												+[Sensor Name]
												+and taking
												+measurement...
													If addition is successful:
														+Successfully added:
														+[Sensor Name]
														+MT: [Measurement Type]
														+Measurement: [Info]
													Else
														+Could not add sensor
														+[Sensor Name]
														+Go to {Set Up
														+Instructions}...
								+[Supported Sensor] 2
								+[Supported Sensor] 3
								+[Supported Sensor] 4
Remove sensor
	Sections:
		+Active Sensor list
			On Action (Select):
				Confirmation screen
					Sections:
						+Remove sensor
						+[Sensor Name]?
						+Yes
							On Action(Select Button 3):
								Removes sensor
						+No
							On Action(Select Button 4):
								Cancels removal
Settings
	Sections:
		+Battery
			+Battery Level (display here)
			+Battery Mode
				On Action (Select):
					+Standard
					+Battery Saving
						On Action (Select):
							+Warning: Battery Saving
							+mode restricts the
							+amount of sensors
							+that can be used
								After x amount of time:
									Activate Low
									Battery Mode?
									Yes
										On Action(Select Button 3):
											Low Battery Mode
											has been activated.
									No
		+Profiles
			On Action (Select):
				+Create profile: saves the current list of sensors and configurations
					On Action (Select Button 2):
						+Create profile?
						+
						+Yes
						+No
				+Delete profile
					On Action (Select Button 3):
						+Delete profile?
						+
						+Yes
							On Action(Select Button 3):
								Creates profile
						+No
							On Action(Select Button 4):
								Cancels profile creation
				+ Profile Options
					Sections:
						+Select Profile
							On Action(Select Button 1):
								+Profile 1
									On Action (Select Button x):
										Profile x has been
										selected.
								+Profile 2
								+Profile 3
								+Profile 4
						+Import Profile
							On Action(Select Button 2):
								+Add profile file -- Screen will stay for x amount of time
								+in the profile
								+folder in the
								+SD Card...
							After time:
								+The file should be -- Screen will stay for x amount of time
								+called
								+"profile_x.csv"
							After time 2 (If 1 file found):
								+Profile found!
								+Add [Profile Name]?

								+Yes
								On Action(Select Button 3):
										(Scans file and checks if its the right information):
											+Profile Added! -- 	Screen will stay for x amount of time
																and will return to Profiles menu
										(If information is not right):
											+The Profile file -- Screen will stay for x amount of time
																and will return to Profiles menu
											+is not correct
											+Check the resources
											+and try again...


								+No
									On Action(Select Button 4):
										Cancels addition
							After time 2 (If 1+ file found):
								+Multiple profiles
								+have been found...
								+Choose a profile
								+from the list.
									After time 3:
										+profile_x.csv
										+profile_y.csv
										+profile_z.csv
										+profile_a.csv
										On Action (Select Button x):
											+Add profile
											+[Profile Name]?
											+Yes
											+No
											On Action(Select Button 3):
										(Scans file and checks if its the right information):
											+Profile Added! -- 	Screen will stay for x amount of time
																and will return to Profiles menu
										(If information is not right):
											+The Profile file -- Screen will stay for x amount of time
																and will return to Profiles menu
											+is not correct
											+Check the resources
											+and try again...


								+No
									On Action(Select Button 4):
										Cancels addition

									On Action(Select Button 3):
										(Scans file and checks if its the right information):
											+Profile Added! -- 	Screen will stay for x amount of time
																and will return to Profiles menu
										(If information is not right):
											+The Profile file -- Screen will stay for x amount of time
																and will return to Profiles menu
											+is not correct
											+Check the resources
											+and try again...


								+No
									On Action(Select Button 4):
										Cancels addition
						+Export Profile
							On Action (Select Button 3):
								Your current node
								set up will be
								stored in the
								SD Card...
								After time:
									+Profile saved in --	Screen will stay for x amount of time
														and will return to Profiles menu
									+SD Card as..
									+"saved_profile_x.csv"
		+Connectivity
			+Node Connection
				On Action (Select Button 1):
					+Connect to Node
						On Action (Select Button 1):
							+Searching for nodes... --	Screen will stay for x amount of time
														and it will return a found node list
														or it will return that no nodes were found
							After wait (Sensors found):
								+Node 1
									On Action (Select Button x):
										+Node ID: ........
										+Location
											On Action (Select Button 2):
												Requesting
												location of node
												[Node ID]...
												If request successful
													+lat: ..........
													+long: .........
												Else
													Failed request of
													node [Node ID]
													location.
										+Pair node
											On Action (Select Button 3):
												+Pair with node
												+[Node ID]?
												+Yes
													On Action (Select Button 3):
														Tries to pair with node...
														If pairing was unsuccessful.
															+Could not pair with
															+node [ID]. Try again?
															+Yes
															+No
														If pairing was successful/
															+Nodes Paired!
															+Node [ID] (current)
															+paired with
															+Node [ID]
												+No
										+Current ID: [Local Node ID]
								+Node 2
								+Node 3
								+Node 4
							After wait (No sensors found):
								+No nodes were found.
								+Please try again and
								+make sure your node is
								+connected
					+Disconnect from Node
						On Action (Select Button 2):
							+Node 1: [ID]
								On Action (Select Button x):
									+Disconnect from node
									+[ID] ?
									+Yes
										On Action (Button 3):
											+Disconnecting...
											If disconnection is unsuccessful
												+Unable to disconnect
												+from node [ID]
												+Try Again? Yes
											Else
												Successfully
												disconnected
												from
												[Node ID]
											No
									No
							+Node 2: [ID]
							+Node 3: [ID]
							+Node 4: [ID]
					+Paired nodes
						On Action (Button 3)
							+Connected nodes' list
								On Action (Select Button x):
									+Node Information
										On Action (Select Button 1):
											+Location
												On Action (Select Button 1):
													If request successful:
														Lat: ------
														Long: -----
													Else:
														Failed to request
														[Node ID]
														location.
											+Battery Level
												On Action (Select Button 2):
													Battery Level
													of [Node ID]
													is xxx%.
											+Active sensors
												On Action (Select Button 3):
													[Active Sensor] 1
													[Active Sensor] 2
													[Active Sensor] 3
													[Active Sensor] 4


			+Station Connection
				On Action (Select Button 2):
					+Connect to Station
						On Action (Select Button 1):
							+Searching for -- 	Screen will stay for x amount of time
												and it will return a found station list
												or it will return that no stations were found
							+stations...
							If station/s found
								+Station 1: [ID]
									On Action (Select Button x):
										+Connect to station
										+[ID] ?
										+Yes
											On action (Select Button 3):
												+Connecting to
												+station [ID]...
													If connection successful
														+Successfully connected
														+to station
														+[ID].
													Else
														+Connection failed
														+Try again?
														+Yes
														+No
										No
								+Station 2: [ID]
								+Station 3: [ID]
								+Station 4: [ID]
					+Disconnect from Station
						On Action (Select Button 3):
							Connected station list
								+Station 1: [ID]
									On Action (Select Button x):
										+Disconnect from
										+station [ID]?
										+Yes
										+No
								+Station 2: [ID]
								+Station 3: [ID]
								+Station 4: [ID]

					+Paired Stations List
						On Action (Select Button 3):
							+Station 1: [ID]
								On Action (Select Button x):
									+Station [ID]
									+Configuration
									+Connected Nodes
							+Station 2: [ID]
							+Station 3: [ID]
							+Station 4: [ID]
			+Data chip
				On Action (Select Button 2):
					+Company: [Company]
					+Check Internet
						On Action (Select Button 2):
							Checking Internet
							Connection...
							After check:
								If there is internet connection:
									Successfully
									connected to
									the internet.
								Else
									Failed to
									connect to the
									internet.
		+Node Location
			On Action (Select Button 4):
				+Node [ID]
				+Lat: [Latitude]
				+Long: [Longitude]






INITIALIZES, CREATES A FILE IN THE SD CARD, WRITES THE TITLE FOR EACH OF THE
DATA TYPES THAT WILL BE WRITTEN IN THE FILE, AND CLOSES THE FILE.

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

*/