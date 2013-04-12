#include <ROSDisplay.h>
#include <ROSRibbon.h>

#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <RTC_DS3234.h>
#include <LiquidCrystal.h>
//#include <ShiftStepper.h> //no clash with TIR
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
void UpdateLCDCountDownDisplay();
void SetTargetTime();
void SetGlobalTime();
void Countdown();
void InitializeClock();
void InitializeLCD();
void InitializeJoystick();
void JoystickLEFT();
void JoystickUP();
void JoystickDOWN();
void JoystickRIGHT();
void ClearJoystickBuffer();
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
  eBooting, eCountdown, eSetGlobalTime, eSetTargetTime, eCompleted, eParked};
enum RunningState {
  eStarting, eSynching, eRunning, eMoving, eZeroing, eTargetMet, eFinished};
enum RunningDisplayState {
  eGlobal, eTarget};
enum Joystick {
  eCentre, eUp, eDown, eLeft, eRight};
enum SetTimeFocus {
  eYear, eMonth, eDay, eHour, eMinute,eSecond};


//State Management
GlobalState GLOBAL_STATE;
RunningState RUNNING_STATE;
RunningDisplayState DISPLAY_STATE;
Joystick JOYSTICK_STATE; 
SetTimeFocus SET_TIME_FOCUS;
bool DEV_MODE;

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
DateTime nextDisplayTime;
Display displayTarget;
char lcdLine1[17];
char lcdLine2[17];
const float mainLoopDelayMS = 200;

//Ribbons
const int ribbonCount = 9;
Ribbon RIBBONS[ribbonCount];

//PWM 
int globalPWMCycle = 0;

//display helpers (for toggling what is on the display)
unsigned int cyclesSinceLastDisplayToggle;
const int displayToggleTimeSeconds = 5; //This valued determins how long the running display will toggle for.
const int displayToggleCycles = displayToggleTimeSeconds * 15; //the multiplier will change depending on the time to processing one loop of the sensors.
const int countDownPrepLeadTimeSeconds = 120;

//Sensor Management
const int SensorThreshold = 512;

//buffers for each phase of the PWMs.
byte LowMotorByte = 0;
byte HighMotorByte = 0;



void setup()
{  
  Serial.begin(115200);
  pl();
  pl("********ARDUINO RESTART*******");
  delay(10);
  
  InitializeRibbons();
  pl("Ribbon Objects Initialized");
  delay(10);
  InitializeInterruptPWM(); //PWM
  InitializeLCD();
  InitializeClock();
  InitializeJoystick();
  InitializeMuxes(); //sensors
  InitializeRibbons();
  InitializeDriverShieldPins();
  pl("InitializeAllComplete!");
  
  GLOBAL_STATE = eCountdown;
  RUNNING_STATE = eStarting;
  DISPLAY_STATE = eGlobal;
  DEV_MODE = true;

  //SetTargetTimeManually(); 
  pl();
  pl("Retrieving Saved Target Time");
  TargetTimeReadEeprom(); //get the stored target time out of non volitile storage.
  SerialDisplayTargetTime();
  GetGlobalTime();
  delay(1);//wait for clock 
  
  EnableTimerInteruptTwo();//Lastly, start interrupts!
}

void loop()
{
  TestRibbonMoveAndDisplay(2);
  TestTurnOnMotorsPWMCycle(0,0,0,0,0,0,0,0,0);

}

/*
void loop()
{
  pl();
  pl("Start Loop");
  //StateManagement
  if(GLOBAL_STATE == eCountdown) {
    pl();
    pl("~eCountdown");
    RunCountdownProgram();
  }
  else if (GLOBAL_STATE == eSetGlobalTime) {
    pl("~eSetGlobalTime");
    SetGlobalTime();
  }
  else if (GLOBAL_STATE == eSetTargetTime) {
    pl("~eSetTargetTime");
    SetTargetTime();
  }
  else if (GLOBAL_STATE == eCompleted)
  {
    pl("~eCompleted");
    MoveToZero();
    GLOBAL_STATE = eParked;
  }
  else if (GLOBAL_STATE == eParked)
  {
    pl("~eParked");
    UpdateLCDCountDownDisplay();
    CheckForNewCountDown();
  }
  else
  {
  pl("ERROR WITH MAIN LOOP - GLOBAL_STATE out of range."); 
  }
  
  delay(mainLoopDelayMS);
  
  //SerialDisplayDev();
  
}


*/







