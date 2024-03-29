#include <WiFi.h>
#include <ESP32Servo.h>
//#include <HTTPClient.h>
static const int servoPin = 13;

Servo servo1;

const char *ssid = "NTNU-IOT";
const char *password = "";

const int LED = 18;
const int BUZZ = 23;
const int channelLED = 15;
const int channelBUZZ = 14;

void setup()
{
  /*
  if ((WiFi.status() == WL_CONNECTED)){
    HTTPClient http;
    http.begin("http://example.com/index.html");
    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed error: %s\n", http.error);
    }
    http.end;

  } else {
    Serial.println("Lost internet connection");
  }
*/


  Serial.begin(115200);
  
  Serial.println("Trying to connect to");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  ledcSetup(channelLED, 2000, 8);
  ledcSetup(channelBUZZ, 2000, 8);
  ledcAttachPin(BUZZ, channelBUZZ);
  ledcAttachPin(LED, channelLED);
  ledcWrite(channelLED, 0);

  servo1.attach(servoPin);
  
}

void loop()
{
  for (int i = 0; i < 255; i++)
  {
    ledcWrite(channelLED, i);
    delay(10);
  }
  ledcWriteTone(channelBUZZ, 2000);
  for (int i = 255; i > 0; i--)
  {
    ledcWrite(channelLED, i);
    delay(10);
  }
  ledcWriteTone(channelBUZZ, 1000);
  
  
  for (int posDegrees = 0; posDegrees <= 180; posDegrees++)
  {
    servo1.write(posDegrees);
    delay(20);
  }

  for (int posDegrees = 180; posDegrees >= 0; posDegrees--)
  {
    servo1.write(posDegrees);
    delay(20);
  }
  
}
