#include <Arduino.h>

  int LED = 13;
void setup() {
  pinMode(LED,OUTPUT);
}

void loop() {
  digitalWrite(LED,1);
  delay(250);
  digitalWrite(LED,0);
  delay(250);
  digitalWrite(LED,1);
  delay(250);
  digitalWrite(LED,0);
  delay(250);
  digitalWrite(LED,1);
  delay(250);
  digitalWrite(LED,0);
  delay(250);
  digitalWrite(LED,1);
  delay(1000);
  digitalWrite(LED,0);
  delay(1000);
  digitalWrite(LED,1);
  delay(2000);
  digitalWrite(LED,0);
  delay(2000);
}