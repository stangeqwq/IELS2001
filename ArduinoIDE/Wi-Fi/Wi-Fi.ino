#include <WiFi.h>

const char* ssid = "NTNU-IOT";
const char* password = "";

const int LED = 18;
const int channelLED = 0; 

void setup() {
  Serial.begin(9600);
  Serial.println("Trying to connect to");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());
  ledcSetup(channelLED, 2000, 8);
  ledcAttachPin(LED, channelLED);
  ledcWrite(channelLED, 0);
}

void loop() {
  for (int i = 0; i < 255; i++) {
    ledcWrite(channelLED, i);
    delay(10);
  }
  for (int i = 255; i > 0; i--) {
    ledcWrite(channelLED, i);
    delay(10);
  }

}
