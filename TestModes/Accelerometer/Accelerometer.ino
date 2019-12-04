#include <I2Cdev.h>
#include <Wire.h>
#include <MPU6050.h>
#include "Motors.h"
#include "Display.h"
MPU6050 accelgyro;
int16_t GyroscopeX=0;
int16_t GyroscopeY=0;
int16_t GyroscopeZ=0;
int16_t AccelerationX=0;
int16_t AccelerationY=0;
int16_t AccelerationZ=0;
float Inclination=90;

void ReadAccel(){
  accelgyro.getMotion6(&AccelerationX, &AccelerationY, &AccelerationZ, &GyroscopeX, &GyroscopeY, &GyroscopeZ);
  Inclination = (map(AccelerationY, -16600, 17000, 0, 180)*0.5)+(Inclination*0.5);
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  accelgyro.initialize();
  accelgyro.setSleepEnabled(false);
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  MotorsInitialize();
  delay(1000);
  DisplayInitialize();
}

void loop() {
  MoveForward(150);
  ReadAccel();
  Serial.println(Inclination);
  Display(String(Inclination), "");
  delay(100);
}
