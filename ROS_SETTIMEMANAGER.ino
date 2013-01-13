

void SetGlobalTime()
{
  pl("Enter SetGLobalTime");

  while (ATARI_JOYSTICK == eCentre && GLOBAL_STATE == eSetGlobalTime) //wait for input
  {
    pl("Waiting For Input Loop");

    //Display The current Global Time
    GetGlobalTime();
    LCDDisplayGlobalTimeSet();

    //Set the cursor to the first position
    SetCursorPositionForSetTimeFocus();
    lcd.blink();
    delay(mainLoopDelayMS/2);

  }

  lcd.clear();

  pl("SetGLobalTime - Post While Loop");
  switch(ATARI_JOYSTICK) {
  case eLeft:
    ShiftTimeFocusLeft();
    ClearAtariJoystickBuffer();
    break;
  case eRight:
    ShiftTimeFocusRight();
    ClearAtariJoystickBuffer();
    break;
  case eUp:
    globalTime = AdjustClockUp(globalTime);
    clock.adjust(globalTime);
    ClearAtariJoystickBuffer();
    break;
  case eDown:
    globalTime = AdjustClockDown(globalTime);
    clock.adjust(globalTime);
    ClearAtariJoystickBuffer();
    break;
  }
}


void SetTargetTime()

{
  pl("Enter TargetGLobalTime");

  while (ATARI_JOYSTICK == eCentre && GLOBAL_STATE == eSetTargetTime) //wait for input
  {
    pl("Waiting For Input (loop)");

    //Display The current Global Time
    LCDDisplayTargetTimeSet();

    //Set the cursor to the first position
    SetCursorPositionForSetTimeFocus();
    lcd.blink();
    delay(mainLoopDelayMS/2);

  }

  lcd.clear();

  pl("SetTargetTime-Navigation");
  switch(ATARI_JOYSTICK) {
  case eLeft:
    ShiftTimeFocusLeft();
    ClearAtariJoystickBuffer();
    break;
  case eRight:
    ShiftTimeFocusRight();
    ClearAtariJoystickBuffer();
    break;
  case eUp:
    targetTime = AdjustClockUp(targetTime);
    TargetTimeWriteEeprom();
    TargetTimeReadEeprom();
    ClearAtariJoystickBuffer();
    break;
  case eDown:
    targetTime = AdjustClockDown(targetTime);
    TargetTimeWriteEeprom();
    TargetTimeReadEeprom();
    ClearAtariJoystickBuffer();
    break;
  }
}

void ShiftTimeFocusRight()
{
    switch (SET_TIME_FOCUS) 
    {
    case eHour:
      SET_TIME_FOCUS = eMinute;
      break;
    case eMinute:
      SET_TIME_FOCUS = eSecond;
      break;
    case eSecond:
      SET_TIME_FOCUS = eMonth;
      break;  
    case eMonth:
      SET_TIME_FOCUS = eDay;
      break;
    case eDay:
      SET_TIME_FOCUS = eYear;
      break;
    case eYear:
      SET_TIME_FOCUS = eHour;
      break;
    }
}

void ShiftTimeFocusLeft()
{
 switch (SET_TIME_FOCUS) 
    {
    case eHour:
      SET_TIME_FOCUS = eYear;
      break;
    case eYear:
      SET_TIME_FOCUS = eDay;
      break;
    case eDay:
      SET_TIME_FOCUS = eMonth;
      break;  
    case eMonth:
      SET_TIME_FOCUS = eSecond;
      break;
    case eSecond:
      SET_TIME_FOCUS = eMinute;
      break;
    case eMinute:
      SET_TIME_FOCUS = eHour;
      break;
    }
}


