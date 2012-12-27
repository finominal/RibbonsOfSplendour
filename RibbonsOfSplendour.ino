#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <RTC_DS3234.h>
#include <LiquidCrystal.h>
#include <ShiftStepper.h>


#define p(x) Serial.print(x);
#define pl(x) Serial.println(x);
#define SPI_CS 53

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
 
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(34, 36, 38, 40, 42, 44);
RTC_DS3234 clock(SPI_CS);

//PROGRAM VARIABLES
DateTime GlobalTime; 
DateTime TargetTime;



void setup()
{
  Serial.begin(57600);
  Serial.println("******Arduino Restart*******");
  
  LCDInitialize();
  ClockInitialize();
      
  GLOBAL_STATE = eCountdown;
  RUNNING_STATE = eStarting;
  
  //Set Clock to PC time, SNAPSHOT AT UPLOAD TIME
  //clock.adjust(DateTime(__DATE__, __TIME__));
}

void loop()
{
  pl("Start Loop");
  
  //StateManagement
  if(GLOBAL_STATE == eCountdown) {Countdown();}
  else if (GLOBAL_STATE == eSetGlobalTime) {SetGlobalTime();}
  else if (GLOBAL_STATE == eSetTargetTime) {SetTargetTime();}
  
  DevDisplay();
  
  delay(1000);
}

void LCDInitialize()
{
  pl("Initializing LCD");
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Fluffy Light");
  lcd.setCursor(0, 1);
  lcd.print("Engineering");
  pl("Initializing LCD OK");
}
void ClockInitialize()
{
  pl("Initializing Clock");
  pinMode(SPI_CS, OUTPUT);
  SPI.begin();
  clock.begin();
  pl("Clock Initialized OK");
}

void Countdown()
{
  pl("Countdown");
}

void SetGlobalTime()
{
  pl("SetGlobalTime");
}

void SetTargetTime()
{
    pl("SetTargetTime");
}

void GetGlobalTime()
{
  GlobalTime = clock.now();
}

void DevDisplay()
{
  //Show the current Time
  const int len = 32;
  static char buf[len];
  Serial.println(GlobalTime.toString(buf,len));


}
