void InitializeJoystick()
{
  //set joystick interrupts  
  pl("Initialize Joystick Intertupts");
  attachInterrupt(0, JoystickRedButtonPressed, FALLING); //pin  = Red Button
  attachInterrupt(5, JoystickLEFT, FALLING); //pin 18
  attachInterrupt(4, JoystickUP, FALLING);  //pin 19 
  attachInterrupt(3, JoystickDOWN, FALLING); //pin 20
  attachInterrupt(2, JoystickRIGHT, FALLING); //pin 21
  pl("InitializeJoystick Intertupts OK");
}
//http://arduino.cc/en/Main/ArduinoBoardMega Lookup Interrupts


void InitializeInterruptPWM()
{
  pl("InitializeInterruptTimerTwo");
  
  DisableTimerInterruptTwo();
  
  TCCR2A &= ~((1<<WGM21) | (1<<WGM20)); //bits 7:6 set compare match (OC2A = pin ?) bits 5:4 set compare match (OC2B = pin ?), 00 = off.
  TCCR2B &= ~(1<<WGM22);
  ASSR &= ~(1<<AS2);
  TIMSK2 &= ~(1<<OCIE2A);
  TCCR2B |= ((1<<CS22))  ; //prescaler 256
  TCCR2B &= ~ ((1<<CS20)| (1<<CS21));
  TCNT2 = 256; // counter
	
  pl("Initialize Interrupt Timer Two OK");
}


//handle timer Zero Trigger
ISR(TIMER2_OVF_vect){
  
  //pl("*T2*");
  ItteratePWM();

}

void EnableTimerInteruptTwo()
{
  TIMSK2 |= (1<<TOIE2);
}

void DisableTimerInterruptTwo()
{
  TIMSK2 &= ~(1<<TOIE2); //disable the timer
}
