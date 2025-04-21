// taskManager.cpp
#include "taskManager.h"
#include "servoControl.h"
#include "sendToBlynk.h"

// Define task handle variables
TaskHandle_t TaskLightServoControl;
TaskHandle_t TaskSendToBlynk;

// Task 1: Light Tracking and Servo Control (Core 0)
void LightAndServoTask(void* parameter) {
  for (;;) {
    LightTrackingAndServoControl();
    vTaskDelay(1 / portTICK_PERIOD_MS); // minimal delay for smoother operation
  }
}

// Task 2: Send Data to Blynk (Core 1)
void SendToBlynkTask(void* parameter) {
  for (;;) {
    sendToBlynk();
    vTaskDelay(100 / portTICK_PERIOD_MS); // slight delay for network operations
  }
}

// Function to create the tasks
void createTasks() {
  // Create Task 1: Light and Servo on Core 0
  xTaskCreatePinnedToCore(
    LightAndServoTask,      // Function to implement the task
    "LightAndServoTask",    // Name of the task
    3000,                   // Stack size (optimized)
    NULL,                   // Task input parameter
    2,                      // Priority (higher priority for real-time servo)
    &TaskLightServoControl, // Task handle
    0                       // Core where the task should run (Core 0)
  );

  // Create Task 2: Send to Blynk on Core 1
  xTaskCreatePinnedToCore(
    SendToBlynkTask,        // Function to implement the task
    "SendToBlynkTask",      // Name of the task
    4000,                   // Stack size (for Wi-Fi, Blynk)
    NULL,                   // Task input parameter
    1,                      // Priority (lower than servo task)
    &TaskSendToBlynk,       // Task handle
    1                       // Core where the task should run (Core 1)
  );
}
