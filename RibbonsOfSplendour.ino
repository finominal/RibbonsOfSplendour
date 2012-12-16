#include <LiquidCrystal.h>

#include <Ds3234.h>
#include <SPI.h>
#include <ShiftStepper.h


#define CS 40 // CS pin for clock


enum GlobalState {eBooting, eCountdown, eSetGlobalTime, eSetTargetTime};
enum RunningState {eStarting, eRunning, eFinished};

GlobalState GLOBAL_STATE;
RunningState RUNNING_STATE;

Ds3234 clock(CS);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte year, month, date, ampm, hour, minute, sec;


//ds3234 clock(CS);

void setup()
{
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.print("Fluffy Light");
  lcd.setCursor(0, 1);
  lcd.print("Engineering");
  
  GLOBAL_STATE = eBooting;
  RUNNING_STATE = eStarting;
}

void loop()
{
if(GLOBAL_STATE == eCountdown) {Countdown();}
else if (GLOBAL_STATE == eSetGlobalTime) {SetGlobalTime();}
else if (GLOBAL_STATE == eSetTargetTime) {SetTargetTime();}
}

void Countdown()
{}

void SetGlobalTime()
{
  rtc.GetDate(year, month, date);
  rtc.GetTime(ampm, hour, minute, sec);
  //display Current Time on LCD
  
}

void SetTargetTime()
{}
