void InitializeAtariJoystick()
{
  //set joystick interrupts  
  attachInterrupt(0, AtariRedButtonPressed, FALLING); 
  attachInterrupt(5, AtariJoystickLEFT, FALLING); 
  attachInterrupt(4, AtariJoystickUP, FALLING); 
  attachInterrupt(3, AtariJoystickDOWN, FALLING); 
  attachInterrupt(2, AtariJoystickRIGHT, FALLING); 
}
