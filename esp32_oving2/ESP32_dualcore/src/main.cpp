/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Arduino.h"

void setup() {
  Serial.begin(115200);
  Serial.print("setup() running on core ");
  Serial.println(xPortGetCoreID());
}

void loop() {
  Serial.print("loop() running on core ");
  Serial.println(xPortGetCoreID());
}