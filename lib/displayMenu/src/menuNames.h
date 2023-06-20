// menu_names.h
#ifndef MENU_NAMES_H
#define MENU_NAMES_H

#include <Arduino.h>
#include <avr/pgmspace.h>

extern const __FlashStringHelper **menuNames; // Declare the menuNames variable
void initMenuNames();                         // Declare the function

#endif // MENU_NAMES_H
