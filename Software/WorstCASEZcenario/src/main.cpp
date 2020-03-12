#include <Arduino.h>

void setup() {
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
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