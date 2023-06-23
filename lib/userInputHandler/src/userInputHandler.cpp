// userInputHandler.cpp
#include <Arduino.h>
#include "userInputHandler.h" // Include the header file you just created
#include <menuStackHandler.h>
#include <globals.h>
#include <menuVariables.h>
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
