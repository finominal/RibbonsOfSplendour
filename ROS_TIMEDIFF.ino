
#define SecondsInDay 86400
#define SecondsInHour 3600
#define SecondsInMinute 60


Display CalculateCountDownDisplay(DateTime global, DateTime target)
{
  return ConvertSecondsToDisplay(target.secondstime() -  global.secondstime());
}
 
Display ConvertSecondsToDisplay(int seconds)
{
  Display result;                                                                                                                                                                                                                                                                                                           
  
  result.second = seconds % SecondsInMinute;
  seconds -= result.second;
  
  result.minute = (seconds % SecondsInHour) / SecondsInMinute;
  seconds -= result.minute;
  
  result.hour = (seconds % SecondsInDay) / SecondsInHour;
  seconds -= result.hour;
  
  result.day = seconds  / SecondsInDay;

  return result;
}  

DateTime TimeDiff_CalculateSyncDisplayTime()
{
  return  DateTime(globalTime.secondstime() +  countDownPrepLeadTimeSeconds);
}

DateTime TimeDiff_CalculateNextTargetTime()
{
  return  DateTime(globalTime.secondstime() +  1);
}

bool IsTimeDiffEnoughForCountDown()
{
  return  globalTime.secondstime() +  countDownPrepLeadTimeSeconds >  targetTime.secondstime();
}
