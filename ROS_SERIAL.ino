

void SerialDisplayGlobalState()
{
  p("GlobalState="); 
  switch(GLOBAL_STATE)
  {
    case 0:
      pl("eBooting");    
      break;
    case 1:
      pl("eCountdown");    
      break;
    case 2:
      pl("eSetGlobalTime");    
      break;
    case 3:
      pl("eSetTargetTime");    
      break;
    case 4:
      pl("eCompleted");
      break;
    case 5:
      pl("eParked");
      break;
  }
}  

void SerialDisplayRunningState()
{
  p("RunningState="); 
  switch(RUNNING_STATE)
  {
    case 0:
      pl("eStarting");    
      break;
    case 1:
      pl("eSynching");    
      break;
    case 2:
      pl("eRunning");    
      break;
    case 3:
      pl("eMoving");    
      break;
    case 4:
      pl("eZeroing");
      break;
    case 5:
      pl("eTargetMet");
      break;
    case 6:
      pl("eFinished");
      break;
  }
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

void SerialDisplayCountdownTime(Display disp)
{
   int bufLen = 12;
   char buf[bufLen];
   pl(disp.toString(buf, bufLen));
}
 
 void SerialDisplayAllRibbonPrimaryValues()
{
  pl();
  pl("DisplayAllRibbonSensorValues");
  for(int i = 0; i < ribbonCount; i++)
  {
    p("R"); p(i); p(" Current="); p(RIBBONS[i].currentDisplay); p(" Target="); pl(RIBBONS[i].targetDisplay); 
  }
  pl();
}
 
void SerialDisplayEeprom()
{
  p("eepTargetYear=");  pl(EEPROM.read(eepTargetYear));
  p("eepTargetMonth=");  pl( EEPROM.read(eepTargetMonth));
  p("eepTargetDay=");  pl(  EEPROM.read(eepTargetDay));
  p("eepTargetHour=");  pl(  EEPROM.read(eepTargetHour));
  p("eepTargetMinute=");  pl(  EEPROM.read(eepTargetMinute));
  p("eepTargetSecond=");  pl(  EEPROM.read(eepTargetSecond));
}

void SerialDisplayDev()
{
  SerialDisplayGlobalTime();
  SerialDisplayTargetTime();
  SerialDisplayEeprom();
}
