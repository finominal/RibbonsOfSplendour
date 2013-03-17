void InitializeClock()
{
  pl("Initializing Clock");
  pinMode(SPI_CS, OUTPUT);
  SPI.begin();
  clock.begin();
  pl("Clock Initialized OK");
}


void GetGlobalTime()
{
  globalTime = clock.now();
}


