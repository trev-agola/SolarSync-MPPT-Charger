#include <Wire.h>                   //SYSTEM PARAMETER  - WIRE Library for I2C (By: Arduino)
#include <LiquidCrystal_I2C.h>      //SYSTEM PARAMETER  - ESP32 LCD Compatible Library

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  pinMode(32, INPUT);
  Serial.begin(115200);
    lcd.init();
    lcd.setBacklight(HIGH);
}
void loop()
{
  float rawVoltage= analogRead(32)*(3.3/4095);
    lcd.setCursor(0,0);
    lcd.print("Current: "+ String(rawVoltage));

    delay(1000);
  // float ACSValue = 0.0, Samples = 0.0, AvgACS = 0.0, BaseVol = 1.48; //Change BaseVol as per your reading in the first step.
  // for (int x = 0; x < 500; x++) { //This would take 500 Samples
  //   ACSValue = analogRead(12);
  //   Samples = Samples + ACSValue;
  //   delay (3);
  // }
  // AvgACS = (((Samples/500) * (3.3 / 4095.0)) - BaseVol ) / 0.066 ;//0.066V = 66mVol. This is sensitivity of your ACS module.

  // if(AvgACS<=0){
  //   AvgACS=0;
  // }
  // Serial.println(AvgACS); 

}