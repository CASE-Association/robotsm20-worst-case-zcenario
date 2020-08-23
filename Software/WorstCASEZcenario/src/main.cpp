#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <VL53L0X.h>

#define NUMPINS 3

VL53L0X tof[] = {VL53L0X(), VL53L0X(), VL53L0X()};

int tofpins[] = {2, 3, 4};

int dists[NUMPINS];


bool setup_tof() {

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
      return(false);
    }

    tof[i].setAddress(0x30+i);
    tof[i].startContinuous();

    delay(10);
  }

  return(true);
}

void read_tof()
{
  for (int i = 0; i < NUMPINS; i++)
  {
    dists[i] = tof[i].readRangeContinuousMillimeters();
  }
  
}
void setup() {
  Serial.begin(9600);
  
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  if(!setup_tof()){ while(1); }
  
  Serial.println("setup complete");

  delay(1000);
}


void loop() {

  read_tof();

  for (int i = 0; i < NUMPINS; i++)
  {
    Serial.print(dists[i]);
    Serial.print(", ");
  }

  Serial.println();

  delay(1000);
}

