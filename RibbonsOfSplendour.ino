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
void LCDPrep();
void TargetTimeReadEeprom();
void TargetTimeWriteEeprom();
void LCDDisplayTargetTime();
void LCDDisplayGlobalTime();
void GetGlobalTime();
void UpdateCountDownDisplay();
void SetTargetTime();
void SetGlobalTime();
void Countdown();
void ClockInitialize();
void LCDInitialize();

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

enum GlobalState {eBooting, eCountdown, eSetGlobalTime, eSetTargetTime};
enum RunningState {eStarting, eRunning, eFinished};
enum DisplayState {eGlobal, eTarget};

GlobalState GLOBAL_STATE;
RunningState RUNNING_STATE;
DisplayState DISPLAY_STATE;

/*The circuit:
 * LCD RS pin to digital pin 12/34
 * LCD Enable pin to digital pin 11/36
 * LCD D4 pin to digital pin 5/38
 * LCD D5 pin to digital pin 4/40
 * LCD D6 pin to digital pin 3/42
 * LCD D7 pin to digital pin 2/44
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3) */

LiquidCrystal lcd(34, 36, 38, 40, 42, 44);

RTC_DS3234 clock(SPI_CS);

//PROGRAM VARIABLES
DateTime globalTime; 
DateTime targetTime;
char lcdLine1[17];
char lcdLine2[17];
unsigned int lastDisplayUpdate;
const int displayToggleTime = 5;//seconds
int mainLoopDelayMS = 200;






void setup()
{
  Serial.begin(57600);
  pl();
  pl("******Arduino Restart*******");
  
  LCDInitialize();
  ClockInitialize();
      
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
  TargetTimeReadEeprom();
  SerialDisplayTargetTime();
  
  lastDisplayUpdate = millis(); //Set the timer value for the display updates
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


//INITIALIZATION //INITIALIZATION //INITIALIZATION //INITIALIZATION //INITIALIZATION 
//INITIALIZATION //INITIALIZATION //INITIALIZATION //INITIALIZATION //INITIALIZATION 
//INITIALIZATION //INITIALIZATION //INITIALIZATION //INITIALIZATION //INITIALIZATION 

void LCDInitialize()
{
  pl("Initializing LCD");
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("FLUFFY LIGHT");
  lcd.setCursor(0, 1);
  lcd.print("ENGINEERING");
  pl("Initializing LCD OK");
  delay(3000);
}
void ClockInitialize()
{
  pl("Initializing Clock");
  pinMode(SPI_CS, OUTPUT);
  SPI.begin();
  //clock.begin();
  pl("Clock Initialized OK");
}




//ACTION MAIN STATES //ACTION MAIN STATES //ACTION MAIN STATES //ACTION MAIN STATES 
//ACTION MAIN STATES //ACTION MAIN STATES //ACTION MAIN STATES //ACTION MAIN STATES 
//ACTION MAIN STATES //ACTION MAIN STATES //ACTION MAIN STATES //ACTION MAIN STATES 

void Countdown()
{
  pl("Countdown");
  GetglobalTime();
  
  //Process
  
   UpdateCountDownDisplay();
}

void SetGlobalTime()
{
  pl("SetglobalTime");
}

void SetTargetTime()
{
  pl("SettargetTime");
}



//ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE 
//ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE 
//ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE 

void UpdateCountDownDisplay()
{
  //Update Display
  if(millis() < displayToggleTime*1000){lastDisplayUpdate = 0;} //Guard Clause to protect following from millis rollover
  
   if((millis()/1000) - lastDisplayUpdate > displayToggleTime)
   {
     pl("*Change Global Display - Update Timer");
     if(DISPLAY_STATE == eGlobal){DISPLAY_STATE=eTarget;}
     else{DISPLAY_STATE=eGlobal;}
     lastDisplayUpdate = (millis()/1000);
   }
   
   pl("Updating CountDown Display");
   if(DISPLAY_STATE == eGlobal) {LCDDisplayGlobalTime();}
   else{LCDDisplayTargetTime();}
}

void GetglobalTime()
{
  globalTime = clock.now();
}

void LCDDisplayGlobalTime()
{
  LCDPrep();
  
  char buf[21];
  globalTime.toString(buf,21);
  
  //Build the first LCD row  
  lcdLine1[0] = 'G';
  lcdLine1[1] = 'L';
  lcdLine1[2] = 'O';
  lcdLine1[3] = 'B';
  lcdLine1[4] = 'A';          
  lcdLine1[5] = 'L';  
  lcdLine1[6] = ':';
  lcdLine1[7] = ' ';
  lcdLine1[8] = buf[12];
  lcdLine1[9] = buf[13];
  lcdLine1[10] = buf[14];
  lcdLine1[11] = buf[15];
  lcdLine1[12] = buf[16];
  lcdLine1[13] = buf[17];
  lcdLine1[14] = buf[18];
  lcdLine1[15] = buf[19];
  lcdLine1[16] = buf[20];
  
  //Build the second  LCD row
  lcdLine2[5] = buf[0];
  lcdLine2[6] = buf[1];          
  lcdLine2[7] = buf[2];          
  lcdLine2[8] = buf[3];
  lcdLine2[9] = buf[4];
  lcdLine2[10] = buf[5];
  lcdLine2[11] = buf[6];
  lcdLine2[12] = buf[7];
  lcdLine2[13] = buf[8];
  lcdLine2[14] = buf[9];
  lcdLine2[15] = buf[10];
   
  //Update Display
  lcd.setCursor(0, 0);
  lcd.print(lcdLine1);
  lcd.setCursor(0, 1);
  lcd.print(lcdLine2);
}

void LCDDisplayTargetTime()
{
  LCDPrep();
  
  char buf[21];
  targetTime.toString(buf,21);
  
  //Build the first LCD row  
  lcdLine1[0] = 'T';
  lcdLine1[1] = 'A';
  lcdLine1[2] = 'R';
  lcdLine1[3] = 'G';
  lcdLine1[4] = 'E';          
  lcdLine1[5] = 'T';  
  lcdLine1[6] = ':';
  lcdLine1[7] = ' ';
  lcdLine1[8] = buf[12];
  lcdLine1[9] = buf[13];
  lcdLine1[10] = buf[14];
  lcdLine1[11] = buf[15];
  lcdLine1[12] = buf[16];
  lcdLine1[13] = buf[17];
  lcdLine1[14] = buf[18];
  lcdLine1[15] = buf[19];
  lcdLine1[16] = buf[20];
  
  //Build the second  LCD row
  lcdLine2[5] = buf[0];
  lcdLine2[6] = buf[1];          
  lcdLine2[7] = buf[2];          
  lcdLine2[8] = buf[3];
  lcdLine2[9] = buf[4];
  lcdLine2[10] = buf[5];
  lcdLine2[11] = buf[6];
  lcdLine2[12] = buf[7];
  lcdLine2[13] = buf[8];
  lcdLine2[14] = buf[9];
  lcdLine2[15] = buf[10];
   
  //Update Display
  lcd.setCursor(0, 0);
  lcd.print(lcdLine1);
  lcd.setCursor(0, 1);
  lcd.print(lcdLine2);
}

void TargetTimeWriteEeprom()
{
  EEPROM.write(eepTargetYear,targetTime.yOff);
  EEPROM.write(eepTargetMonth,targetTime.m);
  EEPROM.write(eepTargetDay,targetTime.d);
  EEPROM.write(eepTargetHour,targetTime.hh);
  EEPROM.write(eepTargetMinute,targetTime.mm);
  EEPROM.write(eepTargetSecond,targetTime.ss);
}

void TargetTimeReadEeprom()
{
  targetTime = DateTime(
  EEPROM.read(eepTargetYear),
  EEPROM.read(eepTargetMonth),
  EEPROM.read(eepTargetDay),
  EEPROM.read(eepTargetHour),
  EEPROM.read(eepTargetMinute),
  EEPROM.read(eepTargetSecond));
}

void LCDPrep()
{
  lcd.clear();
  
  for(int i = 0;i<16;i++)//clean the display characters
  {
    lcdLine1[i] = ' ';
    lcdLine2[i] = ' ';
  }
  
  lcdLine1[16] = '\0';
  lcdLine2[16] = '\0';
}

void SerialDisplayGlobalTime()
{
  //Show the current Time
  const int len = 21;
  static char buf[len];
  p("Global Time: ");
  Serial.println(globalTime.toString(buf,len));
}

void SerialDisplayTargetTime()
{
  //Show the current Time
  const int len = 21;
  static char buf[len];
  p("SRAM Target Time: ");
  Serial.println(targetTime.toString(buf,len));
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
