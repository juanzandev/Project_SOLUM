// sdi12functions.h

#ifndef SDI12_FUNCTIONS
#define SDI12_FUNCTIONS
#include <Arduino.h>

void sdi12_start();
void sdi12_measurement();
byte sdi12_charToDec(char i);
void sdi12_sensorName(char i);
void sdi12_printBufferToScreen();
void sdi12_printInfo(char i);
void sdi12_takeMeasurement(char i);
boolean sdi12_checkActive(char i);
boolean sdi12_isTaken(byte i);
boolean sdi12_setTaken(byte i);

#endif