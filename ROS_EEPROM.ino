void TargetTimeWriteEeprom()
{
  EEPROM.write(eepTargetYear,targetTime.yOff);
  EEPROM.write(eepTargetMonth,targetTime.m);
  EEPROM.write(eepTargetDay,targetTime.d);
  EEPROM.write(eepTargetHour,targetTime.hh);
  EEPROM.write(eepTargetMinute,targetTime.mm);
  EEPROM.write(eepTargetSecond,targetTime.ss);
}

void TargetTimeReadEeprom()
{
  targetTime = DateTime(
  EEPROM.read(eepTargetYear),
  EEPROM.read(eepTargetMonth),
  EEPROM.read(eepTargetDay),
  EEPROM.read(eepTargetHour),
  EEPROM.read(eepTargetMinute),
  EEPROM.read(eepTargetSecond));
}
