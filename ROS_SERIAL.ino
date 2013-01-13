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
