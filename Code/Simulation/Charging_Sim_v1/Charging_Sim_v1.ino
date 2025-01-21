//PIN Definition
#define buck_HIN         0          //SYSTEM PARAMETER - Buck MOSFET Driver High Side PWM Pin
#define buck_LIN         2          //SYSTEM PARAMETER - Buck MOSFET Driver Low Side PWM Pin
#define buck_EN          1          //SYSTEM PARAMETER - Buck MOSFET Driver Enable Pin
#define backflow_MOSFET  3          //SYSTEM PARAMETER - Backflow MOSFET Driver High Side PWM Pin
#define backflow_EN      4          //SYSTEM PARAMETER - Backflow MOSFET Driver Enable Pin

bool
enablePPWM              = 1,          //   USER PARAMETER - Enables Predictive PWM, this accelerates regulation speed
MPPT_Mode               = 1,           //   USER PARAMETER - Enable MPPT algorithm, when disabled charger uses CC-CV algorithm 
output_Mode             = 1;           //   USER PARAMETER - 0 = PSU MODE, 1 = Charger Mode  
int
pwmResolution           = 11,          //  USER PARAMETER - PWM Bit Resolution 
pwmFrequency            = 39000,       //  USER PARAMETER - PWM Switching Frequency - Hz (For Buck)
errorTimeLimit          = 1000,        //  USER PARAMETER - Time interval for reseting error counter (milliseconds) 
errorCountLimit         = 5;           //  USER PARAMETER - Maximum number of errors  


float 
voltageBatteryMax       = 12.0,     //   USER PARAMETER - Maximum Battery Charging Voltage (Output V)
voltageBatteryMin       = 9,     //   USER PARAMETER - Minimum Battery Charging Voltage (Output V)
currentCharging         = 3,     //   USER PARAMETER - Maximum Charging Current (A - Output)
electricalPrice         = 20.0000;      //   USER PARAMETER - Input electrical price per kWh (kshs)

int
avgCountVS              = 3,          //  CALIB PARAMETER - Voltage Sensor Average Sampling Count (Recommended: 3)
avgCountCS              = 4,          //  CALIB PARAMETER - Current Sensor Average Sampling Count (Recommended: 4)
avgCountTS              = 500,        //  CALIB PARAMETER - Temperature Sensor Average Sampling Count
baud                    = 96000;
float
inVoltageDivRatio       = 40.2156,    //  CALIB PARAMETER - Input voltage divider sensor ratio (change this value to calibrate voltage sensor)
outVoltageDivRatio      = 24.5000,    //  CALIB PARAMETER - Output voltage divider sensor ratio (change this value to calibrate voltage sensor)
vOutSystemMax           = 50.0000,    //  CALIB PARAMETER - 
cOutSystemMax           = 50.0000,    //  CALIB PARAMETER - 
voltageDropout          = 1.0000,     //  CALIB PARAMETER - Buck regulator's dropout voltage (DOV is present due to Max Duty Cycle Limit)
voltageBatteryThresh    = 1.5000,     //  CALIB PARAMETER - Power cuts-off when this voltage is reached (Output V)
currentInAbsolute       = 6.0000,    //  CALIB PARAMETER - Maximum Input Current The System Can Handle (A - Input)
currentOutAbsolute      = 8.0000,    //  CALIB PARAMETER - Maximum Output Current The System Can Handle (A - Input)
PPWM_margin             = 99.5000,    //  CALIB PARAMETER - Minimum Operating Duty Cycle for Predictive PWM (%)
PWM_MaxDC               = 97.0000,    //  CALIB PARAMETER - Maximum Operating Duty Cycle (%) 90%-97% is good
efficiencyRate          = 1.0000,     //  CALIB PARAMETER - Theroretical Buck Efficiency (% decimal)
currentMidPoint         = 2.5250,     //  CALIB PARAMETER - Current Sensor Midpoint (V)
currentSens             = 0.0000,     //  CALIB PARAMETER - Current Sensor Sensitivity (V/A)
currentSensV            = 0.0660,     //  CALIB PARAMETER - Current Sensor Sensitivity (mV/A)
vInSystemMin            = 10.000;     //  CALIB PARAMETER -

//===================================== SYSTEM PARAMETERS =========================================//
// Do not change parameter values in this section. The values below are variables used by system   //
// processes  //
//=================================================================================================//
bool
buckEnable            = 0,           // SYSTEM PARAMETER - Buck Enable Status
fanStatus             = 0,           // SYSTEM PARAMETER - Fan activity status (1 = On, 0 = Off)
bypassEnable          = 0,           // SYSTEM PARAMETER - 
chargingPause         = 0,           // SYSTEM PARAMETER - 
lowPowerMode          = 0,           // SYSTEM PARAMETER -     
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
avgStoreTS            = 0,           // SYSTEM PARAMETER - Temperature Sensor uses non invasive averaging, this is used an accumulator for mean averaging
temperature           = 0,           // SYSTEM PARAMETER -
sampleStoreTS         = 0,           // SYSTEM PARAMETER - TS AVG nth Sample
pwmMax                = 0,           // SYSTEM PARAMETER -
pwmMaxLimited         = 0,           // SYSTEM PARAMETER -
PWM                   = 0,           // SYSTEM PARAMETER -
PPWM                  = 0,           // SYSTEM PARAMETER -
pwmCh_BuckHIN         = 0,           // SYSTEM PARAMETER -
pwmCh_BuckLIN         = 1,           // SYSTEM PARAMETER -
deadTime              = 5,            // SYSTEM PARAMETER -
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
energySavings         = 0.0000,      // SYSTEM PARAMETER - Energy savings in fiat currency (Kshs)
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
buckEfficiency        = 0.0000,      // SYSTEM PARAMETER - Measure buck converter power conversion efficiency (only applicable to dual current sensor version)
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

// //Using second core of ESP
// void coreTwo(void * pvParameters){
//  setupWiFi();                                              //TAB#7 - WiFi Initialization
// //================= CORE0: LOOP (DUAL CORE MODE) ======================//
//   while(1){
//     Wireless_Telemetry();                                   //TAB#7 - Wireless telemetry (WiFi & Bluetooth)
    
// }}

//================== CORE1: SETUP (DUAL CORE MODE) ====================//
void setup() { 
  
  //SERIAL INITIALIZATION          
  Serial.begin(baud);                                   //Set serial baud rate
  Serial.println("> Serial Initialized");                   //Startup message
  
  //GPIO PIN INITIALIZATION
  pinMode(backflow_MOSFET, OUTPUT);
  pinMode(backflow_EN,OUTPUT);
  pinMode(buck_EN,OUTPUT);
  
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
  // xTaskCreatePinnedToCore(coreTwo,"coreTwo",10000,NULL,0,&Core2,0);

}

void loop() {
  // put your main code here, to run repeatedly:
  Device_Protection();          
  Charging_Algorithm();
}