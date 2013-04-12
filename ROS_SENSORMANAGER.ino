
#define clockSensorPin 15
#define dataSensorPin 14

//bool waitingForClockLow = false;
int sensorReadThresholdMs = 1000;

    /*
    PERFORM A SENSOR READ CYCLE
    1. Check if timer expired, if so reset read cycle
    2. If just found a postive clock high, wait for it to go low 
    3. Read current Ribbon - both sensors
      3a. If first time finding positive edge, wait for second
      3b. If second positive clock, read data, set wait for clock low.
      3c. IF found positive, check if it was a fourth clock bit, and if so set the current known value in the ribbon object manager
    */
    
void InitializeMuxes()
{
  pl("Initilaize Muxes");
  DDRA = B11111111; //pins 22-29 output (port A) both MUXs are connected, 22-25,26-29
  PORTA = 0;
  pl("Initilaize Muxes OK");
}

void SensorManager_AllSensorsScanItteration()
{
  for(int i = 0; i < ribbonCount; i++)
  {
    RibbonSensorScanCycle_Itteration(i);
  }
}

void RibbonSensorScanCycle_Itteration(int ribbonIdx)
{
  // 1. First, check to see if timeout has occured, if so reset. 
  if( HasTimeoutExpired(ribbonIdx) ) //if too long has passed
  {
    RIBBONS[ribbonIdx].ResetSensorReadCycle(); //RibbonSensorCycle=0 and clear rawSensorData[]
    p("Reset Sensor Cycle - "); pl(ribbonIdx); 
  }
  else 
  {
    // 2. If waiting for clock low after finding an positive: 
    if(RIBBONS[ribbonIdx].waitingForClockLow)//if we are waiting for the clock to go low, meaning we just read the data...
    {
      pl("Waiting");
      WaitForClockLow(ribbonIdx);
    }
    else //***SCAN FOR A NEW RIBBON BIT****
    { 
      ScanForNextClockBit(ribbonIdx);// 2
    }
  }
}

void PrepareSensors()
{
  //get the current starting time of millis so a valid reset time is used.
  long mil = millis();
  for(int i = 0; i<ribbonCount;i++)
  {
    RIBBONS[i].lastDetectedTime = mil;
  }
}

bool HasTimeoutExpired(int ribbonIdx)
{
  // 1. need to accomodate for Millis() rollover each 9 hours.
  long mil = millis();
  if (mil < RIBBONS[ribbonIdx].lastDetectedTime)
  {
    return  RIBBONS[ribbonIdx].readSensorCycle > 0 && ((34359738 -  RIBBONS[ribbonIdx].lastDetectedTime + mil) > sensorReadThresholdMs) ; ;
  }
  //p("mil="); pl( mil ); 
  //p("LastDetected="); pl(RIBBONS[ribbonIdx].lastDetectedTime); 
  //p("sensorReadThresholdMs=");  pl(sensorReadThresholdMs);
  return RIBBONS[ribbonIdx].readSensorCycle > 0 && ((mil - RIBBONS[ribbonIdx].lastDetectedTime) > sensorReadThresholdMs);;
}

void WaitForClockLow(int ribbonIdx)
{
  ReadRibbonClockAndData(ribbonIdx);
  // 2. look for low edge on the clock, which completes the bit read 
  if(RIBBONS[ribbonIdx].lastClockRead == 1 && RIBBONS[ribbonIdx].thisClockRead == 0) 
  {
    RIBBONS[ribbonIdx].lastClockRead = RIBBONS[ribbonIdx].thisClockRead; 
  }
  // 2. look for low edge second read to ensure we have a solid value 
  else if(RIBBONS[ribbonIdx].lastClockRead == 0 && RIBBONS[ribbonIdx].thisClockRead == 0) 
  {
    RIBBONS[ribbonIdx].waitingForClockLow = false;
    pl("ClockLowFound");
  }
}

void ScanForNextClockBit(int ribbonIdx)
{
  //p("ScnSen"); p(ribbonIdx);p(" cyc="); pl(RIBBONS[ribbonIdx].readSensorCycle)
  // 3. read the current ribbons clock and data, store results in RIBBON[] array
  ReadRibbonClockAndData(ribbonIdx);
  //p("idx ");p(ribbonIdx);p(" C="); p(RIBBONS[ribbonIdx].thisClockRead); p(" d="); pl(RIBBONS[ribbonIdx].thisDataRead);
  //p("LC=");p(RIBBONS[ribbonIdx].lastClockRead); p(" LD=");pl(RIBBONS[ribbonIdx].lastDataRead);

  // 3a. Look for a high edge
  if(RIBBONS[ribbonIdx].thisClockRead == 1 && RIBBONS[ribbonIdx].lastClockRead == 0)
  {
    //pl("SetLastClockRead");
    RIBBONS[ribbonIdx].lastClockRead = RIBBONS[ribbonIdx].thisClockRead; //just record the change for first detection    
  }
  // 3b. Look for a high edge second read to ensure solid value   
  else if( RIBBONS[ribbonIdx].thisClockRead == 1 && RIBBONS[ribbonIdx].lastClockRead == 1 )
  {
    //p("SetRawSensorData - Cycle=");    pl(RIBBONS[ribbonIdx].readSensorCycle);

    // set appropriate veriables
    RIBBONS[ribbonIdx].rawSensorData |= RIBBONS[ribbonIdx].thisDataRead <<  RIBBONS[ribbonIdx].readSensorCycle ;  //Three minuse, because we must read the ribbon Binary in reverse, Was manufactured for rolling UP not DOWN.
    RIBBONS[ribbonIdx].lastDetectedTime = millis();
    RIBBONS[ribbonIdx].waitingForClockLow = true;
    RIBBONS[ribbonIdx].readSensorCycle++;

    CheckForCompletedSensorReadCycle( ribbonIdx);
  }
}

void CheckForCompletedSensorReadCycle(int ribbonIdx)
{
  // 3c Check if read cycle complete
  if(RIBBONS[ribbonIdx].readSensorCycle == 4)
  {
    //pl("ReadSenCycFinish")
    RIBBONS[ribbonIdx].currentDisplay = RIBBONS[ribbonIdx].rawSensorData;
    RIBBONS[ribbonIdx].readSensorCycle = 0;
    RIBBONS[ribbonIdx].rawSensorData = 0;
    RIBBONS[ribbonIdx].lastDetectedTime = millis();
  }
}

void ReadRibbonClockAndData(int i )
{
  SelectMuxSensor(i);
  RIBBONS[i].thisClockRead = MuxSensorRead(clockSensorPin);
  
  //broken physical channel 8 on data mux, have to use idx 9
  if(i==8) {RIBBONS[9].thisDataRead = MuxSensorRead(dataSensorPin);}
  else {RIBBONS[i].thisDataRead = MuxSensorRead(dataSensorPin);}
  
  
}

int MuxSensorRead(int analogPin)
{
  //convert the analog read to bit
  return analogRead(analogPin) > 512 ? 0 : 1;; //sensor is inverted on analogue read
}

void SelectMuxSensor(int sensorNumber)
{
   PORTA = sensorNumber;
   PORTA = PORTA << 4;
   PORTA |= sensorNumber;
   delayMicroseconds(10);//wait for mux's to change POINT OF FAILURE!!!
}




