#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Wire.h>                   //SYSTEM PARAMETER  - WIRE Library (By: Arduino)
#include <WiFi.h>                   //SYSTEM PARAMETER  - WiFi Library (By: Arduino)
#include <WiFiClient.h>             //SYSTEM PARAMETER  - WiFi Library (By: Arduino)
#include <BlynkSimpleEsp32.h>       //SYSTEM PARAMETER  - Blynk WiFi Library For Phone App 

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup(){
  lcd.init();                 // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Kasongo yeyee");
  lcd.setCursor(0,1);
  lcd.print("Mobali Na Nga");
}

void loop(){}