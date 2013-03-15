
#define clockSensorPin 15
#define dataSensorPin 14

//bool waitingForClockLow = false;
int sensorReadThresholdMs = 200;

    /*
    PERFORM A SENSOR READ CYCLE
    1. Check if timer expired, if so reset read cycle
    2. If just found a postive clock high, wait for it to go low 
    3. Read current Ribbon - both sensors
      3a. If first time finding positive edge, wait for second
      3b. If second positive clock, read data, set wait for clock low.
      3c. IF found positive, check if it was a fourth clock bit, and if so set the current known value in the ribbon object manager
    */

void RibbonSensorScanCycleItteration(int ribbonIdx)
{
  // 1. First, check to see if timeout has occured, if so reset. 
  if( HasTimeExpired ) //if too long has passed
  {
    RIBBONS[ribbonIdx].ResetSensorReadCycle(); //RibbonSensorCycle=0 and clear rawSensorData[]
  }
  else 
  {
    // 2. If waiting for clock low after finding an positive: 
    if(RIBBONS[ribbonIdx].waitingForClockLow)//if we are waiting for the clock to go low, meaning we just read the data...
    {
      WaitForClockLow(ribbonIdx);
    }
    else //***SCAN FOR A NEW RIBBON BIT****
    { 
      ScanForNextClockBit(ribbonIdx);// 2
    }
  }
}

bool HasTimeExpired(int ribbonIdx)
{
  // 1. need to accomodate for Millis() rollover each 9 hours.
  if ( millis() < RIBBONS[ribbonIdx].lastDetectedTime)
  {
    return (34359738 -  RIBBONS[ribbonIdx].lastDetectedTime + millis()) > sensorReadThresholdMs; 
  }
  return (millis() - RIBBONS[ribbonIdx].lastDetectedTime) > sensorReadThresholdMs;
}

void WaitForClockLow(int ribbonIdx)
{
  // 2. look for low edge on the clock, which completes the bit read 
  if(RIBBONS[ribbonIdx].lastClockRead == 1 && RIBBONS[ribbonIdx].thisClockRead == 0) 
  {
    RIBBONS[ribbonIdx].lastClockRead = RIBBONS[ribbonIdx].thisClockRead; 
  }
  // 2. look for low edge second read to ensure we have a solid value 
  else if(RIBBONS[ribbonIdx].lastClockRead == 0 && RIBBONS[ribbonIdx].thisClockRead == 0) 
  {
    RIBBONS[ribbonIdx].waitingForClockLow = false;
  }
}

void ScanForNextClockBit(int ribbonIdx)
{
  // 3. read the current ribbons clock and data, store results in RIBBON[] array
  ReadRibbonClockAndData(ribbonIdx);
  
  // 3a. Look for a high edge
  if(RIBBONS[ribbonIdx].thisClockRead == 1 && RIBBONS[ribbonIdx].lastClockRead == 0)
  {
    RIBBONS[ribbonIdx].lastClockRead = RIBBONS[ribbonIdx].thisClockRead; //just record the change for first detection    
  }
  // 3b. Look for a high edge second read to ensure solid value   
  else if( RIBBONS[ribbonIdx].thisClockRead == 1 && RIBBONS[ribbonIdx].lastClockRead == 1 )
  {
    // set appropriate veriables
    RIBBONS[ribbonIdx].rawSensorData |= RIBBONS[ribbonIdx].thisDataRead << RIBBONS[ribbonIdx].readSensorCycle;
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
    RIBBONS[ribbonIdx].currentdisplay = RIBBONS[ribbonIdx].rawSensorData;
    RIBBONS[ribbonIdx].readSensorCycle = 0;
    RIBBONS[ribbonIdx].rawSensorData = 0;
    RIBBONS[ribbonIdx].lastDetectedTime = millis();
  }
}

void ReadRibbonClockAndData(int i )
{
  SelectMuxSensor(i);
  RIBBONS[i].lastClockRead = ConvertMuxSensorRead(clockSensorPin);
  RIBBONS[i].lastDataRead = ConvertMuxSensorRead(dataSensorPin);
}

int  ConvertMuxSensorRead(int analogPin)
{
  return analogRead(clockSensorPin) > 512 ? 0 : 1; //sensor is inverted on analogue read
}

void SelectMuxSensor(int sensorNumber)
{
   PORTA = sensorNumber;
   PORTA = PORTA << 4;
   PORTA |= sensorNumber;
   delayMicroseconds(10);//wait for mux's to change POINT OF FAILURE!!!
}

void InitializeMuxes()
{
  pl("InitilaizeMuxes");
  DDRA = B11111111; //pins 22-29 output (port A) both MUXs are connected, 22-25,26-29
  PORTA = 0;
  pl("InitilaizeMuxes_OK!");
  delay(1000);
}
