#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <VL53L0X.h>

#define NUMPINS 2

VL53L0X tof[2] = {VL53L0X(), VL53L0X()};

int tofpins[] = {2, 3};


void setup() {
  Serial.begin(9600);
  
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Wire.begin();

  // Turn off all TOFs
  for (int i = 0; i < NUMPINS; i++)
  {
    pinMode(tofpins[i], OUTPUT);
    delay(10);
    digitalWrite(tofpins[i], LOW);
    delay(10);
  }

  // Setup all TOFs, assign different adresses
  for (int i = 0; i < NUMPINS; i++)
  {
    // Turn on TOF[i]

    digitalWrite(tofpins[i], HIGH);

    // Setup TOF[i]
    tof[i].setTimeout(500);
    
    if (!tof[i].init()) {
      Serial.print("Failed to boot tof on pin: ");
      Serial.println(tofpins[i]);
      while(1);
    }

    tof[i].setAddress(0x30+i);
    tof[i].startContinuous();

    delay(10);
  }
  
  Serial.println("setup complete");

  delay(1000);
}


void loop() {

  for (int i = 0; i < NUMPINS; i++)
  {
    Serial.println(tof[i].readRangeContinuousMillimeters());
    if (tof[i].timeoutOccurred()) { Serial.println("^ TIMEOUT"); }
  }
}

