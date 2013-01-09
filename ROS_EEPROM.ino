void TargetTimeWriteEeprom()
{
  EEPROM.write(eepTargetYear,targetTime.year());
  EEPROM.write(eepTargetMonth,targetTime.month());
  EEPROM.write(eepTargetDay,targetTime.day());
  EEPROM.write(eepTargetHour,targetTime.hour());
  EEPROM.write(eepTargetMinute,targetTime.minute());
  EEPROM.write(eepTargetSecond,targetTime.second());
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
