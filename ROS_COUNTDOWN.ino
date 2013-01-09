

void Countdown()
{
  pl("Countdown");
  GetGlobalTime();

  //Process

  UpdateCountDownDisplay();
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

