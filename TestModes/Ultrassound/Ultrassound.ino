#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
#include "Motors.h"
#include <NewPing.h>
float USFrontCT=99;
float USFrontA=99;
float USFrontB=99;
float USLeftA=99;
float USLeftB=99;
float USRightA=99;
float USRightB=99;
float USBackA=99;
float USBackB=99;
NewPing FrontCT(31, 33, 21);
NewPing FrontA(27, 29, 21);
NewPing FrontB(35, 48, 21);
NewPing BackA(24, 22, 21);
NewPing BackB(32, 34, 21);
NewPing LeftA(23, 25, 20);
NewPing LeftB(26, 28, 20);
NewPing RightA(44, 50, 20);
NewPing RightB(38, 36, 20);


void PingFCT(){
  USFrontCT = ((float)FrontCT.ping_median(1)/57)+9.5;
  if(USFrontCT==9.5){
    USFrontCT=99;
  } else {
    USFrontCT-=0;
  }
}

void PingFA(){
  USFrontA = ((float)FrontA.ping_median(1)/57)+9.5;
  if(USFrontA==9.5){
    USFrontA=99;
  } else {
    USFrontA-=0.5;
  }
}

void PingFB(){
  USFrontB = ((float)FrontB.ping_median(1)/57)+9.5;
  if(USFrontB==9.5){
    USFrontB=99;
  } else {
    USFrontB+=0.5;
  }
}

void PingLA(){
  USLeftA = ((float)LeftA.ping_median(1)/57)+10;
  if(USLeftA==10){
    USLeftA=99;
  } else {
    USLeftA-=0;
  }
}

void PingLB(){
  USLeftB = ((float)LeftB.ping_median(1)/57)+10;
  if(USLeftB==10){
    USLeftB=99;
  } else {
    USLeftB-=0.2;
  }
}

void PingRA(){
  USRightA = ((float)RightA.ping_median(1)/57)+10;
  if(USRightA==10){
    USRightA=99;
  } else {
    USRightA+=0.8;
  }
}

void PingRB(){
  USRightB = ((float)RightB.ping_median(1)/57)+10;
  if(USRightB==10){
    USRightB=99;
  } else {
    USRightB-=0;
  }
}

void PingBA(){
  USBackA = ((float)BackA.ping_median(1)/57)+9.5;
  if(USBackA==9.5){
    USBackA=99;
  } else {
    USBackA-=0;
  }
}

void PingBB(){
  USBackB = ((float)BackB.ping_median(1)/57)+9.5;
  if(USBackB==9.5){
    USBackB=99;
  } else {
    USBackB-=0.8;
  }
}


void ReadUltrassound(bool fa, bool fct, bool fb, bool ra, bool rb, bool bb, bool ba, bool lb, bool la){
  if(ba==true){
    PingBA();
  }
  if(fb==true){
    PingFB(); 
  }
  if(bb==true){
    PingBB();  
  }
  if(fa==true){
    PingFA();  
  }
  if(rb==true){
    PingRB();  
  }
  if(la==true){
    PingLA();  
  }
  if(ra==true){
    PingRA(); 
  }
  if(lb==true){
    PingLB(); 
  }
  if(fct==true){
    PingFCT(); 
  }
}

void Display(String strU, String strL){
  lcd.clear();
  lcd.setCursor(floor((16-strU.length())/2), 0);
  lcd.print(strU);
  lcd.setCursor(floor((16-strL.length())/2), 1);
  lcd.print(strL);
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
}

void loop() {
  ReadUltrassound(true, true, true, true, true, true, true, true, true);
  Display(String(USBackA), String(USBackB));
  delay(50);
}
