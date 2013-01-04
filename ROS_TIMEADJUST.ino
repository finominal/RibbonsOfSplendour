
DateTime AdjustClockUp(DateTime timeToAdjust)
{
  
switch(SET_TIME_FOCUS){
  
  case eYear:
    timeToAdjust.yOff++;
    break;
    
  case eMonth:
   if(timeToAdjust.m == 12)
   {
     timeToAdjust.m = 1;
   }
   else
   {
    timeToAdjust.m++;
   }
   timeToAdjust = CheckMonthDateIsValid(timeToAdjust);
    break;
   
  case eDay:
     if(timeToAdjust.yOff % 4 == 0 && timeToAdjust.m == 2 && timeToAdjust.d == 28)//leapyear.
     {
       timeToAdjust.d++;
     }
   else if(timeToAdjust.yOff % 4 == 0 && timeToAdjust.m == 2 && timeToAdjust.d == 29)//leapyear completed.
     {
       timeToAdjust.d = 1; 
     }
   else if(timeToAdjust.yOff % 4 > 0 && timeToAdjust.m == 2 && timeToAdjust.d == 28)//Febuary
     {
       timeToAdjust.d = 1; 
     }
   else if((timeToAdjust.m == 4 || timeToAdjust.m == 6 || timeToAdjust.m == 9 || timeToAdjust.m == 11) && timeToAdjust.d == 30) //30 day months
     {
       timeToAdjust.d = 1;
     }
   else if((timeToAdjust.m == 1 || timeToAdjust.m == 3 || timeToAdjust.m == 5 || timeToAdjust.m == 7  || timeToAdjust.m == 8 || timeToAdjust.m == 10 || timeToAdjust.m == 12) && timeToAdjust.d == 31 ) //30 day months
      {
        timeToAdjust.d = 1;
     }
   else //defalt on an ordinary day
   {
     pl("up ++ ");
     timeToAdjust.d++;
   }
     break;
  case eHour:
      if(timeToAdjust.hh == 23)
      {
      timeToAdjust.hh = 0;
      }
      else 
      {
      timeToAdjust.hh++;
      }
    break;
  case eMinute:
        if(timeToAdjust.mm == 59)
      {
        timeToAdjust.mm = 0;
      }
      else
      {
      timeToAdjust.mm++;
      }
    break;
  }

return timeToAdjust;
}



DateTime AdjustClockDown(DateTime timeToAdjust)
{
  
switch(SET_TIME_FOCUS){
  
  case eYear:
    timeToAdjust.yOff--;
    break;
    
  case eMonth:
   if(timeToAdjust.m == 1)
   {
     timeToAdjust.m = 12;
   }
   else
   {
    timeToAdjust.m--;
   }
   timeToAdjust = CheckMonthDateIsValid(timeToAdjust);
    break;
    
  case eDay:
     if(timeToAdjust.yOff % 4 == 0 && timeToAdjust.m == 2 && timeToAdjust.d == 1)//leapyear.
     {
       timeToAdjust.d = 29;
     }
   else if(timeToAdjust.yOff % 4 > 0 && timeToAdjust.m == 2 && timeToAdjust.d == 1)//Febuary
     {
       timeToAdjust.d = 28; 
     }
   else if((timeToAdjust.m == 4 || timeToAdjust.m == 6 || timeToAdjust.m == 9 || timeToAdjust.m == 11) && timeToAdjust.d == 1) //30 day months
     {
       timeToAdjust.d = 30;
     }
   else if((timeToAdjust.m == 1 || timeToAdjust.m == 3 || timeToAdjust.m == 5 || timeToAdjust.m == 7  || timeToAdjust.m == 8 || timeToAdjust.m == 10 || timeToAdjust.m == 12) && timeToAdjust.d == 1 ) //30 day months
      {
        timeToAdjust.d = 31;
     }
   else //defalt on an ordinary day
   {
     timeToAdjust.d--;
   }
     break;
  case eHour:
      if(timeToAdjust.hh == 0)
      {
      timeToAdjust.hh = 23;
      }
      else
      {
      timeToAdjust.hh--;
      }
    break;
  case eMinute:
        if(timeToAdjust.mm == 0)
      {
        timeToAdjust.mm = 59;
      }
      else 
      {
      timeToAdjust.mm--;
      }
    break;
}

return timeToAdjust;
}



DateTime CheckMonthDateIsValid(DateTime timeToAdjust)
{
  //if a month is shifted where the date is greater than the months max date, this method will pull the date back to a normal date in that month.
     if(timeToAdjust.yOff % 4 == 0 && timeToAdjust.m == 2 && timeToAdjust.d > 29)//leapyear.
     {
       timeToAdjust.d = 29;
     }
   else if(timeToAdjust.yOff % 4 > 0 && timeToAdjust.m == 2 && timeToAdjust.d > 28)//Febuary
     {
       timeToAdjust.d = 28; 
     }
   else if((timeToAdjust.m == 4 || timeToAdjust.m == 6 || timeToAdjust.m == 9 || timeToAdjust.m == 11) && timeToAdjust.d > 30) //30 day months
     {
       timeToAdjust.d = 30;
     }
return timeToAdjust;
}

