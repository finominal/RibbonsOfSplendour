

void AtariRedButtonPressed()
{
  if(GLOBAL_STATE == eCountdown)
  {
    GLOBAL_STATE = eSetGlobalTime; 
    ClearAtariJoystickBuffer(); //make sure there are no joystick registeres 
    SET_TIME_FOCUS = eYear;    
    return;
  }
  
  if(GLOBAL_STATE == eSetGlobalTime)
  {
    GLOBAL_STATE = eSetTargetTime; 
    ClearAtariJoystickBuffer();
    SET_TIME_FOCUS = eYear;
    return;
  }

  if(GLOBAL_STATE == eSetTargetTime)
  {
    GLOBAL_STATE = eCountdown; 
    return;
  }
}

void AtariJoystickLEFT(){ATARI_JOYSTICK = eLeft;}

void AtariJoystickUP(){ATARI_JOYSTICK = eUp;}

void AtariJoystickDOWN(){ATARI_JOYSTICK = eDown;}

void AtariJoystickRIGHT(){ATARI_JOYSTICK = eRight;}

void ClearAtariJoystickBuffer(){ATARI_JOYSTICK = eCentre;}

