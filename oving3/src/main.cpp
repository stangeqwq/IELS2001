#include <Arduino.h>

#define UART_TX_PIN 1
#define UART_RX_PIN 3

#define LED_PIN 17
void setup() {
    Serial.begin(9600);

    Serial2.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN); //transmit uart data setup
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Done setup");
}

void loop() {
    Serial.println("Sent message");
    Serial.println("Trying to receive");
    if (Serial2.available()) {
        // Read data from Serial2
        String receivedData = Serial2.readStringUntil('\n');

        // Print received data to Serial (for debugging)
        Serial2.println("ESP32 received:" + receivedData); 

        // Process the received data as needed
        Serial.print("Received from Serial2: ");
        Serial.println(receivedData);
        if (receivedData == "On") {
            digitalWrite(LED_PIN, HIGH);
        }
        if (receivedData == "Off") {
            digitalWrite(LED_PIN, LOW);
        }
    }
    // Add any other tasks or code that needs to run in the loop
    delay(300);
}
