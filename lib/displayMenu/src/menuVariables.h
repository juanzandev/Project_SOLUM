// Menu.h
#ifndef MENU_H
#define MENU_H

enum Menu
{
    MAIN_MENU,
    SEN_CAT,
    SEN_LS,
    SEN_CONFIG,
    SEN_SUPP,
    ADDSEN_OPT,
    ADDSEN_STEP,
    ADDING_SEN,
    ADDING_SUC,
    ADDING_FAIL,
    SEN_ACTIVE,
    SEN_REMCONF,
    SEN_REMSUCC,
    SEN_REMCAN,
    SETT_MENU,
    BATT_MENU,
    BATT_MODE,
    BATT_SAV,
    BATT_SAV_ACT,
    PROF_MENU,
    PROF_SAVING,
    PROF_SAVED,
    PROF_DEL_1,
    PROF_DEL_2,
    PROF_OPT,
    PROF_LIST,
    PROF_SELECTED,
    PROF_EXPORT,
    PROF_EXPORTED,
    PROFIMP_INST_1,
    PROFIMP_INST_2,
    PROF_LIST_MULT,
    PROF_IMP_CONF,
    PROF_IMPORTED,
    CONN_MENU,
    NODE_MENU,
    NODE_SEARCH,
    NODE_FOUND_F,
    NODE_FOUND_LS,
    NODE_F_MENU,
    NODE_LOC_R_1,
    NODE_LOC_SUC,
    NODE_LOC_FAIL,
    NODE_PAIR,
    NODE_PAIR_SUC,
    NODE_PAIR_FAIL,
    STATION_MENU,
    STATION_SEARCH,
    STATION_S_LS,
    STATION_S_FAIL,
    STATION_CONN,
    STATION_C_S,
    STATION_C_F,
    STATION_PR_LS,
    STATION_DISC_C,
    STATION_DISC_1,
    STATION_DISC_S,
    CHIP_INT_1,
    CHIP_INT_S,
    CHIP_INT_F,
    EMPTY_MENU
};

struct MenuTransition
{
    Menu currentMenu;
    char input;
    Menu newMenu;
};

extern MenuTransition transitions[]; // Only declare the array here

#endif // MENU_H
