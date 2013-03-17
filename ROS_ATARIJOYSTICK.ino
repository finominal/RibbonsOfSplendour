

void JoystickRedButtonPressed()
{
  pl("*IR_JoystickRedButtonPress");
  if(GLOBAL_STATE == eCountdown || GLOBAL_STATE == eCompleted)
  {
    GLOBAL_STATE = eSetGlobalTime; 
    ClearJoystickBuffer(); //make sure there are no joystick registeres 
    SET_TIME_FOCUS = eHour;    
    return;
  }
  
  if(GLOBAL_STATE == eSetGlobalTime)
  {
    GLOBAL_STATE = eSetTargetTime; 
    ClearJoystickBuffer();
    SET_TIME_FOCUS = eHour; 
    return;
  }

  if(GLOBAL_STATE == eSetTargetTime)
  {
    GLOBAL_STATE = eCountdown; 
    return;
  }
}

void JoystickLEFT(){pl("*IR_JoystickPress_LEFT"); JOYSTICK_STATE = eLeft;}

void JoystickUP(){pl("*IR_JoystickPress_UP"); JOYSTICK_STATE = eUp;}

void JoystickDOWN(){pl("*IR_JoystickPress_DOWN"); JOYSTICK_STATE = eDown;}

void JoystickRIGHT(){pl("*IR_JoystickPress_RIGHT"); JOYSTICK_STATE = eRight;}

void ClearJoystickBuffer(){ JOYSTICK_STATE = eCentre;}

