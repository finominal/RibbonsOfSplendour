#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <RTC_DS3234.h>
#include <LiquidCrystal.h>
#include <ShiftStepper.h>
#include <EEPROM.h>


#define p(x) Serial.print(x);
#define pl(x) Serial.println(x);
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

GlobalState GLOBAL_STATE;
RunningState RUNNING_STATE;

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
DateTime GlobalTime; 
DateTime TargetTime;
char LCDLine1[17];
char LCDLine2[17];


void setup()
{
  Serial.begin(57600);
  Serial.println("******Arduino Restart*******");
  
  LCDInitialize();
  ClockInitialize();
      
  GLOBAL_STATE = eCountdown;
  RUNNING_STATE = eStarting;
  
  //SET GLOBAL TIME to PC time (time snapshot written as constants into progmem)
  //clock.adjust(DateTime(__DATE__, __TIME__));
  
//  //SET TARGET TIME
//  pl("Setting Target Time")
//  TargetTime = DateTime(13, 01, 10, 17, 0, 0);
//  TargetTimeWriteEeprom();
  
  pl("Getting Saved Target Time");
  TargetTimeReadEeprom();
  SerialDisplayTargetTime();
}

void loop()
{
  pl("Start Loop");
  
  //StateManagement
  if(GLOBAL_STATE == eCountdown) {Countdown();}
  else if (GLOBAL_STATE == eSetGlobalTime) {SetGlobalTime();}
  else if (GLOBAL_STATE == eSetTargetTime) {SetTargetTime();}
  
  DevDisplay();
  
  delay(100);
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
  GetGlobalTime();
  //Process
  LCDDisplayTargetTime();
}

void SetGlobalTime()
{
  pl("SetGlobalTime");
}

void SetTargetTime()
{
  pl("SetTargetTime");
}



//ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE 
//ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE 
//ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE //ACTION CODE 

void GetGlobalTime()
{
  GlobalTime = clock.now();
}

void LCDDisplayGlobalTime()
{
  LCDPrep();
  
  char buf[21];
  GlobalTime.toString(buf,21);
  
  //Build the first LCD row  
  LCDLine1[0] = 'G';
  LCDLine1[1] = 'L';
  LCDLine1[2] = 'O';
  LCDLine1[3] = 'B';
  LCDLine1[4] = 'A';          
  LCDLine1[5] = 'L';  
  LCDLine1[6] = ':';
  LCDLine1[7] = ' ';
  LCDLine1[8] = buf[12];
  LCDLine1[9] = buf[13];
  LCDLine1[10] = buf[14];
  LCDLine1[11] = buf[15];
  LCDLine1[12] = buf[16];
  LCDLine1[13] = buf[17];
  LCDLine1[14] = buf[18];
  LCDLine1[15] = buf[19];
  LCDLine1[16] = buf[20];
  
  //Build the second  LCD row
  LCDLine2[5] = buf[0];
  LCDLine2[6] = buf[1];          
  LCDLine2[7] = buf[2];          
  LCDLine2[8] = buf[3];
  LCDLine2[9] = buf[4];
  LCDLine2[10] = buf[5];
  LCDLine2[11] = buf[6];
  LCDLine2[12] = buf[7];
  LCDLine2[13] = buf[8];
  LCDLine2[14] = buf[9];
  LCDLine2[15] = buf[10];
   
  //Update Display
  lcd.setCursor(0, 0);
  lcd.print(LCDLine1);
  lcd.setCursor(0, 1);
  lcd.print(LCDLine2);
}

void LCDDisplayTargetTime()
{
  LCDPrep();
  
  char buf[21];
  TargetTime.toString(buf,21);
  
  //Build the first LCD row  
  LCDLine1[0] = 'T';
  LCDLine1[1] = 'A';
  LCDLine1[2] = 'R';
  LCDLine1[3] = 'G';
  LCDLine1[4] = 'E';          
  LCDLine1[5] = 'T';  
  LCDLine1[6] = ':';
  LCDLine1[7] = ' ';
  LCDLine1[8] = buf[12];
  LCDLine1[9] = buf[13];
  LCDLine1[10] = buf[14];
  LCDLine1[11] = buf[15];
  LCDLine1[12] = buf[16];
  LCDLine1[13] = buf[17];
  LCDLine1[14] = buf[18];
  LCDLine1[15] = buf[19];
  LCDLine1[16] = buf[20];
  
  //Build the second  LCD row
  LCDLine2[5] = buf[0];
  LCDLine2[6] = buf[1];          
  LCDLine2[7] = buf[2];          
  LCDLine2[8] = buf[3];
  LCDLine2[9] = buf[4];
  LCDLine2[10] = buf[5];
  LCDLine2[11] = buf[6];
  LCDLine2[12] = buf[7];
  LCDLine2[13] = buf[8];
  LCDLine2[14] = buf[9];
  LCDLine2[15] = buf[10];
   
  //Update Display
  lcd.setCursor(0, 0);
  lcd.print(LCDLine1);
  lcd.setCursor(0, 1);
  lcd.print(LCDLine2);
}

void TargetTimeWriteEeprom()
{
  EEPROM.write(eepTargetYear,TargetTime.yOff);
  EEPROM.write(eepTargetMonth,TargetTime.m);
  EEPROM.write(eepTargetDay,TargetTime.d);
  EEPROM.write(eepTargetHour,TargetTime.hh);
  EEPROM.write(eepTargetMinute,TargetTime.mm);
  EEPROM.write(eepTargetSecond,TargetTime.ss);
}

void TargetTimeReadEeprom()
{
  TargetTime = DateTime(
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
    LCDLine1[i] = ' ';
    LCDLine2[i] = ' ';
  }
  
  LCDLine1[16] = '\0';
  LCDLine2[16] = '\0';
}

void SerialDisplayGlobalTime()
{
  //Show the current Time
  const int len = 21;
  static char buf[len];
  p("Global Time: ");
  Serial.println(GlobalTime.toString(buf,len));
}

void SerialDisplayTargetTime()
{
  //Show the current Time
  const int len = 21;
  static char buf[len];
  p("SRAM Target Time: ");
  Serial.println(TargetTime.toString(buf,len));
}

void DevDisplay()
{
   SerialDisplayGlobalTime();
  
//  //Show EEPROM data
//  Serial.println(EEPROM.read(Tyear));
//  Serial.println(EEPROM.read(Tmonth));
//  Serial.println(EEPROM.read(Tday));
//  Serial.println(EEPROM.read(Thour));
//  Serial.println(EEPROM.read(Tminute));
//  Serial.println(EEPROM.read(Tsecond));
}
