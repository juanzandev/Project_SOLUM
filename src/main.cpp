#include <Arduino.h>
#include <SDI12.h>
#include <SPI.h>
#include <sdi12functions.h>
#include <Wire.h>
#include <displayMenu.h>
#include <avr/pgmspace.h>
#include <menuVariables.h>
#include <menuNames.h>
#include <menuStackHandler.h>
#include <globals.h>
#include <userInputHandler.h>

#define SERIAL_BAUD 115200 // The baud rate for the output serial port
const int buttons = A0;

void initMenuNames();
char waitForUserInput();

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
