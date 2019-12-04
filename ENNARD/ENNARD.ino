// ENNARD Rescue Maze Robot  (former Project Linker)
// Escola de Robótica ABC Marcelo Salles
// VERSION: 7.8
#include <Wire.h>
#include "Display.h"
#include "Orientation.h"
#include "Temperature.h"
#include "Reflection.h"
#include "Ultrasound.h"
#include "PID.h"
#include "Motors.h"
#include "Encoders.h"
#include "Cameras.h"
#include "Map.h"


void setup() {
  Serial.begin(9600);
  DisplayInitialize();
  CamsInitialize();
  ReflectionInitialize();
  TemperatureInitialize();
  MotorsInitialize();
  PressToStart(true);
  IMUInitialize();
  floodfill[currentfloor][PositionX][PositionY]=1;
}


void loop() {
  ResetEncoders();
  while(EncPulseEA<TileDist || EncPulseEB<TileDist || EncPulseDA<TileDist || EncPulseDB<TileDist){
    UpdateEncoders();
  	CheckBackup();
    ReadUltrassound(true, true, true, true, true, true, true, true, true);
    if(USFrontCT<15 && USFrontB<15){
      Display("", "loop break");
      MotorsStop();
      delay(500);
      MoveBackwards(150);
      delay(100);
      MotorsStop();
      break;
    }
    CheckVictim();
    if(USFrontA<15 && USFrontCT>30 && USFrontB>30 && USLeftA>30 && (currentfloor!=1||PositionX!=15||PositionY!=15)){
      AvoidLeft();
    } 
    if(USFrontB<15 && USFrontCT>30 && USFrontA>30 && USRightA>30 && (currentfloor!=1||PositionX!=15||PositionY!=15)){
      AvoidRight();
    }
    ReadReflection();
    if(ReflectLeft>TrapLimit && ReflectRight>TrapLimit){
      BlackZone();
      break;
    }
    if(currentfloor==1&&PositionX==15&&PositionY==15){
      MoveForward(200);
    } else {
      MoveForwardPID(200); 
    }
    Display(String(ReflectLeft), String(ReflectRight));
  }
  NextMove();
}









void Align(){
  LockEncoders();
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
    MoveBackwards(150);
    while((USBackA>13&&USBackA<30)||(USBackB>13&&USBackB<30)){
      MoveBackwards(150);
      ReadUltrassound(false, false, false, false, false, true, true, false, false);
      CheckVictim();
    }
    delay(200);
    MoveForward(150);
    delay(150);
    MotorsStop();
  } else if(USFrontCT<30 && USFrontA<30 && USFrontB<30){
    MotorsStop();
    Display("bump fwd", "");
    MoveForward(150);
    while((USFrontA>13&&USFrontA<30)||(USFrontB>13&&USFrontB<30)){
      MoveForward(150);
      ReadUltrassound(true, false, true, false, false, false, false, false, false);
      CheckVictim();
    }
    delay(200);
    MoveBackwards(150);
    delay(150);
    MotorsStop();
  }
  UnlockEncoders();
}



void AvoidLeft(){
  LockEncoders();
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
  UnlockEncoders();
}

void AvoidRight(){
  LockEncoders();
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
  UnlockEncoders();
}


void Wobble(){
  LockEncoders();
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
  UnlockEncoders();
}


void Retreat(){
  MotorsStop();
  EA.write(EncPulseEA*1.2);
  EB.write(EncPulseEB*1.2);
  DA.write(EncPulseDA*1.2);
  DB.write(EncPulseDB*1.2);
  while(EncPulseAvg>0){
    MoveBackwards(200);
    EncPulseEA=EA.read();
    EncPulseEB=EB.read();
    EncPulseDA=DA.read();
    EncPulseDB=DB.read();
    EncPulseAvg=(EncPulseEA+EncPulseEB+EncPulseDA+EncPulseDB)/4;
    CheckVictim();
    CheckBackup();
  }
  MotorsStop();
}


void TurnLeft(){
  Wobble();
  MotorsStop();
  MotorsStop();
  MotorsStop();
  Display("<<<", "");
  ResetEncoders();
  while(EncPulseEA<TurnDist || EncPulseEB<TurnDist || EncPulseDA<TurnDist || EncPulseDB<TurnDist){
    RotateLeft(200);
    UpdateEncoders();
    CheckBackup();
    if(EncPulseAvg<(TurnDist/3)){
      CheckVictim();
    }
  }
  MotorsStop();
  if(Quadrant==1){
    Quadrant=4;
  } else if(Quadrant==2){
    Quadrant=3;
  } else if(Quadrant==3){
    Quadrant=1;
  } else if(Quadrant==4){
    Quadrant=2;
  }
  RelativeXY();
  ResetEncoders();
  Wobble();
  Align();
  Wobble();
}



void TurnRight(){
  Wobble();
  MotorsStop();
  MotorsStop();
  MotorsStop();
  Display(">>>", "");
  ResetEncoders();
  while(EncPulseEA<TurnDist || EncPulseEB<TurnDist || EncPulseDA<TurnDist || EncPulseDB<TurnDist){
    RotateRight(200);
    UpdateEncoders();
    CheckBackup();
    if(EncPulseAvg<(TurnDist/3)){
      CheckVictim();
    }
  }
  MotorsStop();
  if(Quadrant==1){
    Quadrant=3;
  } else if(Quadrant==2){
    Quadrant=4;
  } else if(Quadrant==3){
    Quadrant=2;
  } else if(Quadrant==4){
    Quadrant=1;
  }
  RelativeXY();
  ResetEncoders();
  Wobble();
  Align();
  ReadUltrassound(false, false, false, true, true, false, false, true, true);
  Wobble();
}


void TurnBackwards(){
  if(USLeftA>=USRightA){
    TurnLeft();
    TurnLeft();
  } else {
    TurnRight();
    TurnRight();
  }
}


void CheckVictim(){
      ReadTemperature();
      ReadCams();
      if(TemperatureL>=VHeatThreshold && USLeftA<30 && USLeftB<30 && ((EncPulseAvg<=TileDist/2&&heatmap[currentfloor][PositionX][PositionY]==0)||(EncPulseAvg>TileDist/2&&heatmap[currentfloor][ForwardX][ForwardY]==0))){
        Victim(1, 1);
      } else if(TemperatureR>=VHeatThreshold && USRightA<30 && USRightB<30 && ((EncPulseAvg<=TileDist/2&&heatmap[currentfloor][PositionX][PositionY]==0)||(EncPulseAvg>TileDist/2&&heatmap[currentfloor][ForwardX][ForwardY]==0))){
        Victim(1, 2);
      } else if((MVLeftChar==Decode_H || MVLeftChar==Decode_S || MVLeftChar==Decode_U) && USLeftA<30 && USLeftB<30 && USLeftA>13 && (EncPulseAvg<(TileDist*0.25)||EncPulseAvg>(TileDist*0.75)) && ((EncPulseAvg<=TileDist/2&&heatmap[currentfloor][PositionX][PositionY]==0)||(EncPulseAvg>TileDist/2&&heatmap[currentfloor][ForwardX][ForwardY]==0))){
        if(MVLeftChar==Decode_H){
          Victim(2, 1);
        }
        if(MVLeftChar==Decode_S){
          Victim(3, 1);
        }
        if(MVLeftChar==Decode_U){
          Victim(4, 1);
        }
      } else if((MVRightChar==Decode_H || MVRightChar==Decode_S || MVRightChar==Decode_U) && USRightA<30 && USRightB<30 && USRightA>13 && (EncPulseAvg<(TileDist*0.25)||EncPulseAvg>(TileDist*0.75)) && ((EncPulseAvg<=TileDist/2&&heatmap[currentfloor][PositionX][PositionY]==0)||(EncPulseAvg>TileDist/2&&heatmap[currentfloor][ForwardX][ForwardY]==0))){
        if(MVRightChar==Decode_H){
          Victim(2, 2);
        }
        if(MVRightChar==Decode_S){
          Victim(3, 2);
        }
        if(MVRightChar==Decode_U){
          Victim(4, 2);
        }
      }
}


void Victim(int type, int side){
  MotorsStop();
  if(type==1){
    Display("Victim Found:", "Heated");
  } else if(type==2){
    Display("Victim Found:", "Visual HARMED");
  } else if(type==3){
    Display("Victim Found:", "Visual STABLE");
  } else if(type==4){
    Display("Victim Found:", "Visual UNHARMED");
  }
  if(EncPulseAvg<=TileDist/2){
    heatmap[currentfloor][PositionX][PositionY]=1;
  } else {
    heatmap[currentfloor][ForwardX][ForwardY]=1;
  }
  if(type==1){
    Blink_for_five();
  }
  if(type==4 || KitCounter>=12){
    Blink_for_five();
  } else if(side==1){
    DeployKitLeft();
    if(type==2){
      DeployKitLeft();
    }
  } else if(side==2){
    DeployKitRight();
    if(type==2){
      DeployKitRight();
    }
  }
}


void BlackZone(){
  MotorsStop();
  Display("Trap ahead", String(EncPulseAvg));
  Retreat();
  trapmap[currentfloor][ForwardX][ForwardY]=1;
}


void Ramp(){
  if(Inclination>=110){
    Display("Ramping", "UP");
    while(USFrontCT>15 || USFrontA>15 || USFrontB>15){
      ReadUltrassound(true, true, true, true, true, false, false, true, true);
      MoveForwardPID(255);
      CheckBackup();
    }
    currentfloor++;
    if(floodfill[currentfloor][BackwardsX][BackwardsY]==0){
      floodfill[currentfloor][BackwardsX][BackwardsY]=1;
    }
  } else if(Inclination<=70){
    Display("Ramping", "DOWN");
    while(USFrontCT>15 || USFrontA>15 || USFrontB>15){
      ReadUltrassound(true, true, true, true, true, false, false, true, true);
      MoveForwardPID(130);
      CheckBackup();
    }
    currentfloor--;
    if(floodfill[currentfloor][BackwardsX][BackwardsY]==0){
      floodfill[currentfloor][BackwardsX][BackwardsY]=1;
    }
  }
}



void NextMove(){
  //CHECKS
  if(EncPulseAvg>=(TileDist/2)){
    CalculateDisplacement();
    ResetEncoders();
  }
  if(USLeftA<30 && USRightA<30 && USFrontCT>30){
    MotorsStop();
    delay(1000);
    ReadAccel();
    if(Inclination>=110 || Inclination<=70){
      Ramp();
    } else {
      CheckVictim();
    }
  }
  Align();
  ReadReflectionPure();
  if(ReflectLeft<=CheckpointLimit && ReflectRight<=CheckpointLimit && (PositionX!=PositionXBackup || PositionY!=PositionYBackup)){
      UpdateBackup();
  }
  bool IsForwardAvailable=true;
  bool IsRightAvailable=true;
  bool IsLeftAvailable=true;
  bool IsBackwardsAvailable=true;
  ReadUltrassound(false, true, false, true, true, true, true, true, true);
  if(USFrontCT<30 || trapmap[currentfloor][ForwardX][ForwardY]==1){
    IsForwardAvailable=false;
  }
  if((USLeftA<30&&USLeftB<30) || trapmap[currentfloor][LeftX][LeftY]==1){
    IsLeftAvailable=false;
  }
  if((USRightA<30&&USRightB<30) || trapmap[currentfloor][RightX][RightY]==1){
    IsRightAvailable=false;
  }
  if(USBackA<30 || USBackB<30 || trapmap[currentfloor][BackwardsX][BackwardsY]==1){
    IsBackwardsAvailable=false;
  }
  //EXIT
  if(PositionX==15 && PositionY==15 && currentfloor==1 && (floodfill[currentfloor][ForwardX][ForwardY]>0||IsForwardAvailable==false) && (floodfill[currentfloor][RightX][RightY]>0||IsRightAvailable==false) && (floodfill[currentfloor][LeftX][LeftY]>0||IsLeftAvailable==false) && (floodfill[currentfloor][BackwardsX][BackwardsY]>0||IsBackwardsAvailable==false)){
    Display("EXIT...", "");
    MotorsStop();
    Blink_for_five();
    Blink_for_five();
  }
  //DECISION
  if(IsRightAvailable==true && (IsForwardAvailable==false||(floodfill[currentfloor][RightX][RightY]<=floodfill[currentfloor][ForwardX][ForwardY])) && (IsBackwardsAvailable==false||(floodfill[currentfloor][RightX][RightY]<=floodfill[currentfloor][BackwardsX][BackwardsY])) && (IsLeftAvailable==false||(floodfill[currentfloor][RightX][RightY]<=floodfill[currentfloor][LeftX][LeftY]))){
    TurnRight();
  } else if(IsForwardAvailable==true && (IsRightAvailable==false||(floodfill[currentfloor][ForwardX][ForwardY]<=floodfill[currentfloor][RightX][RightY])) && (IsBackwardsAvailable==false||(floodfill[currentfloor][ForwardX][ForwardY]<=floodfill[currentfloor][BackwardsX][BackwardsY])) && (IsLeftAvailable==false||(floodfill[currentfloor][ForwardX][ForwardY]<=floodfill[currentfloor][LeftX][LeftY]))){
    Wobble();
  } else if(IsBackwardsAvailable==true && ((IsRightAvailable==false&&IsLeftAvailable==false&&IsForwardAvailable==false)||(floodfill[currentfloor][BackwardsX][BackwardsY]==0))){
    TurnBackwards();
  } else {
    TurnLeft();
  }
}
