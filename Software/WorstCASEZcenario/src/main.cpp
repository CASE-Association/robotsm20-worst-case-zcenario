#include <Arduino.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("o");
  delay(1000);
  Serial.println("o/");
  delay(1000);
  Serial.println("o7");
  delay(1000);
}