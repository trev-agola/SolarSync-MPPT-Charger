void padding100(int padVar){
  if(padVar<10){lcd.print("  ");}
  else if(padVar<100){lcd.print(" ");}
}
void padding10(int padVar){
  if(padVar<10){lcd.print(" ");}
}
void displayConfig1(){
  lcd.setCursor(0,0);lcd.print(powerInput,0);lcd.print("W");padding100(powerInput);      
  lcd.setCursor(5,0);
  if(Wh<10){lcd.print(Wh,3);lcd.print("Wh ");}                 //9.999Wh_
  else if(Wh<100){lcd.print(Wh,2);lcd.print("Wh ");}           //99.99Wh_
  else if(Wh<1000){lcd.print(Wh,1);lcd.print("Wh ");}          //999.9Wh_
  else if(Wh<10000){lcd.print(kWh,2);lcd.print("kWh ");}       //9.99kWh_
  else if(Wh<100000){lcd.print(kWh,1);lcd.print("kWh ");}      //99.9kWh_
  else if(Wh<1000000){lcd.print(kWh,0);lcd.print("kWh  ");}    //999kWh__
  else if(Wh<10000000){lcd.print(MWh,2);lcd.print("MWh ");}    //9.99MWh_
  else if(Wh<100000000){lcd.print(MWh,1);lcd.print("MWh ");}   //99.9MWh_ 
  else if(Wh<1000000000){lcd.print(MWh,0);lcd.print("MWh  ");} //999MWh__
  lcd.setCursor(13,0);lcd.print(daysRunning,0); 
  lcd.setCursor(0,1);lcd.print(batteryPercent);lcd.print("%");padding100(batteryPercent);
  if(BNC==0){lcd.setCursor(5,1); lcd.print(voltageOutput,1);lcd.print("V");padding10(voltageOutput);}
  else{lcd.setCursor(5,1);lcd.print("NOBAT ");}          
  lcd.setCursor(11,1);lcd.print(currentOutput,1);lcd.print("A");padding10(currentOutput);     
}
void displayConfig2(){
  lcd.setCursor(0,0); lcd.print(powerInput,0);  lcd.print("W");padding100(powerInput);    
  lcd.setCursor(5,0); lcd.print(voltageInput,1);lcd.print("V");padding10(voltageInput);            
  lcd.setCursor(11,0);lcd.print(currentInput,1);lcd.print("A");padding10(currentInput);    
  lcd.setCursor(0,1); lcd.print(batteryPercent);lcd.print("%");padding100(batteryPercent); 
  if(BNC==0){lcd.setCursor(5,1); lcd.print(voltageOutput,1);lcd.print("V");padding10(voltageOutput);}
  else{lcd.setCursor(5,1);lcd.print("NOBAT");}
  lcd.setCursor(11,1);lcd.print(currentOutput,1);lcd.print("A");padding10(currentOutput);    
}
void displayConfig3(){
  lcd.setCursor(0,0);  lcd.print(powerInput,0);lcd.print("W");padding100(powerInput); 
  lcd.setCursor(5,0);
  if(Wh<10){lcd.print(Wh,2);lcd.print("Wh ");}                 //9.99Wh_
  else if(Wh<100){lcd.print(Wh,1);lcd.print("Wh ");}           //99.9Wh_
  else if(Wh<1000){lcd.print(Wh,0);lcd.print("Wh  ");}         //999Wh__
  else if(Wh<10000){lcd.print(kWh,1);lcd.print("kWh ");}       //9.9kWh_
  else if(Wh<100000){lcd.print(kWh,0);lcd.print("kWh  ");}     //99kWh__
  else if(Wh<1000000){lcd.print(kWh,0);lcd.print("kWh ");}     //999kWh_
  else if(Wh<10000000){lcd.print(MWh,1);lcd.print("MWh ");}    //9.9MWh_
  else if(Wh<100000000){lcd.print(MWh,0);lcd.print("MWh  ");}  //99MWh__
  else if(Wh<1000000000){lcd.print(MWh,0);lcd.print("MWh ");}  //999Mwh_
  lcd.setCursor(12,0);lcd.print(batteryPercent);lcd.print("%");padding100(batteryPercent);
  int batteryPercentBars;
  batteryPercentBars = batteryPercent/6.18; //6.25 proper value
  lcd.setCursor(0,1);
  for(int i=0;i<batteryPercentBars;i++){lcd.print((char)255);} //Battery Bar Blocks    
  for(int i=0;i<16-batteryPercentBars;i++){lcd.print(" ");}    //Battery Blanks
}

void displayConfig5(){
  lcd.setCursor(0,0);lcd.print(" SETTINGS MENU  ");
  lcd.setCursor(0,1);lcd.print("--PRESS SELECT--");
}