void buck_Enable(){                                                                  //Enable MPPT Buck Converter
  buckEnable = 1;
  digitalWrite(buck_EN,HIGH);
}
void buck_Disable(){                                                                 //Disable MPPT Buck Converter
  buckEnable = 0; 
  digitalWrite(buck_EN,LOW);
  PWM = 0;
}
// Write Complementary PWM with Dead Time
void complementaryPWM(int dutyCycle) {
  int dutyHIN = dutyCycle;                                 // High-side duty cycle
  int dutyLIN = pwmMax - dutyCycle;                        // Low-side duty cycle

  // Add dead time logic
  if (dutyHIN > (pwmMax - deadTime)) {
    dutyHIN = pwmMax - deadTime;
  }
  if (dutyLIN < deadTime) {
    dutyLIN = deadTime;
  }

  ledcWriteChannel(pwmCh_BuckHIN,dutyHIN);
  ledcWriteChannel(pwmCh_BuckLIN,dutyLIN);                                                         //Set PWM duty cycle and write to GPIO when buck is enabled
}

void predictivePWM(){                                                                //PREDICTIVE PWM ALGORITHM 
  if(voltageInput<=0)
  { 
    PPWM=0;
  }                                                       //Prevents Indefinite Answer when voltageInput is zero
  else{
    PPWM =(PPWM_margin*pwmMax*voltageOutput)/(100.00*voltageInput);//Compute for predictive PWM Floor and store in variable
    }              
  PPWM = constrain(PPWM,0,pwmMaxLimited);
}   

void PWM_Modulation(){
  if(output_Mode==0)
  {
    PWM = constrain(PWM,0,pwmMaxLimited);
    }                          //PSU MODE PWM = PWM OVERFLOW PROTECTION (limit floor to 0% and ceiling to maximim allowable duty cycle)
  else{
    predictivePWM();                                                                 //Runs and computes for predictive pwm floor
    PWM = constrain(PWM,PPWM,pwmMaxLimited);                                         //CHARGER MODE PWM - limit floor to PPWM and ceiling to maximim allowable duty cycle)                                       
  } 

  complementaryPWM(PWM);
  buck_Enable();                                                                     //Turn on MPPT buck (IR2104)
}
     
void Charging_Algorithm(){
  if(ERR>0||chargingPause==1){buck_Disable();}                                       //ERROR PRESENT  - Turn off MPPT buck when error is present or when chargingPause is used for a pause override
  else{
    if(REC==1){                                                                      //IUV RECOVERY - (Only active for charging mode)
      REC=0;                                                                         //Reset IUV recovery boolean identifier 
      buck_Disable();                                                                //Disable buck before PPWM initialization 
      predictivePWM();
      PWM = PPWM; 
    }  
    else{                                                                            //NO ERROR PRESENT  - Continue power conversion              
      /////////////////////// CC-CV BUCK PSU ALGORITHM ////////////////////////////// 
      if(MPPT_Mode==0){                                                              //CC-CV PSU MODE
        if(currentOutput>currentCharging)       {PWM--;}                             //Current Is Above → Decrease Duty Cycle
        else if(voltageOutput>voltageBatteryMax){PWM--;}                             //Voltage Is Above → Decrease Duty Cycle   
        else if(voltageOutput<voltageBatteryMax){PWM++;}                             //Increase duty cycle when output is below charging voltage (for CC-CV only mode)
        else{}                                                                       //Do nothing when set output voltage is reached 
        PWM_Modulation();                                                            //Set PWM signal to Buck PWM GPIO       
      }     
        /////////////////////// MPPT & CC-CV CHARGING ALGORITHM ///////////////////////  
      else{                                                                                                                                                         
        if(currentOutput>currentCharging){PWM--;}                                      //Current Is Above → Decrease Duty Cycle
        else if(voltageOutput>voltageBatteryMax){PWM--;}                               //Voltage Is Above → Decrease Duty Cycle   
        else{                                                                          //MPPT ALGORITHM
          if(powerInput>powerInputPrev && voltageInput>voltageInputPrev)     {PWM--;}  //  ↑P ↑V ; →MPP  //D--
          else if(powerInput>powerInputPrev && voltageInput<voltageInputPrev){PWM++;}  //  ↑P ↓V ; MPP←  //D++
          else if(powerInput<powerInputPrev && voltageInput>voltageInputPrev){PWM++;}  //  ↓P ↑V ; MPP→  //D++
          else if(powerInput<powerInputPrev && voltageInput<voltageInputPrev){PWM--;}  //  ↓P ↓V ; ←MPP  //D--
          else if(voltageOutput<voltageBatteryMax)                           {PWM++;}  //  MP MV ; MPP Reached - 
          powerInputPrev   = powerInput;                                               //Store Previous Recorded Power
          voltageInputPrev = voltageInput;                                             //Store Previous Recorded Voltage        
        }   
        PWM_Modulation();                                                              //Set PWM signal to Buck PWM GPIO                                                                       
      }  
    }
  }
}