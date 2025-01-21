#define BLYNK_TEMPLATE_ID "TMPL2caJdmrhf"
#define BLYNK_TEMPLATE_NAME "SolarSync MPPT"
#define BLYNK_AUTH_TOKEN "YSeRJ1cABPNnI08EPfKENf9X5t8oX6fj"

String 
firmwareInfo      = "V1.0   ",
firmwareDate      = "14/01/2024",
firmwareContactR1 = "trevoragola5968@gmail.com",  
firmwareContactR2 = "Trevor Agola     ";  

#include <Wire.h>                   //SYSTEM PARAMETER  - WIRE Library for I2C (By: Arduino)
#include <LiquidCrystal_I2C.h>      //SYSTEM PARAMETER  - ESP32 LCD Compatible Library
#include <WiFi.h>                   //SYSTEM PARAMETER  - WiFi Library (By: Arduino)
#include <WiFiClient.h>             //SYSTEM PARAMETER  - WiFi Library (By: Arduino)
#include <BlynkSimpleEsp32.h>       //SYSTEM PARAMETER  - Blynk WiFi Library For Phone App 
TaskHandle_t Core2;                 //SYSTEM PARAMETER  - Used for the ESP32 dual core operation

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//PIN Definition
#define voltage_IN       34          //SYSTEM PARAMETER - Input voltage
#define current_IN       32          //SYSTEM PARAMETER - Buck MOSFET Driver High Side PWM Pin
#define voltage_OUT      35          //SYSTEM PARAMETER - Buck MOSFET Driver High Side PWM Pin
#define buck_HIN         33          //SYSTEM PARAMETER - Buck MOSFET Driver High Side PWM Pin
#define buck_LIN         26          //SYSTEM PARAMETER - Buck MOSFET Driver Low Side PWM Pin
#define buck_EN          25          //SYSTEM PARAMETER - Buck MOSFET Driver Enable Pin
#define backflow_MOSFET  27          //SYSTEM PARAMETER - Backflow MOSFET Driver High Side PWM Pin
#define backflow_EN      12          //SYSTEM PARAMETER - Backflow MOSFET Driver Enable Pin



//========================================= WiFi SSID ==============================================//
//                                           //

char 
auth[] = BLYNK_AUTH_TOKEN,   //   USER PARAMETER - Blynk Authentication Token (From email after registration)
ssid[] = "VI",                  // USER PARAMETER - Enter Your WiFi SSID
pass[] = "violetkerubo";   // USER PARAMETER - Enter Your WiFi Password


bool
enableLCD               = 1,           //   USER PARAMETER - Enable LCD display
enablePPWM              = 1,          //   USER PARAMETER - Enables Predictive PWM, this accelerates regulation speed
enableWiFi              = 1,           //   USER PARAMETER - Enable WiFi Connection
MPPT_Mode               = 1,           //   USER PARAMETER - Enable MPPT algorithm, when disabled charger uses CC-CV algorithm 
output_Mode             = 1;           //   USER PARAMETER - 0 = PSU MODE, 1 = Charger Mode  
int
ADCresolution           = 12,           //  USER PARAMETER - ADC Bit Resolution 
serialTelemMode         = 0,           //  USER PARAMETER - Selects serial telemetry data feed (0 - Disable Serial, 1 - Display All Data, 2 - Display Essential, 3 - Number only)
pwmResolution           = 11,          //  USER PARAMETER - PWM Bit Resolution 
telemCounterReset       = 0,           //  USER PARAMETER - Reset Telem Data Every (0 = Never, 1 = Day, 2 = Week, 3 = Month, 4 = Year) 
errorTimeLimit          = 1000,        //  USER PARAMETER - Time interval for reseting error counter (milliseconds)  
errorCountLimit         = 5,           //  USER PARAMETER - Maximum number of errors  
millisRoutineInterval   = 250,         //  USER PARAMETER - Time Interval Refresh Rate For Routine Functions (ms)
millisSerialInterval    = 1000,           //  USER PARAMETER - Time Interval Refresh Rate For USB Serial Datafeed (ms)
millisLCDInterval       = 1000,        //  USER PARAMETER - Time Interval Refresh Rate For LCD Display (ms)
millisWiFiInterval      = 2000,        //  USER PARAMETER - Time Interval Refresh Rate For WiFi Telemetry (ms)
pwmFrequency            = 39000,       //  USER PARAMETER - PWM Switching Frequency - Hz (For Buck)
baud                    = 115200;      //  USER PARAMETER - Serial Monitor Baud Rate
float 
voltageBatteryMax       = 12.0,     //   USER PARAMETER - Maximum Battery Charging Voltage (Output V)
voltageBatteryMin       = 9,     //   USER PARAMETER - Minimum Battery Charging Voltage (Output V)
currentCharging         = 3,     //   USER PARAMETER - Maximum Charging Current (A - Output)
electricalPrice         = 20.0000;      //   USER PARAMETER - Input electrical price per kWh (kshs)

int
avgCountVS              = 5,          //  CALIB PARAMETER - Voltage Sensor Average Sampling Count (Recommended: 3)
avgCountCS              = 5;          //  CALIB PARAMETER - Current Sensor Average Sampling Count (Recommended: 4)

float
BaseVol                 = 1.48,
ADC_MAX                 = 4095.0,     // ADC resolution (12-bit)
VREF                    = 3.3,        // Reference voltage (ESP32 ADC max)
inVoltageDivRatio       = 42.9200,    //  CALIB PARAMETER - Input voltage divider sensor ratio (change this value to calibrate voltage sensor)
outVoltageDivRatio      = 25.1905,    //  CALIB PARAMETER - Output voltage divider sensor ratio (change this value to calibrate voltage sensor)
vOutSystemMax           = 30.0000,    //  CALIB PARAMETER - 
cOutSystemMax           = 30.0000,    //  CALIB PARAMETER - 
voltageDropout          = 1.0000,     //  CALIB PARAMETER - Buck regulator's dropout voltage (DOV is present due to Max Duty Cycle Limit)
voltageBatteryThresh    = 9.0000,     //  CALIB PARAMETER - Power cuts-off when this voltage is reached (Output V)
currentInAbsolute       = 8.0000,    //  CALIB PARAMETER - Maximum Input Current The System Can Handle (A - Input)
currentOutAbsolute      = 4.0000,    //  CALIB PARAMETER - Maximum Output Current The System Can Handle (A - Input)
PPWM_margin             = 99.5000,    //  CALIB PARAMETER - Minimum Operating Duty Cycle for Predictive PWM (%)
PWM_MaxDC               = 92.0000,    //  CALIB PARAMETER - Maximum Operating Duty Cycle (%) 90%-97% is good
efficiencyRate          = 1.0000,     //  CALIB PARAMETER - Theroretical Buck Efficiency (% decimal)
currentMidPoint         = 2.5250,     //  CALIB PARAMETER - Current Sensor Midpoint (V)
currentSens             = 0.0000,     //  CALIB PARAMETER - Current Sensor Sensitivity (V/A)
currentSensV            = 0.0660,     //  CALIB PARAMETER - Current Sensor Sensitivity (mV/A)
vInSystemMin            = 5.000;     //  CALIB PARAMETER -

//===================================== SYSTEM PARAMETERS =========================================//
//The values below are variables used by system processes  //
//=================================================================================================//
bool
buckEnable            = 0,           // SYSTEM PARAMETER - Buck Enable Status
bypassEnable          = 0,           // SYSTEM PARAMETER - 
PWMCharging           = 0,
chargingPause         = 0,           // SYSTEM PARAMETER -      
WIFI                  = 0,           // SYSTEM PARAMETER - 
BNC                   = 0,           // SYSTEM PARAMETER -  
REC                   = 0,           // SYSTEM PARAMETER - 
FLV                   = 0,           // SYSTEM PARAMETER - 
IUV                   = 0,           // SYSTEM PARAMETER - 
IOV                   = 0,           // SYSTEM PARAMETER - 
IOC                   = 0,           // SYSTEM PARAMETER - 
OUV                   = 0,           // SYSTEM PARAMETER - 
OOV                   = 0,           // SYSTEM PARAMETER - 
OOC                   = 0,           // SYSTEM PARAMETER - 
OTE                   = 0;           // SYSTEM PARAMETER - 
int
inputSource           = 0,           // SYSTEM PARAMETER - 0 = MPPT has no power source, 1 = MPPT is using solar as source, 2 = MPPTis using battery as power source
pwmMax                = 0,           // SYSTEM PARAMETER -
pwmMaxLimited         = 0,           // SYSTEM PARAMETER -
PWM                   = 0,           // SYSTEM PARAMETER -
PPWM                  = 0,           // SYSTEM PARAMETER -
pwmCh_BuckHIN         = 0,           // SYSTEM PARAMETER -
pwmCh_BuckLIN         = 1,           // SYSTEM PARAMETER -
deadTime              = 80,          // SYSTEM PARAMETER -
batteryPercent        = 0,           // SYSTEM PARAMETER -
errorCount            = 0,           // SYSTEM PARAMETER -
ERR                   = 0,           // SYSTEM PARAMETER - 
conv1                 = 0,           // SYSTEM PARAMETER -
conv2                 = 0,           // SYSTEM PARAMETER -
intTemp               = 0;           // SYSTEM PARAMETER -
float
VSI                   = 0.0000,      // SYSTEM PARAMETER - Raw input voltage sensor ADC voltage
VSO                   = 0.0000,      // SYSTEM PARAMETER - Raw output voltage sensor ADC voltage
CSI                   = 0.0000,      // SYSTEM PARAMETER - Raw current sensor ADC voltage
CSI_converted         = 0.0000,      // SYSTEM PARAMETER - Actual current sensor ADC voltage 
powerInput            = 0.0000,      // SYSTEM PARAMETER - Input power (solar power) in Watts
powerInputPrev        = 0.0000,      // SYSTEM PARAMETER - Previously stored input power variable for MPPT algorithm (Watts)
powerOutput           = 0.0000,      // SYSTEM PARAMETER - Output power (battery or charing power in Watts)
energySavings         = 0.0000,      // SYSTEM PARAMETER - Energy savings in currency (Kshs)
voltageInput          = 0.0000,      // SYSTEM PARAMETER - Input voltage (solar voltage)
voltageInputPrev      = 0.0000,      // SYSTEM PARAMETER - Previously stored input voltage variable for MPPT algorithm
voltageOutput         = 0.0000,      // SYSTEM PARAMETER - Input voltage (battery voltage)
currentInput          = 0.0000,      // SYSTEM PARAMETER - Output power (battery or charing voltage)
currentOutput         = 0.0000,      // SYSTEM PARAMETER - Output current (battery or charing current in Amperes)
daysRunning           = 0.0000,      // SYSTEM PARAMETER - Stores the total number of days the MPPT device has been running since last powered
Wh                    = 0.0000,      // SYSTEM PARAMETER - Stores the accumulated energy harvested (Watt-Hours)
kWh                   = 0.0000,      // SYSTEM PARAMETER - Stores the accumulated energy harvested (Kiliowatt-Hours)
MWh                   = 0.0000,      // SYSTEM PARAMETER - Stores the accumulated energy harvested (Megawatt-Hours)
loopTime              = 0.0000,      // SYSTEM PARAMETER -
outputDeviation       = 0.0000,      // SYSTEM PARAMETER - Output Voltage Deviation (%)
vOutSystemMin         = 0.0000;     //  CALIB PARAMETER - 
unsigned long 
currentErrorMillis    = 0,           //SYSTEM PARAMETER -
currentRoutineMillis  = 0,           //SYSTEM PARAMETER -
currentSerialMillis   = 0,           //SYSTEM PARAMETER -
currentLCDMillis      = 0,           //SYSTEM PARAMETER - 
currentLCDBackLMillis = 0,           //SYSTEM PARAMETER - 
currentWiFiMillis     = 0,           //SYSTEM PARAMETER - 
prevSerialMillis      = 0,           //SYSTEM PARAMETER -
prevRoutineMillis     = 0,           //SYSTEM PARAMETER -
prevErrorMillis       = 0,           //SYSTEM PARAMETER -
prevWiFiMillis        = 0,           //SYSTEM PARAMETER -
prevLCDMillis         = 0,           //SYSTEM PARAMETER -
timeOn                = 0,           //SYSTEM PARAMETER -
loopTimeStart         = 0,           //SYSTEM PARAMETER - Used for the loop cycle stop watch, records the loop start time
loopTimeEnd           = 0,           //SYSTEM PARAMETER - Used for the loop cycle stop watch, records the loop end time
secondsElapsed        = 0;           //SYSTEM PARAMETER - 

void wifiTask(void * pvParameters){
 setupWiFi();                                              //TAB#7 - WiFi Initialization
//================= CORE0: LOOP (DUAL CORE MODE) ======================//
  while(true){
    Wireless_Telemetry();                                   //TAB#7 - Wireless telemetry (WiFi & Bluetooth)
    delay(3000);
    
}}
//================== CORE1: SETUP (DUAL CORE MODE) ====================//
void setup() { 
  
  //SERIAL INITIALIZATION          
  Serial.begin(baud);                                   //Set serial baud rate
  Serial.println("> Serial Initialized");                   //Startup message
  analogReadResolution(ADCresolution);            // Set ADC resolution

    //ENABLE DUAL CORE MULTITASKING
      // Create a task and pin it to Core 0
    xTaskCreatePinnedToCore(
        wifiTask,  // Task function
        "TaskOnCore0", // Task name
        10000,          // Stack size
        NULL,          // Parameters
        1,             // Priority
        &Core2,        // Task handle (to manage this task later)
        0              // Pin to Core 0
    );
  
  //GPIO PIN INITIALIZATION
  pinMode(backflow_MOSFET, OUTPUT);
  pinMode(backflow_EN,OUTPUT);
  pinMode(buck_EN,OUTPUT);

  digitalWrite(backflow_EN,1);
  digitalWrite(backflow_MOSFET,1);                          //Signal backflow MOSFET GPIO pin
  
  //PWM INITIALIZATION
   // Set up HIN PWM
  ledcAttachChannel(buck_HIN, pwmCh_BuckHIN, pwmFrequency, pwmResolution);                          
  
  // Set up LIN PWM
  ledcAttachChannel(buck_LIN,pwmFrequency, pwmResolution, pwmCh_BuckLIN);                           
  
  // Initialize PWM values
  ledcWriteChannel(pwmCh_BuckHIN, PWM);  // Start with duty cycle 0
  ledcWriteChannel(pwmCh_BuckLIN, PWM);  // Start with duty cycle 0

  pwmMax = pow(2,pwmResolution)-1;                           //Get PWM Max Bit Ceiling
  pwmMaxLimited = (PWM_MaxDC*pwmMax)/100.000;                //Get maximum PWM Duty Cycle (pwm limiting protection)
  
  //GPIO INITIALIZATION                          
  buck_Disable();

  //ENABLE DUAL CORE MULTITASKING
  xTaskCreatePinnedToCore(wifiTask,"coreTwo",10000,NULL,0,&Core2,0);
  //LCD INITIALIZATION
  if(enableLCD==1){
    lcd.init();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0,0);
    lcd.print("SOLARSYNC "+ String(firmwareInfo));
    lcd.setCursor(0,1);
    lcd.print("By: ");
    lcd.print("Trevor Agola");    
    delay(1500);
    lcd.clear();
  }

  //SETUP FINISHED
  Serial.println("> SOLARSYNC HAS INITIALIZED");                //Startup message
}

void loop() {
  // put your main code here, to run repeatedly:
  Read_Sensors();         //Sensor data measurement and computation
  Device_Protection();    //Fault detection algorithm  
  Charging_Algorithm();   //Battery Charging Algorithm                    
  Onboard_Telemetry();    //Onboard telemetry (Serial Monitor)
  displayConfig2();  //display data on LCD
}
