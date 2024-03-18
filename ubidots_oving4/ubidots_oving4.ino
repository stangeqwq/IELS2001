#include <UbiConstants.h>
#include <UbiTypes.h>
#include <UbidotsEsp32Mqtt.h>

#include <UbiConstants.h>
#include <UbiTypes.h>
#include <ESP32Servo.h>

/******************************************
 *
 * This example works for both Industrial and STEM users.
 *
 * Developed by Jose Garcia, https://github.com/jotathebest/
 *
 * ****************************************/

/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsEsp32Mqtt.h"

/****************************************
 * Define Constants
 ****************************************/
const char *UBIDOTS_TOKEN = "BBUS-WMqcC4EuFhK3pBOhtO5bkFD3BeGgdW";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "NTNU-IOT";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "esp32";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL1 = "led1"; // Put here your Variable label to which data  will be published
const char *VARIABLE_LABEL2 = "led2";
const char *VARIABLE_LABEL3 = "servo1"; // Put here your Variable label to which data  will be published
const char *VARIABLE_LABEL4 = "servo2";
const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds

unsigned long timer;
uint8_t analogPin = 34; // Pin used to read data from GPIO34 ADC_CH6.
uint8_t led1Pin = 16; 
uint8_t led2Pin = 17; 
Ubidots ubidots(UBIDOTS_TOKEN);
Servo servo1; 
Servo servo2; 

/****************************************
 * Auxiliar Functions
 ****************************************/
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String s = "";
  String t = "";

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
    s += (char) payload[i];
  }
  for (int i = 0; i < strlen(topic); i++) {
    t += (char) topic[i];
  }
      // Convert String to char array
  char charArray[s.length() + 1]; // +1 for null terminator
  s.toCharArray(charArray, sizeof(charArray));

  // Convert char array to float
  float servoValue = atof(charArray);
  Serial.println("");
  Serial.println(s);
  Serial.println(t);
  Serial.println(servoValue);

  if (s == "1.0" && t == "/v2.0/devices/esp32/led1/lv") {
      digitalWrite(led1Pin, HIGH);
    } else if (t == "/v2.0/devices/esp32/led1/lv"){
      digitalWrite(led1Pin, LOW);
    }
  if (s == "1.0" && t == "/v2.0/devices/esp32/led2/lv") {
      digitalWrite(led2Pin, HIGH);
    } else if (t == "/v2.0/devices/esp32/led2/lv") {
      digitalWrite(led2Pin, LOW);
    }
  
    if (s == "1.0" && t == "/v2.0/devices/esp32/led1/lv") {
      digitalWrite(led1Pin, HIGH);
    } else if (t == "/v2.0/devices/esp32/led1/lv"){
      digitalWrite(led1Pin, LOW);
    }
  if (t == "/v2.0/devices/esp32/servo2/lv") {
      servo2.write(int(servoValue) * (360/100)); // servoValue er % av 180 grader
      delay(15);
    } 
  
  if (t == "/v2.0/devices/esp32/servo1/lv") {
    servo1.write(int(servoValue) * (360/100));
    delay(15);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  ubidots.setDebug(true);  // uncomment this to make debug messages available
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
  ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL1); // Insert the dataSource and Variable's Labels
  ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL2); // Insert the dataSource and Variable's Labels
  ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL3); // Insert the dataSource and Variable's Labels
  ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL4); // Insert the dataSource and Variable's Labels
  Serial.println("subscribed");

  servo1.setPeriodHertz(50);    // standard 50 hz servo
	servo1.attach(32, 500, 2400); // attaches the servo on pin 18 to the servo object
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep
    servo2.setPeriodHertz(50);    // standard 50 hz servo
	servo2.attach(13, 500, 2400); // attaches the servo on pin 18 to the servo object
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (!ubidots.connected())
  {
    ubidots.reconnect();
    ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL1); // Insert the dataSource and Variable's Labels
    ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL2); // Insert the dataSource and Variable's Labels
    ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL3); // Insert the dataSource and Variable's Labels
    ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL4); // Insert the dataSource and Variable's Labels
    Serial.println("subscribed");
  }

  ubidots.loop();
}