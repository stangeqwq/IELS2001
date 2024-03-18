#include <Arduino.h>

const int led_pin = 14;
const int button_pin = 25;
int button_state = 0;
int last_button_state = 0;
int led_state = 0;
void setup() 
{
    pinMode(led_pin, OUTPUT);
    pinMode(button_pin, INPUT_PULLUP);
    Serial.begin(9600);
    Serial.println("Done setup");
}

int counter = 0;

void loop() {
  last_button_state = button_state;
  button_state = digitalRead(button_pin);
  Serial.println(counter);
  Serial.print("button_state");
  Serial.println(button_state);
  counter ++;
  esp_sleep_enable_timer_wakeup(2 * 1000000); //light sleep for 2 seconds
  esp_light_sleep_start(); 
    if (last_button_state == 1 && button_state == 0) {
      Serial.println("The button is pressed");

      // toggle state of LED
      led_state = !led_state;

      // control LED arccoding to the toggled state
      digitalWrite(led_pin, led_state);
    } 
  delay(100);
}