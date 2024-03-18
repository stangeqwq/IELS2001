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
esp_now_peer_info_t peerInfo;

// Callback when data is sent
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}
void onDataRecv(const uint8_t* mac, const uint8_t* callbackData, int len) {
  memcpy(&incomingData, callbackData, sizeof(callbackData)); // error in example code
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingSensorData = incomingData.sensorData;
  incomingMsg = incomingData.msg1;
  incomingNum = incomingData.num1;
  Serial.println(incomingSensorData);
  Serial.println(incomingMsg);
  Serial.println(incomingNum);
}
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(onDataSent);
  //register recv callback function that will be called when data is received
 

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
   esp_now_register_recv_cb(onDataRecv);

}
 
void loop() {
  outgoingData.sensorData = analogRead(sensorPin);
  outgoingData.msg1 = "The cake is a lie!";
  outgoingData.num1 = 420;

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t*) &outgoingData, sizeof(outgoingData));

  if (result == ESP_OK) {
    Serial.println("Sent successfully");
  } else {
    Serial.println("Error sending data");
  }

  delay(1000);
}