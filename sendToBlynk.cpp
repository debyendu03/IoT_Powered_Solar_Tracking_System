#define BLYNK_TEMPLATE_ID "TMPL3Y95Jqa3r"
#define BLYNK_TEMPLATE_NAME "IoT Powered Solar Tracking System"
#define BLYNK_AUTH_TOKEN "UYV1OePmeVDxN0oYqXjUAJMCcVhza4iz"

#include <BlynkSimpleEsp32.h>  
#include <WiFi.h>
#include "sendToBlynk.h" 

bool sendDataEnabled = false;
unsigned long lastSendTime = 0;
unsigned long sendInterval = 30000; // Default: 30 seconds

// Button on/off control (V5)
BLYNK_WRITE(V5) {
  int buttonState = param.asInt();
  sendDataEnabled = (buttonState == 1);
}

// Interval control (V6) in minutes
BLYNK_WRITE(V6) {
  int minutes = param.asInt();
  
  if (minutes >= 1 && minutes <= 60) {
    sendInterval = minutes * 60000UL; // convert minutes to milliseconds
  } else {
    sendInterval = 30000; // if somehow invalid, fallback to default 30 seconds
  }
}

void initWiFiAndBlynk(const char* auth, const char* ssid, const char* pass) {
  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass);
}

void sendToBlynk() {
  Blynk.run();

  if (sendDataEnabled) {
    unsigned long currentMillis = millis();

    if (currentMillis - lastSendTime >= sendInterval) {
      lastSendTime = currentMillis;

      INA226Data sensorData = getINA226Value();
      Blynk.virtualWrite(V0, sensorData.shuntVoltage_mV);
      Blynk.virtualWrite(V1, sensorData.busVoltage_V);
      Blynk.virtualWrite(V2, sensorData.loadVoltage_V);
      Blynk.virtualWrite(V3, sensorData.current_mA);
      Blynk.virtualWrite(V4, sensorData.power_mW);
    }
  }
}
