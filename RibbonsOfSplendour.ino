#include <ROSDisplay.h>

#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <RTC_DS3234.h>
#include <LiquidCrystal.h>
#include <ShiftStepper.h>
#include <EEPROM.h>

//Methods
void DevDisplay();
void SerialDisplayTargetTime();
void SerialDisplayGlobalTime();
void TargetTimeReadEeprom();
void TargetTimeWriteEeprom();
void LCDDisplayTargetTime();
void LCDDisplayGlobalTime();
void LCDDisplayGlobalTimeSet();
void GetGlobalTime();
void UpdateCountDownDisplay();
void SetTargetTime();
void SetGlobalTime();
void Countdown();
void InitializeClock();
void InitializeLCD();
void InitializeAtariJoystick();
void AtariJoystickLEFT();
void AtariJoystickUP();
void AtariJoystickDOWN();
void AtariJoystickRIGHT();
void ClearAtariJoystickBuffer();
void SerialDisplayDev();
void DisplayMoveTo(Display displayTarget);

//Helpers
#define p(x) Serial.print(x);
#define pl(x) Serial.println(x);

//Clock Chip CS
#define SPI_CS 53

//EEPROM Tartet Time Locations
#define eepTargetYear 4000
#define eepTargetMonth 4001
#define eepTargetDay 4002
#define eepTargetHour 4003
#define eepTargetMinute 4004
#define eepTargetSecond 4005



//Enumerators 
enum GlobalState {
  eBooting, eCountdown, eSetGlobalTime, eSetTargetTime};
enum RunningState {
  eStarting, ePreparing, eSynching, eRunning, eZeroing, eFinished};
enum RunningDisplayState {
  eGlobal, eTarget};
enum AtariJoystick {
  eCentre, eUp, eDown, eLeft, eRight};
enum SetTimeFocus {
  eYear, eMonth, eDay, eHour, eMinute,eSecond};


//State Management
GlobalState GLOBAL_STATE;
RunningState RUNNING_STATE;
RunningDisplayState DISPLAY_STATE;
AtariJoystick ATARI_JOYSTICK; 
SetTimeFocus SET_TIME_FOCUS;


//Declare Library Classes
RTC_DS3234 clock(SPI_CS);

LiquidCrystal lcd(34, 36, 38, 40, 42, 44);
// * LCD RS pin to digital pin 34
// * LCD Enable pin to digital pin 36
// * LCD D4 pin to digital pin 38
// * LCD D5 pin to digital pin 40
// * LCD D6 pin to digital pin 42
// * LCD D7 pin to digital pin 44
// * LCD R/W pin to ground
// http://www.halted.com/objects/catalog/product/extras/25549_22687_LCD%20GTC-1602.pdf


//Program Variables
DateTime globalTime; 
DateTime targetTime;
Display displayTarget;
char lcdLine1[17];
char lcdLine2[17];
const float mainLoopDelayMS = 200;
const int displayCharacterCount = 9;

//display helpers (for toggling what is on the display)
unsigned int cyclesSinceLastDisplayToggle;
const int displayToggleTimeSeconds = 5; //THis valued determins how long the running display will toggle for.
const int displayToggleCycles = displayToggleTimeSeconds * ( 1000 / mainLoopDelayMS); //calcuate cycles dynamically
const int DisplayLeadTimeSeconds = 180;





void setup()
{
  Serial.begin(57600);
  pl();
  pl("********ARDUINO RESTART*******");
  
  InitializeLCD();
  InitializeClock();
  InitializeAtariJoystick();
  InitializeCustomPWM();

  GLOBAL_STATE = eCountdown;
  RUNNING_STATE = eStarting;
  DISPLAY_STATE = eGlobal;

  //SetTargetTimeManually();
 
  pl("Getting Saved Target Time");

  TargetTimeReadEeprom(); //get the stored target time out of non volitile storage.
  SerialDisplayTargetTime();
  delay(100);
  
}





void loop()
{
  pl("Start Loop");

  //StateManagement
  if(GLOBAL_STATE == eCountdown) {
    Countdown();
  }
  else if (GLOBAL_STATE == eSetGlobalTime) {
    SetGlobalTime();
  }
  else if (GLOBAL_STATE == eSetTargetTime) {
    SetTargetTime();
  }

  delay(mainLoopDelayMS);
  pl();
  
  SerialDisplayDev();
}










