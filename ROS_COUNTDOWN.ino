
void RunCountdownProgram()
{
  while(GLOBAL_STATE == eCountdown)
  {
    if(RUNNING_STATE == eStarting)
    {
      PrepareSensors();
      if(IsTimeDiffEnoughForCountDown)
      {
        PrepareDisplayForCountDown(); 
      }
      else
      {
        GLOBAL_STATE = eCompleted; //not enought time left to start up the sequence, or Timer has expired.
        //Completed will trigger the display to move to ZERO, then change the Global State to eParked
      }
    }
    else if(RUNNING_STATE == eSynching)
    {
      WaitForSync();
    }
    else
    {
       ExecuteCountDownSequence(); //sub loop in here
    }
  }
}

//runs when eParked to check for a new countdown 
void CheckForNewCountDown()
{
  if(globalTime.secondstime() < targetTime.secondstime())
    {
      GLOBAL_STATE = eCountdown;
      RUNNING_STATE = eStarting;
  }
}


void WaitForSync()
{
  GetGlobalTime();
  if(nextDisplayTime.secondstime() -  globalTime.secondstime() < 0) 
  {
    nextDisplayTime = DateTime(globalTime.secondstime()+1); //advance to the next Second
    RUNNING_STATE == eRunning;
  }
}

void PrepareDisplayForCountDown()
{
  //this subroutine runs ONCE, and exits when the ribbons are in place. 
  //To get here the RUNING_STATE must be in eStarting, and will end with eSyncing
  pl();
  pl("PrepareDisplayForCountDown");
  pl();
  
  LcdInformStartingCountdown();
  
  nextDisplayTime = TimeDiff_CalculateNextTargetTime(); //calculate a waiting time to sync to.
  displayTarget = ConvertSecondsToDisplay(nextDisplayTime.secondstime());
  displayTarget.second = 0; //Round down to the minute.
  
  UpdateRibbonTargets();
  
  MoveToTarget(); //Loops inside here untill ribbons have moved to ready position. 
}

void ExecuteCountDownSequence()
{
  pl("CountingDownLoop")
  UpdateLCDCountDownDisplay();
  SetDisplayTarget(); 
  UpdateRibbonTargets();
  MoveToTarget();
  CheckForCompletion(); //will change GLOBAL_STATE to exit this loop
  delay(mainLoopDelayMS/10);
}

void SetDisplayTarget()
{
  pl("  SetDisplayTarget");
  displayTarget = CalculateCountDownDisplay(globalTime, targetTime);
}

void UpdateRibbonTargets()
{
  pl("  UpdateRibbonTargets");
  
  //Set Days: Ribbon ID 8,7,6
  //Set Days Hundreds
  RIBBONS[8].targetDisplay = displayTarget.day / 100;
    if(RIBBONS[8].targetDisplay == 0) RIBBONS[8].targetDisplay = RIBBONS[8].length + 1; //If Zero, change to blank = max Ribbon IDX
  
  //Set Days Tens
  RIBBONS[7].targetDisplay = (displayTarget.day % 100) / 10; //days tens
    if(RIBBONS[7].targetDisplay == 0 && RIBBONS[8].targetDisplay == RIBBONS[8].length + 1 ) RIBBONS[7].targetDisplay = RIBBONS[7].length + 1; //If Zero and hudreds is blank, change to blank = max Ribbon IDX
    
  //Set Days Ones
  RIBBONS[6].targetDisplay = (displayTarget.day % 100) % 10 ;
      //Will set black, otherwize will show zero for last numeral 
      //if(RIBBONS[6].targetDisplay == 0 && RIBBONS[8].targetDisplay == RIBBONS[8].length + 1 && RIBBONS[7].targetDisplay = RIBBONS[7].length + 1) RIBBONS[6].targetDisplay = RIBBONS[6].length + 1; //If Zero and hudreds is blank, change to blank = max Ribbon IDX
   
  //Set Hours: 5,4
  //Set Hours Tens
  RIBBONS[5].targetDisplay = displayTarget.hour / 10 ; //days ones
      if(RIBBONS[5].targetDisplay == 0) RIBBONS[5].targetDisplay = RIBBONS[5].length + 1; //If Zero, change to blank = max Ribbon IDX
  
  //Set Hours Ones
  RIBBONS[4].targetDisplay = displayTarget.hour % 10 ; //days ones
      //Will set black, otherwize will show zero for last numeral 
      //if(RIBBONS[4].targetDisplay == 0 && RIBBONS[5].targetDisplay == RIBBONS[5].length + 1 ) RIBBONS[4].targetDisplay = RIBBONS[4].length + 1; //If Zero and hudreds is blank, change to blank = max Ribbon IDX
    
  //Set Minutes: 3,2
  //Set Minutes Tens
  RIBBONS[3].targetDisplay = displayTarget.minute / 10 ; //days ones
      if(RIBBONS[3].targetDisplay == 0) RIBBONS[3].targetDisplay = RIBBONS[3].length + 1; //If Zero, change to blank = max Ribbon IDX
  
  //Set Minutes Ones
  RIBBONS[2].targetDisplay = displayTarget.minute % 10 ; //days ones
      //Will set black, otherwize will show zero for last numeral 
      //if(RIBBONS[2].targetDisplay == 0 && RIBBONS[3].targetDisplay == RIBBONS[3].length + 1 ) RIBBONS[2].targetDisplay = RIBBONS[2].length + 1; //If Zero and hudreds is blank, change to blank = max Ribbon IDX
    
  //Set Seconds: 1,0
  //Set Seconds Tens
  RIBBONS[1].targetDisplay = displayTarget.second / 10 ; //days ones
      if(RIBBONS[1].targetDisplay == 0) RIBBONS[1].targetDisplay = RIBBONS[1].length + 1; //If Zero, change to blank = max Ribbon IDX
  
  //Set Seconds Ones
  RIBBONS[0].targetDisplay = displayTarget.second % 10 ; //days ones
      //Will set black, otherwize will show zero for last numeral 
      //if(RIBBONS[2].targetDisplay == 0 && RIBBONS[3].targetDisplay == RIBBONS[3].length + 1 ) RIBBONS[2].targetDisplay = RIBBONS[2].length + 1; //If Zero and hudreds is blank, change to blank = max Ribbon IDX
      
  if(DEV_MODE) SerialDisplayAllRibbonPrimaryValues();
}



void MoveToTarget()
{
  pl("  MoveRibbonsToTargets");
  RUNNING_STATE = eMoving;
  while(RUNNING_STATE == eMoving && GLOBAL_STATE == eCountdown) //GLobal State helps exit on TimeChange selected.
  {
    UpdatePWMs();// has to run each loop as some ribbins will stop in place before others.
    SensorManager_AllSensorsScanItteration();
    CheckForTargetMet();
    
    if(DEV_MODE) 
    {
      delay(500);
      //SerialDisplayAllRibbonPrimaryValues();
    }
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
  pl("   UpdatePWM's");
  for(int i = 0; i < ribbonCount; i++)
  {
    if(RIBBONS[i].targetDisplay == RIBBONS[i].currentDisplay) 
    { RIBBONS[i].pwmDuty = 0; }
    else 
    { RIBBONS[i].pwmDuty = 4; }
  }
}

void MoveToZero()
{
  displayTarget = ConvertSecondsToDisplay(0);
  UpdateRibbonTargets();
  MoveToTarget();
  RUNNING_STATE == eTargetMet;
}

void CheckForTargetMet()
{
  pl("   CheckForTargetMet");
  //check every target value to see if the round is completed
  for(int i = 0; i < ribbonCount; i++)
  {
    if(RIBBONS[i].targetDisplay != RIBBONS[i].currentDisplay)
    {
      p("     Ribbon "); p(i); pl(" Not Ready.");
      return;
    }
  }
  //if all targets are met, change the runing state
  RUNNING_STATE == eTargetMet;
}




