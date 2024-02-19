#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#define LIGHT_SENSOR_PIN 36 // ESP32 pin GIOP36 (ADC0)
// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int potPin = 34;
int sensorDataArr[] = {0, 0};

// SSID & Password
const char* ssid = "Joshua's ESP32 server";  // Enter your SSID here
const char* password = "esp32password12345678";  //Enter your Password here

// IP Address details
IPAddress local_ip(192, 168, 200, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(7777);

// Handle root url (/)
void handle_root();
String GetHTML_Data(int sensorDataArr[]);

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.print("Trying to connect to:");
  // Create SoftAP
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
   Serial.print("Connect to My access point: ");
  Serial.println(ssid);

  server.on("/", handle_root);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);

}

void loop() {
  server.handleClient();
  

  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  int potValue = analogRead(potPin);
  sensorDataArr[0] = analogValue;
  sensorDataArr[1] = potValue;

  Serial.println(potValue);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 40) {
    Serial.println(" => Dark");
  } else if (analogValue < 800) {
    Serial.println(" => Dim");
  } else if (analogValue < 2000) {
    Serial.println(" => Light");
  } else if (analogValue < 3200) {
    Serial.println(" => Bright");
  } else {
    Serial.println(" => Very bright");
  }

  delay(500);
}

String GetHTML_Data(int sensorDataArr[]) {
  // HTML & CSS contents which display on web server
  String HTML = "<!DOCTYPE html>"
  "<html>"
  "<head>"
  "<title>Sensordata</title>"
  "</head>"
  "<body>"
  "<h1>Sensordata</h1>";
  HTML += "<h2>Light Sensor: ";
  HTML += sensorDataArr[0];
  HTML += "</h2>";
  HTML += "<h2>Potentiometer: ";
  HTML += sensorDataArr[1];
  HTML += "</h2>";
  HTML += "</body>";
  HTML += "</html>";
  return HTML;
}

void handle_root() {
  server.send(200, "text/html", GetHTML_Data(sensorDataArr));
}
