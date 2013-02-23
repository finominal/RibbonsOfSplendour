void InitializeAtariJoystick()
{
  //set joystick interrupts  
  attachInterrupt(0, AtariRedButtonPressed, FALLING); //pin 2
  attachInterrupt(5, AtariJoystickLEFT, FALLING); //pin 18
  attachInterrupt(4, AtariJoystickUP, FALLING);  //pin 19 
  attachInterrupt(3, AtariJoystickDOWN, FALLING); //pin 20
  attachInterrupt(2, AtariJoystickRIGHT, FALLING); //pin 21
}
//http://arduino.cc/en/Main/ArduinoBoardMega Lookup Interrupts

void InitializeCustomPWM()
{
//initialise timer interrupt to trigger PWM

}


