

void Countdown()
{
  pl("Countdown");
  
  GetGlobalTime();

  //MAIN PROCESSING
  //Perform Action based on current running state:
  if (RUNNING_STATE == eStarting)
  {
    pl("RunningState=eStarting");
    DetermineState();
  }
  else if (RUNNING_STATE == ePreparing)
  {
    pl("RunningState=ePreparing");
  }
   else if (RUNNING_STATE == eSynching)
  {
    pl("RunningState=eSynching");
  }
  else if (RUNNING_STATE == eRunning)
  {
    pl("RunningState=eRunning");
  }
  else if (RUNNING_STATE == eZeroing)
  {
    pl("RunningState=eZeroing");
    DisplayZeroCountdown();
    RUNNING_STATE = eFinished;
  }
  else if (RUNNING_STATE == eFinished)
  {
    pl("RunningState=eFinished");
    //do nothing
  }


  UpdateCountDownDisplay();
}

void DetermineState()
{
  if( globalTime.secondstime() + DisplayLeadTimeSeconds < targetTime.secondstime()  ) //if we are greater than lead time away from the end. (lead time is time to roll display and wait for sync)
  {
    RUNNING_STATE = ePreparing;
  }
  else 
  {
    RUNNING_STATE = eZeroing;
  }

}


void UpdateCountDownDisplay()
{
  //Update Display
  
  


    if(cyclesSinceLastDisplayToggle > displayToggleCycles)//Time to change display, uses a display state
  {
    pl("*Change Global Display - Update Timer");
    if(DISPLAY_STATE == eGlobal){
      DISPLAY_STATE=eTarget;
    }
    else{
      DISPLAY_STATE=eGlobal;
    }
    cyclesSinceLastDisplayToggle = 0; //reset the counter
  }

  pl("Updating CountDown Display");
  if(DISPLAY_STATE == eGlobal) {
    LCDDisplayGlobalTime();
  }
  else{
    LCDDisplayTargetTime();
  }

  cyclesSinceLastDisplayToggle++;
}

