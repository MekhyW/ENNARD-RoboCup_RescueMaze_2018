#include "Motors.h"
#include "Orientation.h"
#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Serial.println("begin");
  MotorsInitialize();
  IMUInitialize();
  delay(2000);
  ////////////////////////
  ReadCompass();
  int TempCompass=Compass;
  if(TempCompass<270){
    while(Compass<TempCompass+90){
      RotateRight(150);
      ReadCompass();
      Serial.println(Compass);
    }
  } else {
    while(Compass>180 || Compass<TempCompass-270){
      RotateRight(150);
      ReadCompass();
      Serial.println(Compass);
    }
  }
  RotateLeft(150);
  delay(100);
  MotorsStop();
}


void loop() {
  
}
