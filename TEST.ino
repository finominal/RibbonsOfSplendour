int counter  = 0; 


void  TestTurnOnMotorsPWMCycle(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)
{
  RIBBONS[0].pwmDuty = i0;
  RIBBONS[1].pwmDuty = i1;
  RIBBONS[2].pwmDuty = i2;
  RIBBONS[3].pwmDuty = i3;
  RIBBONS[4].pwmDuty = i4;
  RIBBONS[5].pwmDuty = i5;
  RIBBONS[6].pwmDuty = i6;
  RIBBONS[7].pwmDuty = i7;
  RIBBONS[8].pwmDuty = i8;
}

void TestRibbonMoveAndShowRaw(int idx, int pwmDuty)
{
  pl();
  pl("Loop");
    //dev
  int lastClock = 0;
  int lastData = 0;
  

  RIBBONS[idx].pwmDuty = pwmDuty;
  
  while(true)
  {
    RibbonSensorScanCycle_Itteration(idx); 
    //p(RIBBONS[idx].thisClockRead); p(" "); pl(RIBBONS[idx].thisDataRead);

    if(lastClock != RIBBONS[idx].thisClockRead || lastData != RIBBONS[idx].thisDataRead)
    {
      
      lastClock = RIBBONS[idx].thisClockRead;
      lastData = RIBBONS[idx].thisDataRead;
      
      lcd.clear();
       
      //Update Display
      //Line 1
      lcd.setCursor(0, 0);
      lcd.print("R"); lcd.print(idx); lcd.print(" ");
        
      //Line 2
       lcd.setCursor(0, 1); 
      lcd.print("c=");
      lcd.print(RIBBONS[idx].thisClockRead); 
      
      lcd.setCursor(5, 1); 
      lcd.print("d=");
      lcd.print(RIBBONS[idx].thisDataRead); 
    }
  }
  
}



void TestRibbonMoveAndDisplay(int idx, int pwmDuty)
{
  pl();
  pl("Loop");
    //dev
    
  int lastCharacterDetected = -1;
  int lastSensorDetectCycle = 0;
  RIBBONS[idx].pwmDuty = pwmDuty;
  long loopCounter = 0;
  long watchdog = 0; 
  long watchdogThreshold = 1300;

  while(true)
  {
    RibbonSensorScanCycle_Itteration(idx);
    
    //check for time change, and update display, sensorReadCycle will coincide with detected time.
    if(lastSensorDetectCycle != RIBBONS[idx].readSensorCycle) 
    {  
      lastSensorDetectCycle = RIBBONS[idx].readSensorCycle;
      UpdateDisplaySensorReadTest(idx);
      watchdog = 0; 
    }
    
    if( lastCharacterDetected != RIBBONS[idx].currentDisplay )
    {
      UpdateDisplaySensorReadTest(idx);
      RIBBONS[idx].pwmDuty = 0;//pause for a moment
      lastCharacterDetected = RIBBONS[idx].currentDisplay;
      
      p(loopCounter); p(","); pl(lastCharacterDetected);
      loopCounter++;
      
      delay(1000);
      RIBBONS[idx].pwmDuty = pwmDuty;//continue running
      
      watchdog = 0;
    }
    
    if(lastCharacterDetected == RIBBONS[idx].currentDisplay && lastSensorDetectCycle == RIBBONS[idx].readSensorCycle)
    {
      watchdog++;
    }
    
    if(watchdog >= watchdogThreshold)
    {
      Shutdown(idx);
    }
    delay(5);
  }
}

void Shutdown(int idx)
{
   RIBBONS[idx].pwmDuty = 0;
   p("SHUT DOWN AT "); pl(millis());
   while(true)
   {
       lcd.clear();

      //Update Display
      //Line 1
      lcd.setCursor(0, 0);
      lcd.print("ERROR:");
       lcd.setCursor(0, 1);
      lcd.print("Stuck Ribbon");
      delay(1000);
   }
}
  
void UpdateDisplaySensorReadTest(int idx)
{
  lcd.clear();
   
  //Update Display
  //Line 1
  lcd.setCursor(0, 0);
  lcd.print("R"); lcd.print(idx); lcd.print(" ");
  
  lcd.print( RIBBONS[idx].lastDetectedTime);
  lcd.setCursor(14, 0);
  lcd.print("c");
  lcd.print( RIBBONS[idx].readSensorCycle); 
    

  //Line 2
  lcd.setCursor(0, 1);
  lcd.print(RIBBONS[idx].currentDisplay); 
  
  lcd.setCursor(3, 1); 
  lcd.print("r");
  lcd.print(RIBBONS[idx].rawSensorData, DEC); 
  
  lcd.setCursor(7, 1);
  lcd.print("M");
  lcd.print(HighMotorByte, HEX);
  lcd.print(LowMotorByte, HEX);
  delay(5);
  //Yay
  }
  
