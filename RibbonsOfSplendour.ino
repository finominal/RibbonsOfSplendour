

#include <SplendourClock.h>
#include <LiquidCrystal.h>
#include <ShiftStepper.h>


enum GlobalState {eBooting, eCountdown, eSetGlobalTime, eSetTargetTime};
enum RunningState {eStarting, eRunning, eFinished};


GlobalState GLOBAL_STATE;
RunningState RUNNING_STATE;


SplendourClock clockManager;

/*The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3) */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup()
{
    Serial.begin(9600);
    
    // set up the LCD's number of columns and rows: 
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Fluffy Light");
    lcd.setCursor(0, 1);
    lcd.print("Engineering");
    //SplendourClock::SplendourClock(11);

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
{
  
}

void SetGlobalTime()
{
  
}

void SetTargetTime()
{}

//Joystick button handler
/*
//state based decision - INTERRUPT ON
If(GLOBAL_STATE == Running)
{
//Turn off FireButton INTERRUPT
//Set GLOBAL_STATE to eSetGlobalTime
}

*/
