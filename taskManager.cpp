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
    LightTrackingAndServoControl(); // Call your servo control logic
    vTaskDelay(10 / portTICK_PERIOD_MS); // Small delay
  }
}

// Task 2: Send Data to Blynk (Core 1)
void SendToBlynkTask(void* parameter) {
  for (;;) {
    sendToBlynk(); // Call your Blynk sending logic
    vTaskDelay(100 / portTICK_PERIOD_MS); // Small delay
  }
}

// Function to create the tasks
void createTasks() {
  // Create Task 1: Light and Servo on Core 0
  xTaskCreatePinnedToCore(
    LightAndServoTask, 
    "LightAndServoTask", 
    4000, 
    NULL, 
    1, 
    &TaskLightServoControl, 
    0
  );

  // Create Task 2: Send to Blynk on Core 1
  xTaskCreatePinnedToCore(
    SendToBlynkTask, 
    "SendToBlynkTask", 
    4000, 
    NULL, 
    1, 
    &TaskSendToBlynk, 
    1
  );
}
