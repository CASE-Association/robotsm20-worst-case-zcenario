#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <VL53L0X.h>

#define NUMPINS 3

VL53L0X tof[] = {VL53L0X(), VL53L0X(), VL53L0X()};
Servo steering;

int tofpins[] = {2,3,4};

int dists[NUMPINS];

int M_in1 = 9;
int M_in2 = 10;
int M_pwm = 11;
int M_Stby = 12;

int steerpin = 5;

int ang;

bool tof_setup() {

  Wire.begin();

  // Turn off all TOFs
  for (int i = 0; i < NUMPINS; i++)
  {
    pinMode(tofpins[i], OUTPUT);
    delay(100);
    digitalWrite(tofpins[i], LOW);
    delay(100);
  }

  // Setup all TOFs, assign different adresses
  for (int i = 0; i < NUMPINS; i++)
  {
    // Turn on TOF[i]
    digitalWrite(tofpins[i], HIGH);
    delay(100);

    // Setup TOF[i]
    tof[i].setTimeout(500);
    
    if (!tof[i].init()) {
      Serial.print("Failed to boot tof on pin: ");
      Serial.println(tofpins[i]);
      return(false);
    }

    tof[i].setAddress(0x30+i);
    tof[i].startContinuous();

    delay(100);
  }

  return(true);
}

void tof_read()
{
  for (int i = 0; i < NUMPINS; i++)
  {
    dists[i] = tof[i].readRangeContinuousMillimeters();
  }
  
}

void motor_setup()
{
  pinMode(M_in1, OUTPUT);
  pinMode(M_in2, OUTPUT);
  pinMode(M_pwm, OUTPUT);
  pinMode(M_Stby, OUTPUT);

  digitalWrite(M_Stby, HIGH);
  digitalWrite(M_in1, HIGH);
  digitalWrite(M_in2, LOW);
}

void setup() {
  Serial.begin(115200);

  motor_setup();

  steering.attach(steerpin);

  if(!tof_setup()){ while(1); }
  
  Serial.println("setup complete");

  delay(1000);
}

void loop() {
  
  tof_read();

  int speed = dists[1]/4;
  speed = constrain(speed, 0, 128);

  analogWrite(M_pwm, speed);
  //Serial.println(speed);

  
  int sidediff = dists[0] - dists[2];
  ang = map(sidediff, -200, 200, -45, 45);

  ang = 90 + constrain(ang, -45, 45);
  steering.write(ang);
  

  /*
  for (int i = 0; i < NUMPINS; i++)
  {
    Serial.print(dists[i]);
    Serial.print(", ");
  }

  Serial.println();
  */

  delay(50);
}