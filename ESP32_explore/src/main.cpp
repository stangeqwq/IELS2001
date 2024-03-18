#include "Arduino.h"

void setup() {
  Serial.begin(9600);

}

void loop() {
  Serial.println("Dette er bare en test");
  delay(500);
}