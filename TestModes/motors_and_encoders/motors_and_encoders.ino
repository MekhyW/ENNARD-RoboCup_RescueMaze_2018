#include <Encoder.h>
#define TileDist 2800
#define TurnDist 1800
Encoder EA(45, 43);
Encoder EB(39, 37);
Encoder DA(49, 47);
Encoder DB(51, 41);
//E=left , D=right
//A=front , B=back
int EncPulseEA=0;
int EncPulseEB=0;
int EncPulseDA=0;
int EncPulseDB=0;
int EncPulseAvg=0;
bool Locked=false;
int EncPulseEAbackup=0;
int EncPulseEBbackup=0;
int EncPulseDAbackup=0;
int EncPulseDBbackup=0;
#define motorUL 5
#define motorULdirA 2
#define motorULdirB 4
#define motorLL 8
#define motorLLdirA 10
#define motorLLdirB 9
#define motorUR 7
#define motorURdirA 6
#define motorURdirB 3
#define motorLR 11
#define motorLRdirA 40
#define motorLRdirB 12

void UpdateEncoders(){
  EncPulseEA=abs(EA.read());
  EncPulseEB=abs(EB.read());
  EncPulseDA=abs(DA.read());
  EncPulseDB=abs(DB.read());
  EncPulseAvg=(EncPulseEA+EncPulseEB+EncPulseDA+EncPulseDB)/4;
}

void Retreat(){
  EA.write(EncPulseEA*1.3);
  EB.write(EncPulseEB*1.3);
  DA.write(EncPulseDA*1.3);
  DB.write(EncPulseDB*1.3);
  while(EncPulseAvg>0){
    MoveBackwards(200);
    EncPulseEA=EA.read();
    EncPulseEB=EB.read();
    EncPulseDA=DA.read();
    EncPulseDB=DB.read();
    EncPulseAvg=(EncPulseEA+EncPulseEB+EncPulseDA+EncPulseDB)/4;
    Serial.println(EncPulseAvg);
    delay(5);
  }
  MotorsStop();
}

void LockEncoders(){
  Locked=true;
  EncPulseEAbackup = EncPulseEA;
  EncPulseEBbackup = EncPulseEB;
  EncPulseDAbackup = EncPulseDA;
  EncPulseDBbackup = EncPulseDB;
}

void UnlockEncoders(){
  Locked=false;
  EA.write(EncPulseEAbackup);
  EB.write(EncPulseEBbackup);
  DA.write(EncPulseDAbackup);
  DB.write(EncPulseDBbackup);
}

void ResetEncoders(){
  EA.write(0);
  EB.write(0);
  DA.write(0);
  DB.write(0);
  EncPulseEA=0;
  EncPulseEB=0;
  EncPulseDA=0;
  EncPulseDB=0;
  EncPulseAvg=0;
}

void MotorsStop(){
  digitalWrite(40, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  delay(100);
}

void MotorsInitialize(){
  pinMode(40, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  MotorsStop();
}

void URForward(){
  digitalWrite(motorURdirA, HIGH);
  digitalWrite(motorURdirB, LOW);
}

void URBackwards(){
  digitalWrite(motorURdirA, LOW);
  digitalWrite(motorURdirB, HIGH);
}

void ULForward(){
  digitalWrite(motorULdirA, HIGH);
  digitalWrite(motorULdirB, LOW);
}

void ULBackwards(){
  digitalWrite(motorULdirA, LOW);
  digitalWrite(motorULdirB, HIGH);
}

void LRForward(){
  digitalWrite(motorLRdirA, HIGH);
  digitalWrite(motorLRdirB, LOW);
}

void LRBackwards(){
  digitalWrite(motorLRdirA, LOW);
  digitalWrite(motorLRdirB, HIGH);
}

void LLForward(){
  digitalWrite(motorLLdirA, HIGH);
  digitalWrite(motorLLdirB, LOW);
}

void LLBackwards(){
  digitalWrite(motorLLdirA, LOW);
  digitalWrite(motorLLdirB, HIGH);
}


void MoveForward(int speed){
  ULForward();
  LLForward();
  URForward();
  LRForward();
  analogWrite(motorUL, speed);
  analogWrite(motorLL, speed);
  analogWrite(motorUR, speed);
  analogWrite(motorLR, speed);
}


void MoveBackwards(int speed){
  ULBackwards();
  LLBackwards();
  URBackwards();
  LRBackwards();
  analogWrite(motorUL, speed);
  analogWrite(motorLL, speed);
  analogWrite(motorUR, speed);
  analogWrite(motorLR, speed);
}


void RotateLeft(int speed){
  ULBackwards();
  LLBackwards();
  URForward();
  LRForward();
  analogWrite(motorUL, speed);
  analogWrite(motorLL, speed);
  analogWrite(motorUR, speed);
  analogWrite(motorLR, speed);
}


void RotateRight(int speed){
  ULForward();
  LLForward();
  URBackwards();
  LRBackwards();
  analogWrite(motorUL, speed);
  analogWrite(motorLL, speed);
  analogWrite(motorUR, speed);
  analogWrite(motorLR, speed);
}

void AvoidLeft(){
  LockEncoders();
  RotateLeft(200);
  delay(200);
  MoveBackwards(150);
  delay(200);
  RotateRight(200);
  delay(300);
  MoveForward(150);
  delay(200);
  RotateLeft(200);
  delay(150);
  UnlockEncoders();
}


void setup() {
  Serial.begin(9600);
  delay(1000);
  MotorsInitialize();
  while(EncPulseEA<1900 || EncPulseEB<1900 || EncPulseDA<1900 || EncPulseDB<1900){
    UpdateEncoders();
    Serial.println(EncPulseAvg);
    RotateLeft(200);
    delay(0);
  }
  MotorsStop();
  //Retreat();
}

void loop() {

}
