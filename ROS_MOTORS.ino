#define DATPIN    11  
#define SCLPIN    13
#define LATPIN    7
#define MRPIN     8  
#define INDPIN    4

//buffers for each phase of the PWMs.
byte LowMotorByte = 0;
byte HighMotorByte = 0;

//ENTRY POINT
//Called By Timer Interrupt.
//Looks up global objects, and sets motors based on the objects variables ( PWM_Cycle )
void ItteratePWM()
{
    AdvanceGlobalPWMCycle();
    CalculateNextPWMBufferValues(); //motors
    PushTo4x4Shield(LowMotorByte, HighMotorByte); //motors
}

void AdvanceGlobalPWMCycle()
{
  globalPWMCycle = globalPWMCycle++ % 4;
}

void CalculateNextPWMBufferValues()
{
  //reset the motor buffers
  LowMotorByte = 0; 
  HighMotorByte = 0;

  //loop through each motor/ribbon
  for(int idx = 0; idx<ribbonCount; idx++)
  {
     //Set the masks based on the current motor/ribbon
    byte lowMask = 0;
    byte highMask = 0;
    if(idx <=7) 
    {
      lowMask = 1 << idx;
    }
    else
    {
      highMask = 1 << idx % 8;
    }
      
    //set the motors based on the current pwmCycle and ribbon duty
    if(RIBBONS[idx].pwmDuty > globalPWMCycle) 
    {
      LowMotorByte = LowMotorByte | lowMask;
      HighMotorByte = HighMotorByte | highMask;
    }
  }
}


void PushTo4x4Shield(byte lowbyte, byte highbyte)
{
  digitalWrite(LATPIN, LOW); // Prepares latch 
  digitalWrite(MRPIN,HIGH);
  shiftOut(11, 13, MSBFIRST, highbyte); // shift data for OUT8-OUT15
  shiftOut(11, 13, MSBFIRST, lowbyte); // shift data for OUT0-OUT7
  digitalWrite(LATPIN, HIGH); // latch 
}



void InitializeDriverShieldPins()
{
  pinMode(DATPIN,OUTPUT);
  pinMode(SCLPIN,OUTPUT);
  pinMode(LATPIN,OUTPUT);
  pinMode(MRPIN,OUTPUT);
  pinMode(INDPIN,INPUT);
  
  digitalWrite(MRPIN, HIGH);// Deactivates master reset
}


