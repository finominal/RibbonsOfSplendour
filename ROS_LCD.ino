void InitializeLCD()
{
  pl("Initializing LCD");
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  //print welcome streen
  lcd.setCursor(0, 0);
  lcd.print("FLUFFY LIGHT");
  lcd.setCursor(0, 1);
  lcd.print("ENGINEERING");
  
  pl("Initializing LCD OK");
  delay(3000); //pause welcome screen
}

void UpdateLCDCountDownDisplay() 
{
  
  p("cyclesSinceLastDisplayToggle="); pl("cyclesSinceLastDisplayToggle");
  p("displayToggleCycles="); pl(cyclesSinceLastDisplayToggle);
  
  pl("    UpdateLCDCountDownDisplay");
  if(cyclesSinceLastDisplayToggle > displayToggleCycles)//Time to change display, uses a display state
  {
    pl("    Change Global Display - Update Timer");
    if(DISPLAY_STATE == eGlobal){
      DISPLAY_STATE=eTarget;
    }
    else{
      DISPLAY_STATE=eGlobal;
    }
    cyclesSinceLastDisplayToggle = 0; //reset the counter
  }

  pl("    Updating Display");
  if(DISPLAY_STATE == eGlobal) {
    LCDDisplayGlobalTime();
  }
  else{
    LCDDisplayTargetTime();
  }

  cyclesSinceLastDisplayToggle++;
 pl("    CompletedDisplayUpdate");
}



void LCDDisplayTargetTime()
{
  lcd.clear();
  
  char buf[21];
  targetTime.toString(buf,21);
   
  //Update Display
  //Line 1
  lcd.setCursor(0, 0);
  lcd.print("TARGET: ");
  for(int i = 12;i<=20;i++){lcd.print(buf[i]);}

  //Line 2
  lcd.setCursor(0, 1);
  lcd.print("     ");
  for(int i = 0;i<=10;i++){lcd.print(buf[i]);}
}

void LCDDisplayTargetTimeSet()
{
  lcd.clear();
  
  char buf[21];
  targetTime.toString(buf,21);
   
  //Update Display
  //Line 1
  lcd.setCursor(0, 0);
  lcd.print("target: ");
  for(int i = 12;i<=20;i++){lcd.print(buf[i]);}

  //Line 2
  lcd.setCursor(0, 1);
  lcd.print("set  ");
  for(int i = 0;i<=10;i++){lcd.print(buf[i]);}
}


void LCDDisplayGlobalTime()
{
  lcd.clear();
  
  char buf[21];
  globalTime.toString(buf,21);
   
  //Update Display
  //Line 1
  lcd.setCursor(0, 0);
  lcd.print("GLOBAL: ");
  for(int i = 12;i<=20;i++){lcd.print(buf[i]);}

  //Line 2
  lcd.setCursor(0, 1);
  lcd.print("     ");
  for(int i = 0;i<=10;i++){lcd.print(buf[i]);}
}

void LCDDisplayGlobalTimeSet()
{
  lcd.clear();
  
  char buf[21];
  globalTime.toString(buf,21);
   
  //Update Display
  //Line 1
  lcd.setCursor(0, 0);
  lcd.print("global: ");
  for(int i = 12;i<=20;i++){lcd.print(buf[i]);}

  //Line 2
  lcd.setCursor(0, 1);
  lcd.print("set  ");
  for(int i = 0;i<=10;i++){lcd.print(buf[i]);}
}


int SetCursorPositionForSetTimeFocus()
{
  switch (SET_TIME_FOCUS) {
    
    case eYear:
      lcd.setCursor(15,1); 
      break;
    case eMonth:
      lcd.setCursor(5,1); 
      break;
     case eDay:
      lcd.setCursor(10,1); 
      break;
     case eHour:
      lcd.setCursor(9,0); 
      break;
     case eMinute:
      lcd.setCursor(12,0); 
      break;
     case eSecond:
      lcd.setCursor(15,0); 
      break;
  }
}
 
 

