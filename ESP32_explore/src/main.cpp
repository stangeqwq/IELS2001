#include <esp_now.h>
#include <WiFi.h>

const int sensorPin = 32;
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // MAC-address of receiver board

float outgoingSensorData;
float incomingSensorData;
char* incomingMsg;
float incomingNum;

String success;
typedef struct struct_message {
  float sensorData;
  char* msg1;
  float num1;
} struct_message;

struct_message outgoingData;
struct_message incomingData;
void setup() {

}
 
void loop() {

}