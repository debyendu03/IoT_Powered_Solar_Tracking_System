// otaManager.cpp
#include "otaManager.h"
#include <ArduinoOTA.h>

// Easy to change OTA password
const char* otaPassword = "update";  // <-- Change this password anytime

void setupOTA() {
  ArduinoOTA.setPassword(otaPassword); // Protect OTA with password
  ArduinoOTA.begin(); // Start OTA service
}

void handleOTA() {
  ArduinoOTA.handle(); // Keep OTA service running
}
