// taskManager.h
#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <Arduino.h>

// Declare the task handle variables
extern TaskHandle_t TaskLightServoControl;
extern TaskHandle_t TaskSendToBlynk;

// Declare the task functions
void LightAndServoTask(void* parameter);
void SendToBlynkTask(void* parameter);

// Declare the function to create tasks
void createTasks();

#endif
