void RunCountdownProgram()
{
  
  while(GLOBAL_STATE == eCountdown)
  {
    UpdateLCDCountDownDisplay();
    SetDisplayTargetTime(); 
    UpdateRibbonTargets();
    MoveToTarget();
    CheckForCompletion(); //will change GLOBAL_STATE to exit this loop
  }
}

void SetDisplayTargetTime()
{
  //SHIT!
}

void UpdateRibbonTargets()
{
  
  RUNNING_STATE = eMoving;
}

void MoveToTarget()
{
  while(RUNNING_STATE == eMoving)
  {
    UpdatePWMs();
    CheckForTargetMet();
  }
}

void CheckForCompletion()
{
  if(targetTime.secondstime() <  globalTime.secondstime())
  {
    GLOBAL_STATE = eCompleted;
  }
}


void UpdatePWMs()
{
   for(int i = 0; i < ribbonCount; i++)
  {
    if(RIBBONS[i].targetDisplay == RIBBONS[i].currentdisplay) 
    { RIBBONS[i].pwmDuty = 0; }
    else 
    { RIBBONS[i].pwmDuty = 4; }
  }
}

void MoveToZero()
{
  //ToDo: Implement
}

void CheckForTargetMet()
{
  //check every target value to see if the round is completed
  for(int i = 0; i < ribbonCount; i++)
  {
    if(RIBBONS[i].targetDisplay != RIBBONS[i].currentdisplay)
    {
      return;
    }
  }
  //if all targets are met, change the runing state
  RUNNING_STATE == eTargetMet;
}




