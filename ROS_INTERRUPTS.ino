void InitializeJoystick()
{
  //set joystick interrupts  
  pl("InitializeJoystick_Intertupts");
  attachInterrupt(0, JoystickRedButtonPressed, FALLING); //pin  = Red Button
  attachInterrupt(5, JoystickLEFT, FALLING); //pin 18
  attachInterrupt(4, JoystickUP, FALLING);  //pin 19 
  attachInterrupt(3, JoystickDOWN, FALLING); //pin 20
  attachInterrupt(2, JoystickRIGHT, FALLING); //pin 21
  pl("InitializeJoystick_Intertupts_OK");
}
//http://arduino.cc/en/Main/ArduinoBoardMega Lookup Interrupts



void InitializeInterruptTimerOne()
{
  pl("InitializeInterruptTimerOne");
   
  cli();//stop interrupts

  
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B
  
  // set compare match register to desired timer count:
  OCR1A = 50; //at 64 prescale, 50 = 3200 clock cycles = 5K 
  
  // turn on CTC mode:
  TCCR1B |= (1 << WGM12);
  
  // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS11);
  
  // enable timer compare interrupt:
  TIMSK1 |= (1 << OCIE1A);
  
  //sei();
  
  pl("InitializeInterruptTimerOne_OK");
}


//handle timer Zero Trigger
ISR(TIMER1_COMPA_vect){
  pl("TIMER1_COMPA_vect");
  ItteratePWM();

}


