#include <WiFi.h>
//#include <ESP32Servo.h>
static const int servoPin = 13;

//Servo servo1;

const char *ssid = "NTNU-IOT";
const char *password = "";

const int LED = 18;
const int BUZZ = 23;
const int channelLED = 0;
const int channelBUZZ = 1;
const int channelSERVO1 = 2;

void setup()
{
  Serial.begin(9600);
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

  /*
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo1.setPeriodHertz(50);    // standard 50 hz servo
  servo1.attach(servoPin, 1000, 2000);
  */
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
  /*
  for (int posDegrees = 0; posDegrees <= 180; posDegrees++)
  {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }

  for (int posDegrees = 180; posDegrees >= 0; posDegrees--)
  {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
  */
}
