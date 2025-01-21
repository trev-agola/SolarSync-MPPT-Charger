void setupWiFi(){
     WiFi.begin(ssid, pass);
    Serial.println("Connecting to WiFi...");
    
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000); // Wait for WiFi connection
    }
    Serial.println("\nWiFi Connected!");

    Blynk.config(auth); // Configure Blynk with the token
    Blynk.connect();    // Attempt to connect to Blynk server
    

    while (!Blynk.connected()) {
        Serial.println("Connecting to Blynk...");
        delay(1000); // Wait for Blynk connection
    }
    Serial.println("Blynk Connected!");
    WIFI = 1;
}

void Wireless_Telemetry(){
  
  ////////// WIFI TELEMETRY ////////// 
  if(enableWiFi==1&&WIFI==1){
    int LED1, LED2, LED3, LED4;                      //Declare LED brightness variable 
    if(buckEnable==1)      {LED1=200;}else{LED1=0;}  //BATTERY CHARGING STATUS
    if(PWMCharging>0 ){LED2=200;}else{LED2=0;}  //PWM STATUS
    if(batteryPercent<=10) {LED3=200;}else{LED3=0;}  //LOW BATTERY STATUS
    if(IUV==0)             {LED4=200;}else{LED4=0;}  //PV INPUT PRESENCE STATUS

    Blynk.run();  
    Blynk.virtualWrite(V0,powerInput); 
    Blynk.virtualWrite(V1,batteryPercent);
    Blynk.virtualWrite(V2,voltageInput);    
    Blynk.virtualWrite(V3,currentInput);   
    Blynk.virtualWrite(V4,voltageOutput); 
    Blynk.virtualWrite(V5,currentOutput); 
    Blynk.virtualWrite(V6,energySavings);       
    Blynk.virtualWrite(V7,LED1);               //LED - Battery Charging Status
    Blynk.virtualWrite(V8,LED2);               //LED - PWM
    Blynk.virtualWrite(V9,LED3);               //LED - Low Battery Charge Status
    Blynk.virtualWrite(V10,LED4);               //LED - PV Harvesting
    
    Blynk.virtualWrite(V11,PWM);  //PWM Value (Read)
    Blynk.virtualWrite(V15,Wh/1000); //energy Harversted in Wh
  }
  ////////// WIFI TELEMETRY ////////// 
  // if(enableBluetooth==1){
  //   //ADD BLUETOOTH CODE
  // }
  
} 
