#include <Arduino.h>
#include <SDI12.h>
#include <SPI.h>
#include <sdi12functions.h>
#include <Wire.h>
#include <displayMenu.h>
#include <avr/pgmspace.h>
#include <menuVariables.h>
#include <menuNames.h>
#define SERIAL_BAUD 115200 // The baud rate for the output serial port
const int buttons = A0;

void initMenuNames();
char waitForUserInput();
void addMenuToStack(Menu newMenu);
void handleUserInput(char input);

int menuStack_end = 0;
int menuStack_current = menuStack_end - 1;
int main_menu_id = 0;
Menu currentMenu;

Menu menuStack[20] = {MAIN_MENU, EMPTY_MENU, EMPTY_MENU, EMPTY_MENU, EMPTY_MENU,
					  EMPTY_MENU, EMPTY_MENU, EMPTY_MENU, EMPTY_MENU, EMPTY_MENU,
					  EMPTY_MENU, EMPTY_MENU, EMPTY_MENU, EMPTY_MENU, EMPTY_MENU,
					  EMPTY_MENU, EMPTY_MENU, EMPTY_MENU, EMPTY_MENU, EMPTY_MENU};

int main(void)
{
	init();
#if defined(USBCON)
	USBDevice.attach();
#endif

	Serial.begin(SERIAL_BAUD);

	while (!Serial)
	{
		;
	}
	initMenuNames();
	menuStack_end += 1;
	int currentID = menuStack_current;
	menuStack[currentID] = MAIN_MENU;
	Serial.print("Current Menu ID: ");
	Serial.println(menuStack[menuStack_current]);
	currentMenu = MAIN_MENU;
	displayMenu(menuNames[currentMenu]);
	while (true)
	{
		char input = waitForUserInput();
		handleUserInput(input);
		Serial.print("end: ");
		Serial.println(menuStack_end);
		Serial.print("current: ");
		Serial.println(menuStack_current);
		displayMenu(menuNames[currentMenu]);
	}
}

MenuTransition transitions[] = {
	{MAIN_MENU, '1', SEN_LS},
	{MAIN_MENU, '2', SEN_CAT},
	{MAIN_MENU, '3', SEN_ACTIVE},
	{MAIN_MENU, '4', SETT_MENU},
	{SEN_LS, '1', SEN_CONFIG},
	{SEN_CAT, '1', SEN_SUPP},
	{SEN_CAT, '2', SEN_SUPP},
	{SEN_CAT, '3', SEN_SUPP},
	{SEN_CAT, '4', SEN_SUPP},
	{SEN_SUPP, '1', ADDSEN_OPT},
	{SEN_SUPP, '2', ADDSEN_OPT},
	{SEN_SUPP, '3', ADDSEN_OPT},
	{SEN_SUPP, '4', ADDSEN_OPT},
	{SEN_ACTIVE, '1', SEN_REMCONF},
	{SEN_ACTIVE, '2', SEN_REMCONF},
	{SEN_ACTIVE, '3', SEN_REMCONF},
	{SEN_ACTIVE, '4', SEN_REMCONF},
	{SETT_MENU, '1', BATT_MENU},
	{SETT_MENU, '2', PROF_MENU},
	{SETT_MENU, '3', CONN_MENU},
	{SETT_MENU, '4', NODE_LOC_R_1},
	{BATT_MENU, '2', BATT_MODE},
	{BATT_MODE, '2', BATT_SAV}};
char waitForUserInput()
{

	while (Serial.available() == 0)
	{
		int buttonVoltage = analogRead(buttons);
		if (buttonVoltage > 50)
		{
			if (buttonVoltage < 220)
			{
				return 'b';
			}
			else if (buttonVoltage < 350)
			{
				return '1';
			}
			else if (buttonVoltage < 500)
			{
				return '2';
			}
			else if (buttonVoltage < 600)
			{
				return '3';
			}
			else if (buttonVoltage < 710)
			{
				return '4';
			}
			else
			{
				return 'n';
			}
		}
	}

	return Serial.read();
}
void addMenuToStack(Menu newMenu)
{
	menuStack_end += 1;
	menuStack_current = menuStack_end - 1;
	menuStack[menuStack_current] = newMenu;
	currentMenu = menuStack[menuStack_current];
}
void handleUserInput(char input)
{
	for (size_t i = 0; i < sizeof(transitions) / sizeof(MenuTransition); i++)
	{
		if (transitions[i].currentMenu == currentMenu && transitions[i].input == input)
		{
			addMenuToStack(transitions[i].newMenu);
			return;
		}
	}

	if (input == 'b')
	{
		if (menuStack[menuStack_current] != main_menu_id)
		{
			menuStack[menuStack_current] = EMPTY_MENU;
			menuStack_end -= 1;
			menuStack_current = menuStack_end - 1;
			currentMenu = menuStack[menuStack_current];
			Serial.print("Current Menu ID: ");
			Serial.println(menuStack[menuStack_current]);
			Serial.println("Quit");
			Serial.print("Logged input: ");
			Serial.println(input);
		}
	}
}
