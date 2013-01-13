
#define SecondsInDay 86400
#define SecondsInHour 3600
#define SecondsInMinute 60


Display CalculateCountdownTime(DateTime global, DateTime target)
{
  int long  difference;
  difference = target.secondstime() -  global.secondstime();
  return SecondsToDateTime(difference);
}
 
Display SecondsToDateTime(long seconds)
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
