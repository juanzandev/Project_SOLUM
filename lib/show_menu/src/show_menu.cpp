#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void initializeLCD()
{
    lcd.init();
    lcd.backlight();
}
void showMainMenu()
{
    initializeLCD();
    lcd.setCursor(0, 0);
    lcd.print("Sensor List");
    Serial.println("Sensor List");
    lcd.setCursor(0, 1);
    lcd.print("Add Sensor");
    Serial.println("Add Sensor");
    lcd.setCursor(0, 2);
    lcd.print("Remove Sensor");
    Serial.println("Remove Sensor");
    lcd.setCursor(0, 3);
    lcd.print("Settings");
    Serial.println("Settings");
}

// SENSOR LIST PATH
void showSensorListMenu()
{
    initializeLCD();
    lcd.setCursor(0, 0);
    lcd.print("Soil Moisture");
    Serial.println("Soil Moisture");
    lcd.setCursor(0, 1);
    lcd.print("Soil Temperature");
    Serial.println("Soil Temperature");
    lcd.setCursor(0, 2);
    lcd.print("Wind Speed");
    Serial.println("Wind Speed");
    lcd.setCursor(0, 3);
    lcd.print("Water Table");
    Serial.println("Water Table");
}
void showSensorList()
{
    Serial.println("[Sensor Name] 1");
    Serial.println("[Sensor Name] 2");
    Serial.println("[Sensor Name] 3");
    Serial.println("[Sensor Name] 4");
}
void showSensorConfig()
{
    Serial.println("Information");
    Serial.println("Configuration");
    Serial.println("Measurement Type");
    Serial.println("Take Measurement");
}

// ADD SENSOR PATH

void showSensorCategories()
{
    Serial.println("Soil Moisture");
    Serial.println("Soil Temperature");
    Serial.println("Wind Speed");
    Serial.println("Water Table");
}
void showSupportedSensor()
{
    Serial.println("[Supported Sensor Name] 1");
    Serial.println("[Supported Sensor Name] 1");
    Serial.println("[Supported Sensor Name] 1");
    Serial.println("[Supported Sensor Name] 1");
}
void showAddSensorOptions()
{
    Serial.println("Information");
    Serial.println("Set Up Instructions");
}
void showAddSensorSteps()
{
    // WIP
    Serial.println("Step 1....");
    delay(5000);
    Serial.println("Step 2....");
    delay(5000);
    Serial.println("Step 3....");
    delay(5000);
}
void showAddingSensor()
{
    Serial.println("Adding sensor");
    Serial.println("[Sensor Name]");
    Serial.println("and taking");
    Serial.println("a measurement...");
}
void showSuccessSensorAdd()
{
    Serial.println("Successfully added:");
    Serial.println("[Sensor Name]");
    Serial.println("MT: [Measurement Type]");
    Serial.println("Measurement: [Info]");
}
void showFailedSensorAdd()
{
    Serial.println("Could not add sensor");
    Serial.println("[Sensor Name]");
    Serial.println("Go to {Set Up");
    Serial.println("Instructions}");
}

// REMOVE SENSOR PATH

void showActiveSensors()
{
    Serial.println("[Active Sensor Name] 1");
    Serial.println("[Active Sensor Name] 2");
    Serial.println("[Active Sensor Name] 3");
    Serial.println("[Active Sensor Name] 4");
}

void showRemoveSensorConfirmation()
{
    Serial.println("Remove Sensor");
    Serial.println("[Sensor Name]");
    Serial.println("Yes");
    Serial.println("No");
}
void showSuccessSensorRemove()
{
    Serial.println("Successfully removed");
    Serial.println("[Sensor Name]");
}
void showCancelSensorRemove()
{
    Serial.println("Cancelled Removal");
    Serial.println("[Sensor Name]");
}

// SETTINGS PATH

void showSettingsMenu()
{
    Serial.println("Battery");
    Serial.println("Profiles");
    Serial.println("Connectivity");
    Serial.println("Node Location");
}
// BATTERY PATH
void showBatteryMenu()
{
    Serial.println("Battery Level xxx%");
    Serial.println("BatteryMode");
}
void showBatterySavingConfirmation()
{
    Serial.println("Warning: Battery Sav");
    Serial.println("Mode restricts the");
    Serial.println("amount of sensors");
    Serial.println("that can be used.");
    delay(5000);
    Serial.println("Activate Battery");
    Serial.println("Saving Mode?");
    Serial.println("Yes");
    Serial.println("No");
}
void showBatterySavingActivated()
{
    Serial.println("Battery Saving");
    Serial.println("has been activated.");
}
// PROFILES PATH
void showProfilesMenu()
{
    Serial.println("Create Profile");
    Serial.println("Delete Profile");
    Serial.println("Profile Options");
}

void showSavingProfile()
{
    Serial.println("Your current node");
    Serial.println("set up will be");
    Serial.println("stored in the");
    Serial.println("SD Card...");
}
void showProfileSaved()
{
    Serial.println("Profile saved in");
    Serial.println("SD Card as");
    Serial.println("saved_profile_x.csv");
}
void showDeleteProfileConfirmation()
{
    Serial.println("Your current node");
    Serial.println("set up will be");
    Serial.println("deleted...");
    delay(5000);
    Serial.println("Delete current");
    Serial.println("profile?");
    Serial.println("Yes");
    Serial.println("No");
}
void showDeletedProfile()
{
    Serial.println("Profile deleted.");
    Serial.println("[Current Profile]");
}
// PROFILE OPTIONS PATH
void showProfileOptionsMenu()
{
    Serial.println("Select Profile");
    Serial.println("Export Profile");
    Serial.println("Import Profile");
}
void showProfileList()
{
    Serial.println("Profile 1");
    Serial.println("Profile 2");
    Serial.println("Profile 3");
    Serial.println("Profile 4");
}
void showProfileSelected()
{
    Serial.println("Profile x has been");
    Serial.println("selected");
}

void showExportingProfile()
{
    Serial.println("Your current node");
    Serial.println("set up will be");
    Serial.println("stored in the");
    Serial.println("SD Card...");
}
void showProfileExported()
{
    Serial.println("Profile saved in");
    Serial.println("SD Card as");
    Serial.println("saved_profile_x.csv");
}
void showImportProfileInstructions()
{
    Serial.println("Add profile file");
    Serial.println("in the profile folder");
    Serial.println("in the SD Card");
    delay(5000);
    Serial.println("The file should be");
    Serial.println("called");
    Serial.println("\"profile_x.csv\"");
}
void showFoundProfileList()
{
    Serial.println("Multiple profiles");
    Serial.println("have been found...");
    Serial.println("Choose a profile");
    Serial.println("from the list...");
    delay(5000);
    Serial.println("profile_x.csv");
    Serial.println("profile_y.csv");
    Serial.println("profile_z.csv");
    Serial.println("profile_a.csv");
}
void showSingleProfileFoundConfirmation()
{
    Serial.println("Profile found!");
    Serial.println("Add [Profile Name]?");
    Serial.println("Yes");
    Serial.println("No");
}
void showMultipleProfileFoundConfirmation()
{
    Serial.println("Add [Profile Name]?");
    Serial.println("Yes");
    Serial.println("No");
}
void showImportedProfile()
{
    Serial.println("Profile");
    Serial.println("[Profile Name]");
    Serial.println("has been added!");
}

// CONNECTIVITY PATH
void showConnectivityMenu()
{
    Serial.println("Node Connection");
    Serial.println("Station Connection");
    Serial.println("Data Chip");
}

// NODE CONNECTION PATH
void showNodeConnectionMenu()
{
    Serial.println("Connect to Node");
    Serial.println("Disconnect from Node");
    Serial.println("Paired Nodes");
}

void showSearchingNodes()
{
    Serial.println("Searching nodes...");
}
void showNodesFound()
{
    // IF NO NODES FOUND
    Serial.println("No nodes were found.");
    Serial.println("Please try again and");
    Serial.println("make sure your node");
    Serial.println("is connected");
    // IF NODES FOUND
    Serial.println("[Node ID] 1");
    Serial.println("[Node ID] 2");
    Serial.println("[Node ID] 3");
    Serial.println("[Node ID] 4");
}

void showNodePairMenu()
{
    Serial.println("Node ID: [Node ID]");
    Serial.println("Location");
    Serial.println("Pair Node");
    Serial.println("Local ID: [Local]");
}
void showNodeLocationRequest()
{
    Serial.println("Requesting for");
    Serial.println("[Node ID]");
    Serial.println("location...");
    // IF SUCCESSFUL REQUEST
    Serial.println("Lat: --------");
    Serial.println("Long: -------");
    // IF FAILED REQUEST
    Serial.println("Failed to request");
    Serial.println("[Node ID]");
    Serial.println("location.");
}
void showPairNodeConfirmation()
{
    Serial.println("Pair with node");
    Serial.println("[Node ID]");
    Serial.println("Yes");
    Serial.println("No");
}
void showPairNode()
{
    // IF NODE PAIRING SUCCESSFUL
    Serial.println("Nodes Paired!");
    Serial.println("[Local ID]");
    Serial.println("paired with");
    Serial.println("[Node ID]");
    // IF FAILED PAIRING
    Serial.println("Could not pair with");
    Serial.println("[Node ID]. Try again");
    Serial.println("Yes");
    Serial.println("No");
}

// STATION CONNECTION PATH
void showStationConnectionMenu()
{
    Serial.println("Connect");
    Serial.println("Disconnect");
    Serial.println("Paired Stations");
}

void showSearchingForStations()
{
    Serial.println("Searching for");
    Serial.println("stations...");
}

void showStationsFound()
{
    // IF NO STATIONS FOUND
    Serial.println("No stations");
    Serial.println("found. Try again?");
    Serial.println("Yes");
    Serial.println("No");
    // IF STATIONS FOUND
    Serial.println("[Station ID] 1");
    Serial.println("[Station ID] 2");
    Serial.println("[Station ID] 3");
    Serial.println("[Station ID] 4");
}

void showConnectingStation()
{
    Serial.println("Connecting to");
    Serial.println("station");
    Serial.println("[Station ID]...");
}
void showStationConnected()
{
    // IF STATION CONNECTION SUCCESSFUL
    Serial.println("Successfully");
    Serial.println("connected");
    Serial.println("to station");
    Serial.println("[Station ID]");
    // IF STATION CONNECTION FAILED
    Serial.println("Connection failed");
    Serial.println("Try again?");
    Serial.println("Yes");
    Serial.println("No");
}

void showPairedStationsList()
{
    Serial.println("[Paired Station ID] 1");
    Serial.println("[Paired Station ID] 2");
    Serial.println("[Paired Station ID] 3");
    Serial.println("[Paired Station ID] 4");
}
void showStationDisconnectConfirmation()
{
    Serial.println("Disconnect from node");
    Serial.println("[Node ID]?");
    Serial.println("Yes");
    Serial.println("No");
}
void showDisconnectingStation()
{
    Serial.println("Disconnecting");
    Serial.println("from station");
    Serial.println("[Station ID]...");
}
void showStationDisconnected()
{
    // IF STATION DISCONNECTION SUCCESSFUL
    Serial.println("Successfully");
    Serial.println("disconnected");
    Serial.println("from station");
    Serial.println("[Station ID]");
}
void showStationMenu()
{
    Serial.println("[Station ID]");
    Serial.println("Configuration");
    Serial.println("Connected Nodes");
}

// DATA CHIP PATH

void showChipMenu()
{
    Serial.println("Chip: [Chip Company]");
    Serial.println("Check Internet");
}
void showCheckingInternet()
{
    Serial.println("Checking Internet");
    Serial.println("connection...");
}
void showInternetConnection()
{
    // IF CONNECTION SUCCESSFUL
    Serial.println("Successfully");
    Serial.println("connected to");
    Serial.println("the internet");

    // ELSE
    Serial.println("Failed to");
    Serial.println("connect to the");
    Serial.println("internet.");
}
