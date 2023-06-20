#include <Arduino.h>
#include <avr/pgmspace.h>
String menuNames[] = {};
void setup()
{
    Serial.begin(115200);

    const __FlashStringHelper *menuNames[] = {F("MAIN_MENU"), F("SEN_CAT"),
                                              F("SEN_LS"), F("SEN_CONFIG"), F("SEN_SUP"), F("ADDSEN_OPT"),
                                              F("ADDSEN_STEP"),
                                              F("ADDING_SEN"),
                                              F("ADDING_SUC"),
                                              F("ADDING_FAIL"),
                                              F("SEN_ACTIVE"),
                                              F("SEN_REMCONF"),
                                              F("SEN_REMSUCC"),
                                              F("SEN_REMCAN"),
                                              F("SETT_MENU"),
                                              F("BATT_MENU"),
                                              F("BATT_MODE"),
                                              F("BATT_SAV"),
                                              F("BATT_SAV_ACT"),
                                              F("PROF_MENU"),
                                              F("PROF_SAVING"),
                                              F("PROF_SAVED"),
                                              F("PROF_DEL_1"),
                                              F("PROF_DEL_2"),
                                              F("PROF_OPT"),
                                              F("PROF_LIST"),
                                              F("PROF_SELECTED"),
                                              F("PROF_EXPORT"),
                                              F("PROF_EXPORTED"),
                                              F("PROFIMP_INST_1"),
                                              F("PROFIMP_INST_2"),
                                              F("PROF_LIST_MULT"),
                                              F("PROF_IMP_CONF"),
                                              F("PROF_IMPORTED"),
                                              F("CONN_MENU"),
                                              F("NODE_MENU"),
                                              F("NODE_SEARCH"),
                                              F("NODE_FOUND_F"),
                                              F("NODE_FOUND_LS"),
                                              F("NODE_F_MENU"),
                                              F("NODE_LOC_R_1"),
                                              F("NODE_LOC_SUC"),
                                              F("NODE_LOC_FAIL"),
                                              F("NODE_PAIR"),
                                              F("NODE_PAIR_SUC"),
                                              F("NODE_PAIR_FAIL"),
                                              F("STATION_MENU"),
                                              F("STATION_SEARCH"),
                                              F("STATION_S_LS"),
                                              F("STATION_S_FAIL"),
                                              F("STATION_CONN"),
                                              F("STATION_C_S"),
                                              F("STATION_C_F"),
                                              F("STATION_PR_LS"),
                                              F("STATION_DISC_C"),
                                              F("STATION_DISC_1"),
                                              F("STATION_DISC_S"),
                                              F("CHIP_INT_1"),
                                              F("CHIP_INT_S"),
                                              F("CHIP_INT_F"),
                                              F("EMPTY_MENU")};

    Serial.println(menuNames[0]);
    Serial.println(menuNames[1]);
}

void loop()
{
    // nothing to do
}