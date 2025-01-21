#define BLYNK_TEMPLATE_ID "TMPL2caJdmrhf"
#define BLYNK_TEMPLATE_NAME "SolarSync MPPT"
#define BLYNK_AUTH_TOKEN "YSeRJ1cABPNnI08EPfKENf9X5t8oX6fj"

#include <WiFi.h>                   //SYSTEM PARAMETER  - WiFi Library (By: Arduino)
#include <WiFiClient.h>             //SYSTEM PARAMETER  - WiFi Library (By: Arduino)
#include <BlynkSimpleEsp32.h>       //SYSTEM PARAMETER  - Blynk WiFi Library For Phone App 

TaskHandle_t Core2; // Handle for a task on Core 0
int WIFI = 0;
char 
auth[] = BLYNK_AUTH_TOKEN,   //   USER PARAMETER - Blynk Authentication Token (From email after registration)
ssid[] = "T",                   //   USER PARAMETER - Enter Your WiFi SSID
pass[] = "iwill_lookforyou";     //   USER PARAMETER - Enter Your WiFi Password



void TaskFunction(void *pvParameters) {
    Blynk.begin(auth,ssid,pass);
    WIFI = 1;
    Serial.println("Wifi Enabled");
    delay(5000);

  while (true) {
    Serial.print("Running task on Core: ");
    Serial.println(xPortGetCoreID()); // Display which core the task is running on
    Serial.print("Wifi Status: ");
    Serial.print(WIFI);
    delay(5000);
  }
}

void setup() {
  Serial.begin(115200); // Initialize Serial communication
  delay(100);           // Ensure Serial initialization completes

  // Create a task and pin it to Core 0
  xTaskCreatePinnedToCore(
    TaskFunction,  // Task function
    "TaskOnCore0", // Task name
    4000,          // Stack size
    NULL,          // Parameters
    1,             // Priority
    &Core2,        // Task handle (to manage this task later)
    0              // Pin to Core 0
  );

  Serial.println("Task created on Core 0");
}

void loop() {
  // Main application code here
  Serial.println("Main loop running on Core 1");
  delay(5000);
}
