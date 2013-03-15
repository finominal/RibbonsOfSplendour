void InitializeAtariJoystick()
{
  //set joystick interrupts  
  pl("InitializeJoystick_Intertupts");
  attachInterrupt(0, AtariRedButtonPressed, FALLING); //pin 2
  attachInterrupt(5, AtariJoystickLEFT, FALLING); //pin 18
  attachInterrupt(4, AtariJoystickUP, FALLING);  //pin 19 
  attachInterrupt(3, AtariJoystickDOWN, FALLING); //pin 20
  attachInterrupt(2, AtariJoystickRIGHT, FALLING); //pin 21
  pl("InitializeJoystick_Intertupts_OK!");
  delay(1000);
}
//http://arduino.cc/en/Main/ArduinoBoardMega Lookup Interrupts



void InitializeInterruptTimerZero()
{
  pl("InitializeInterruptTimerZero");
   
  cli();//stop interrupts

//  //set timer0 interrupt at 2kHz
//  TCCR1A = 0;// set entire TCCR0A register to 0
//  TCCR1B = 0;// same for TCCR0B
//  TCNT0  = 0;//initialize counter value to 0
//  
//    
//  // set compare match register for 2khz increments
//  OCR0A = 50 ;// = (16*10^6) / (2000*64) - 1 (must be <256)
//  // turn on CTC mode
//  TCCR0A |= (1 << WGM01);
//  // Set CS11 and CS10 bits for 64 prescaler
//  TCCR0B |= (1 << CS11) | (1 << CS10);   
//  // enable timer compare interrupt
//  TIMSK0 |= (1 << OCIE0A);
  
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
  
  
  sei();
  
  pl("InitializeInterruptTimerZero_OK!");
  delay(1000);
}

//handle timer Zero Trigger
ISR(TIMER1_COMPA_vect){
  
  ItteratePWM();

}


