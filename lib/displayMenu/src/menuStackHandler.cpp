#include <Arduino.h>
#include <globals.h>

void addMenuToStack(Menu newMenu)
{
    menuStack_end += 1;
    menuStack_current = menuStack_end - 1;
    menuStack[menuStack_current] = newMenu;
    currentMenu = menuStack[menuStack_current];
}