void resetVariables(){
  secondsElapsed = 0;
  energySavings  = 0; 
  daysRunning    = 0; 
  timeOn         = 0; 
}
void Read_Sensors(){

  /////////// VOLTAGE & CURRENT SENSORS /////////////
  VSI = 0.0000;      //Clear Previous Input Voltage 
  VSO = 0.0000;      //Clear Previous Output Voltage  
  CSI = 0.0000;      //Clear Previous Current  

  //VOLTAGE SENSOR - Instantenous Averaging   
  for(int i = 0; i<avgCountVS; i++){
    VSI = VSI + (analogRead(voltage_IN)/ ADC_MAX) * VREF; // Calculate voltage at ADC pin;
    VSO = VSO + (analogRead(voltage_OUT)/ ADC_MAX) * VREF; // Calculate voltage at ADC pin;
  }
  voltageInput  = (VSI/avgCountVS)*inVoltageDivRatio;  
  voltageOutput = (VSO/avgCountVS)*outVoltageDivRatio*1.360;

  // float ACSValue = 0.0, Samples = 0.0, AvgACS = 0.0; //Change BaseVol as per your reading in the first step.
  // for (int x = 0; x < avgCountCS; x++) { //This would take 500 Samples
  //   ACSValue = analogRead(12);
  //   Samples = Samples + ACSValue;
  //   delay (3);
  // } 

  // if(AvgACS<=0){
  //   AvgACS=0;
  // }
  //CURRENT SENSOR - Instantenous Averaging   
  for(int i = 0; i<avgCountCS; i++){
    CSI = CSI + analogRead(current_IN);
  }

  currentInput  = (((CSI/avgCountCS)* (VREF / ADC_MAX))) / 0.100 ;//0.100V = 100mVol. This is sensitivity of your ACS module.
  // currentInput  = analogRead(current_IN)*(VREF / ADC_MAX);

  if(currentInput<0)
  {
    currentInput=0.0000;
  }
  // if(voltageInput<=10.0){
  //   voltageInput = 0.0000;
  //   }
  if(voltageOutput<=0){
    currentOutput = 0.0000;
    }
  else{
    currentOutput = (voltageInput*currentInput)/voltageOutput;
    }

  //POWER SOURCE DETECTION
  if(voltageInput<=3 && voltageOutput<=3){inputSource=0;}  //System is only powered by USB port
  else if(voltageInput>voltageOutput)    {inputSource=1;}  //System is running on solar as power source
  else if(voltageInput<voltageOutput)    {inputSource=2;}  //System is running on batteries as power source
  
  // //////// AUTOMATIC CURRENT SENSOR CALIBRATION ////////
  // if(buckEnable==0 && FLV==0 && OOV == 0){                
  //   currentMidPoint = ((CSI/avgCountCS)*1.3300)-0.003;
  // }
  
  //POWER COMPUTATION - Through computation
  powerInput      = voltageInput*currentInput;
  powerOutput     = voltageInput*currentInput*efficiencyRate;
  outputDeviation = (voltageOutput/voltageBatteryMax)*100.000;

  //STATE OF CHARGE - Battery Percentage
  batteryPercent  = ((voltageOutput-voltageBatteryMin)/(voltageBatteryMax-voltageBatteryMin))*101;
  batteryPercent  = constrain(batteryPercent,0,100);

  //TIME DEPENDENT SENSOR DATA COMPUTATION
  currentRoutineMillis = millis();
  if(currentRoutineMillis-prevRoutineMillis>=millisRoutineInterval){   //Run routine every millisRoutineInterval (ms)
    prevRoutineMillis = currentRoutineMillis;                          //Store previous time
    Wh = Wh+(powerInput/(3600.000*(1000.000/millisRoutineInterval)));  //Accumulate and compute energy harvested (3600s*(1000/interval))
    kWh = Wh/1000.000;
    MWh = Wh/1000000.000;
    daysRunning = timeOn/(86400.000*(1000.000/millisRoutineInterval)); //Compute for days running (86400s*(1000/interval))
    timeOn++;                                                          //Increment time counter
  } 

  //OTHER DATA
  secondsElapsed = millis()/1000;                                      //Gets the time in seconds since the was turned on  and active
  energySavings  = electricalPrice*(Wh/1000.0000);                     //Computes the solar energy saving in terms of money (electricity flag rate)   
}