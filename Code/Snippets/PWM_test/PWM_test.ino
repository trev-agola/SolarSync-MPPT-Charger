#define buck_HIN         33          //SYSTEM PARAMETER - Buck MOSFET Driver High Side PWM Pin
#define buck_LIN         26          //SYSTEM PARAMETER - Buck MOSFET Driver Low Side PWM Pin
#define buck_EN          25          //SYSTEM PARAMETER - Buck MOSFET Driver Enable Pin

int
pwmCh_BuckHIN         = 0,           // SYSTEM PARAMETER -
pwmCh_BuckLIN         = 1,           // SYSTEM PARAMETER -
deadTime              = 80,         // SYSTEM PARAMETER -
pwmResolution           = 11,          //  USER PARAMETER - PWM Bit Resolution 
pwmFrequency            = 39000,       //  USER PARAMETER - PWM Switching Frequency - Hz (For Buck)
pwmMax                = 0,           // SYSTEM PARAMETER -
PWM                   = 0,           // SYSTEM PARAMETER -
pwmMaxLimited         = 0;           // SYSTEM PARAMETER -



float
PPWM_margin             = 99.5000,    //  CALIB PARAMETER - Minimum Operating Duty Cycle for Predictive PWM (%)
PWM_MaxDC               = 92.0000;    //  CALIB PARAMETER - Maximum Operating Duty Cycle (%) 90%-97% is good

void complementaryPWM(int dutyCycle) {
  int dutyHIN = dutyCycle - deadTime;                 // High-side duty cycle adjusted for deadtime
  int dutyLIN = (pwmMaxLimited - dutyCycle) - deadTime;      // Low-side duty cycle adjusted for deadtime

    // Prevent overlap: Ensure high-side duty is not negative
  if (dutyHIN < 0) {
    dutyHIN = 0;  // Prevent underflow on high-side
  }

  if (dutyLIN < 0) {  
    dutyLIN = 0;  // Prevent underflow on low-side
  }

  ledcWriteChannel(pwmCh_BuckHIN,dutyHIN);
  
ledcWriteChannel(pwmCh_BuckLIN,dutyLIN);    //Set PWM duty cycle and write to GPIO when buck is enabled
Serial.println("High side PWM: ");
Serial.println(dutyHIN);
Serial.println("Low side PWM: ");
Serial.println(dutyLIN);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                                   //Set serial baud rate
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
}

void loop() {

  complementaryPWM(1500);
  delay(1000);
}
