void  TestTurnOnMotorsPWMCycle(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)
{
  RIBBONS[0].pwmDuty = i0;
  RIBBONS[1].pwmDuty = i1;
  RIBBONS[2].pwmDuty = i2;
  RIBBONS[3].pwmDuty = i3;
  RIBBONS[4].pwmDuty = i4;
  RIBBONS[5].pwmDuty = i5;
  RIBBONS[6].pwmDuty = i6;
  RIBBONS[7].pwmDuty = i7;
  RIBBONS[8].pwmDuty = i8;
}

void TestRibbonMoveAndDisplay(int idx)
{
  pl();
  pl("Loop");
    //dev
  RIBBONS[idx].pwmDuty = 4;
  
  RibbonSensorScanCycle_Itteration(idx);
  
  lcd.clear();
  
  char buf[21];
  targetTime.toString(buf,21);
   
  //Update Display
  //Line 1
  lcd.setCursor(0, 0);
  lcd.print("R"); lcd.print(idx); lcd.print(" ");
  
  lcd.print( RIBBONS[idx].lastDetectedTime);
  lcd.setCursor(14, 0);
  lcd.print("c");
  lcd.print( RIBBONS[idx].readSensorCycle); 
    

  //Line 2
  lcd.setCursor(0, 1);
  lcd.print(RIBBONS[idx].currentDisplay); 
  
  lcd.setCursor(3, 1); 
  lcd.print("r");
  lcd.print(RIBBONS[idx].rawSensorData, DEC); 
  
  lcd.setCursor(7, 1);
  lcd.print("M");
    lcd.print(HighMotorByte, HEX);
  lcd.print(LowMotorByte, HEX);

  delay(20);
  //Yay
  }
