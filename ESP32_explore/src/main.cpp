#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int read_p_1 = analogRead(39);
  int read_p_2 = analogRead(34);
  Serial.println(read_p_1);
  Serial.println(read_p_2);

  }
