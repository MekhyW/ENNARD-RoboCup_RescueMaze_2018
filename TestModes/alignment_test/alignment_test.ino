#include "Display.h"
#include "Ultrasound.h"
#include "PID.h"
#include "Motors.h"

void setup() {
  MotorsInitialize();
  DisplayInitialize();
  Serial.begin(9600);
  delay(1000);
  Align();
  //Wobble();
  //AvoidLeft();
  MotorsStop();
}

void loop() {
  
}


void Align(){
  MotorsStop();
  //LockEncoders();
  ReadUltrassound(true, true, true, true, true, true, true, true, true);
  if(USFrontCT<99 && ((USFrontA==99&&USFrontB<99)||(USFrontA<99&&USFrontB==99))){
    Display("out of bounds", "");
    if(USFrontA<USFrontB){
      AvoidRight();
    } else if(USFrontB<USFrontA){
      AvoidLeft();
    }
    ReadUltrassound(true, true, true, true, true, true, true, true, true);
  }
  if(USBackA<30 && USBackB<30){
    Display("bump back", "");
    while((USBackA>13&&USBackA<30)||(USBackB>13&&USBackB<30)){
      MoveBackwards(150);
      ReadUltrassound(false, false, false, false, false, true, true, false, false);
      //CheckVictim();
    }
    delay(200);
    MoveForward(150);
    delay(150);
    MotorsStop();
  } else if(USFrontCT<30 && USFrontA<30 && USFrontB<30){
    Display("bump fwd", "");
    while((USFrontA>13&&USFrontA<30)||(USFrontB>13&&USFrontB<30)){
      MoveForward(150);
      ReadUltrassound(true, false, true, false, false, false, false, false, false);
      //CheckVictim();
    }
    delay(200);
    MoveBackwards(150);
    delay(150);
    MotorsStop();
  }
  //UnlockEncoders();
}


void AvoidLeft(){
  //LockEncoders();
  RotateLeft(150);
  delay(200);
  MoveBackwards(150);
  delay(200);
  RotateRight(150);
  delay(300);
  MoveForward(150);
  delay(200);
  RotateLeft(150);
  delay(150);
  //UnlockEncoders();
}

void AvoidRight(){
  //LockEncoders();
  RotateRight(150);
  delay(200);
  MoveBackwards(150);
  delay(200);
  RotateLeft(150);
  delay(300);
  MoveForward(150);
  delay(200);
  RotateRight(150);
  delay(150);
  //UnlockEncoders();
}

void Wobble(){
  //LockEncoders();
  ReadUltrassound(false, false, false, true, true, false, false, true, true);
  if(USLeftA>17 && USLeftA<30 && USLeftB<30){
      Display("wobble left", "");
      while(USLeftA>17 && USLeftA<30 && USLeftB<30){
        ReadUltrassound(false, false, false, false, false, false, false, false, true);
        RotateRight(150);
        delay(50);
        MoveBackwards(200);
        delay(50);
        RotateLeft(150);
        delay(50);
        MoveForward(200);
        delay(50);  
      }
  } else if(USRightA>17 && USRightA<30 && USRightB<30){
      Display("wobble right", "");
      while(USRightA>17 && USRightA<30 && USRightB<30){
        ReadUltrassound(false, false, false, true, false, false, false, false, false);
        RotateLeft(150);
        delay(50);
        MoveBackwards(200);
        delay(50);
        RotateRight(150);
        delay(50);
        MoveForward(200);
        delay(50);  
      }
  } else if(USRightA<14 && USRightB<30){
      Display("wobble left", "");
      while(USRightA<14 && USRightB<30){
        ReadUltrassound(false, false, false, true, false, false, false, false, false);
        RotateRight(150);
        delay(50);
        MoveBackwards(200);
        delay(50);
        RotateLeft(150);
        delay(50);
        MoveForward(200);
        delay(50);  
      }
  } else if(USLeftA<14 && USLeftB<30){
      Display("wobble right", "");
      while(USLeftA<14 && USLeftB<30){
        ReadUltrassound(false, false, false, false, false, false, false, false, true);
        RotateLeft(150);
        delay(50);
        MoveBackwards(200);
        delay(50);
        RotateRight(150);
        delay(50);
        MoveForward(200);
        delay(50);  
      }
  }
  //UnlockEncoders();
}
