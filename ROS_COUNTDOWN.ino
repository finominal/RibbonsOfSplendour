
void RunCountdownProgram()
{
  
  while(GLOBAL_STATE == eCountdown)
  {
    pl("CountingDownLoop")
    UpdateLCDCountDownDisplay();
    SetDisplayTarget(); 
    UpdateRibbonTargets();
    MoveToTarget();
    CheckForCompletion(); //will change GLOBAL_STATE to exit this loop
      delay(mainLoopDelayMS/10);
  }
}

void SetDisplayTarget()
{
  pl("  SetDisplayTarget");
  //SHIT
}

void UpdateRibbonTargets()
{
  pl("  UpdateRibbonTargets");
  //RUNNING_STATE = eMoving;
}

void MoveToTarget()
{
  pl("  MoveRibbonsToTargets");
  while(RUNNING_STATE == eMoving)
  {
    UpdatePWMs();
    CheckForTargetMet();
  }
}

void CheckForCompletion()
{
  pl("  CheckForMoveToTargetsComletion");
  if(targetTime.secondstime() <  globalTime.secondstime())
  {
    GLOBAL_STATE = eCompleted;
  }
}


void UpdatePWMs()
{
  pl("  UpdatePWM's");
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
  pl("CheckForTargetMet");
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




