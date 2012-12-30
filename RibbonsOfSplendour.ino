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

//Helpers
#define p(x) Serial.print(x);
#define pl(x) Serial.println(x);

//Clock Chip CS
#define SPI_CS 53

//EEPROM Tartet Time Locations
#define eepTargetYear 4000 //2000 and ...
#define eepTargetMonth 4001
#define eepTargetDay 4002
#define eepTargetHour 4003
#define eepTargetMinute 4004
#define eepTargetSecond 4005


//Enumerators 
enum GlobalState {eBooting, eCountdown, eSetGlobalTime, eSetTargetTime};
enum RunningState {eStarting, eRunning, eFinished};
enum RunningDisplayState {eGlobal, eTarget};
enum AtariJoystick {eCentre, eUp, eDown, eLeft, eRight};
enum SetTimeFocus {eYear, eMonth, eDay, eHour, eMinute};


//State Management
GlobalState GLOBAL_STATE;
RunningState RUNNING_STATE;
RunningDisplayState DISPLAY_STATE;
AtariJoystick ATARI_JOYSTICK; 
SetTimeFocus SET_TIME_FOCUS;


//Declare Library Classes
LiquidCrystal lcd(34, 36, 38, 40, 42, 44);
RTC_DS3234 clock(SPI_CS);

//Program Variables
DateTime globalTime; 
DateTime targetTime;
char lcdLine1[17];
char lcdLine2[17];
unsigned int cyclesSinceLastDisplayToggle;
const float mainLoopDelayMS = 200;
const int displayToggleTimeSeconds = 5; //THis valued determins how long the running display will toggle for.
int displayToggleCycles = displayToggleTimeSeconds * ( 1000 / mainLoopDelayMS); //calcuate cycles dynamically


//Custom Font
byte underscore[8] = {
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};





void setup()
{
  Serial.begin(57600);
  pl();
  pl("******Arduino Restart*******");
  
  InitializeLCD();
  InitializeClock();
  InitializeAtariJoystick();
      
  GLOBAL_STATE = eCountdown;
  RUNNING_STATE = eStarting;
  DISPLAY_STATE = eGlobal;
  
  
//  //SET GLOBAL TIME to PC time (time snapshot written as constants into progmem)
//  clock.adjust(DateTime(__DATE__, __TIME__));

//  //SET TARGET TIME
//  pl("Setting Target Time")
//  targetTime = DateTime(13, 01, 8, 17, 0, 0);
//  TargetTimeWriteEeprom();
  
  pl("Getting Saved Target Time");
  TargetTimeReadEeprom(); //get the stored target time out of non volitile storage.
  SerialDisplayTargetTime();
  delay(1000);

}


void loop()
{
  pl("Start Loop");

  //StateManagement
  if(GLOBAL_STATE == eCountdown) {Countdown();}
  else if (GLOBAL_STATE == eSetGlobalTime) {SetGlobalTime();}
  else if (GLOBAL_STATE == eSetTargetTime) {SetTargetTime();}
  
  //DevDisplay();
  
  delay(mainLoopDelayMS);
  pl();
}









//ACTION MAIN STATES //ACTION MAIN STATES //ACTION MAIN STATES //ACTION MAIN STATES 
//ACTION MAIN STATES //ACTION MAIN STATES //ACTION MAIN STATES //ACTION MAIN STATES 
//ACTION MAIN STATES //ACTION MAIN STATES //ACTION MAIN STATES //ACTION MAIN STATES 



 
 void Countdown()
{
  pl("Countdown");
  GetGlobalTime();
  
  //Process
  
   UpdateCountDownDisplay();
}

void SetGlobalTime()
{
  pl("Enter SetGLobalTime");

  
  //NEED TO IMPLEMENT CURSOR HERE 
  while (ATARI_JOYSTICK == eCentre && GLOBAL_STATE == eSetGlobalTime) //wait for input
    {
        pl("Waiting For Input Loop");
        
        //Display The current Global Time
        lcd.clear();
        GetGlobalTime();
        LCDDisplayGlobalTimeSet();
        
        //Set the cursor to the first position
        SetCursorPositionForSetTimeFocus();
        lcd.blink();
        delay(mainLoopDelayMS);
    }
    
    lcd.clear();
    
  pl("SetGLobalTime - Post While Loop");
  switch(ATARI_JOYSTICK) {
  case eLeft:
    lcd.print("Left");
    delay(500);
    ClearAtariJoystickBuffer();
    break;
  case eRight:
    lcd.print("RIght");
    delay(500);
    ClearAtariJoystickBuffer();
    break;
  case eUp:
    globalTime = AdjustClockUp(globalTime);
    clock.adjust(globalTime);
    ClearAtariJoystickBuffer();
    break;
  case eDown:
    globalTime = AdjustClockDown(globalTime);
    clock.adjust(globalTime);
    ClearAtariJoystickBuffer();
    break;
  }

}


void SetTargetTime()
{
  lcd.clear();
  lcd.print("Setting Target");
}









//ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE 
//ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE 
//ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE 


void UpdateTimeWithJoystick()
{
  
   
  switch (SET_TIME_FOCUS) {
    case eYear:
      
      break;
    case eMonth:
      
      break;
     case eDay:
      
      break;
     case eHour:
       
      break;
     case eMinute:
      
      break;
  }
}




void UpdateCountDownDisplay()
{
  //Update Display

   if(cyclesSinceLastDisplayToggle > displayToggleCycles)//Time to change display, uses a display state
   {
     pl("*Change Global Display - Update Timer");
     if(DISPLAY_STATE == eGlobal){DISPLAY_STATE=eTarget;}
     else{DISPLAY_STATE=eGlobal;}
     cyclesSinceLastDisplayToggle = 0; //reset the counter
   }
   
   pl("Updating CountDown Display");
   if(DISPLAY_STATE == eGlobal) {LCDDisplayGlobalTime();}
   else{LCDDisplayTargetTime();}
   
   cyclesSinceLastDisplayToggle++;
}




void SerialDisplayGlobalTime()
{
  //Show the current Time
  const int len = 21;
  static char buf[len];
  p("Global Time: ");
  pl(globalTime.toString(buf,len));
}

void SerialDisplayTargetTime()
{
  //Show the current Time
  const int len = 21;
  static char buf[len];
  p("SRAM Target Time: ");
  pl(targetTime.toString(buf,len));
}

void DevDisplay()
{
   LCDDisplayGlobalTime();
  
//  //Show EEPROM data
//  Serial.println(EEPROM.read(Tyear));
//  Serial.println(EEPROM.read(Tmonth));
//  Serial.println(EEPROM.read(Tday));
//  Serial.println(EEPROM.read(Thour));
//  Serial.println(EEPROM.read(Tminute));
//  Serial.println(EEPROM.read(Tsecond));
}
