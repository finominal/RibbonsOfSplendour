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
  //Timer/Counter Control Register, Set the cloock source
  TCCR0A = B00000010; //Compare Match off 7:4 = 0, CTC mode 1:0 = B10;
  TCCR0B  = B00000011; //FOC0A:7 = 0,FOC0B:6 = 0, 5:4 res, WGM02:3 = 0, CS02:0 = 011 = 64
  
  //Timer/Counter
  //TCNT0 = counter register being declinated.
  
  //Output Compare Registers
  OCR0A  = 100; //the value to compare. 64*50 = 3200 = 5KHZ @16mhZ clock
  //OCR0B = 0; //Not used in this implementation
  
  //Timer Interrupt Mask Register
  TIMSK0 = B00000010; //7:3 res, OCIE0B:2 B register enable = 0; OCIE0A:1 A register Enable = 1; TOIE0:0 = over flow enable =0;
  
  sei();
  
  pl("InitializeInterruptTimerOne_OK");
}


//handle timer Zero Trigger
ISR(TIMER1_COMPA_vect){
  
  pl(" *TIMER1_COMPA_vect* ");
  ItteratePWM();

}

/*
  TCCR0A = 0;     // set entire TCCR1A register to 0
  TCCR0B = 0;     // same for TCCR1B
  
  // set compare match register to desired timer count:
  OCR0A = 50; //at 64 prescale, 50 = 3200 clock cycles = 5K 
  
  // turn on CTC mode:
  TCCR0B |= (1 << WGM12);
  
  // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR0B |= (1 << CS10);
  TCCR0B |= (1 << CS11);
  
  // enable timer compare interrupt:
  TIMSK0 |= (1 << OCIE1A);
  */
