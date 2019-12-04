#include <Servo.h>
#define DeployerPin 46
Servo Deployer;
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
int KitCounter=0;

void MotorsStop(){
  digitalWrite(motorULdirA, HIGH);
  digitalWrite(motorULdirB, HIGH);
  digitalWrite(motorURdirA, HIGH);
  digitalWrite(motorURdirB, HIGH);
  digitalWrite(motorLLdirA, HIGH);
  digitalWrite(motorLLdirB, HIGH);
  digitalWrite(motorLRdirA, HIGH);
  digitalWrite(motorLRdirB, HIGH);
  delay(200);
}

void MotorsInitialize(){
  Deployer.attach(DeployerPin);
  Deployer.write(90);
  pinMode(motorUL, OUTPUT);
  pinMode(motorULdirA, OUTPUT);
  pinMode(motorULdirB, OUTPUT);
  pinMode(motorLL, OUTPUT);
  pinMode(motorLLdirA, OUTPUT);
  pinMode(motorLLdirB, OUTPUT);
  pinMode(motorUR, OUTPUT);
  pinMode(motorURdirA, OUTPUT);
  pinMode(motorURdirB, OUTPUT);
  pinMode(motorLR, OUTPUT);
  pinMode(motorLRdirA, OUTPUT);
  pinMode(motorLRdirB, OUTPUT);
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

void IntroduceRight(int speed){
  ULForward();
  LLForward();
  analogWrite(motorUL, speed);
  analogWrite(motorLL, speed);
  analogWrite(motorUR, 0);
  analogWrite(motorLR, 0);
}

void IntroduceLeft(int speed){
  URForward();
  LRForward();
  analogWrite(motorUL, 0);
  analogWrite(motorLL, 0);
  analogWrite(motorUR, speed);
  analogWrite(motorLR, speed);
}


void StrafeLeft(int speed){
  ULBackwards();
  LLForward();
  URForward();
  LRBackwards();
  analogWrite(motorUL, speed);
  analogWrite(motorLL, speed);
  analogWrite(motorUR, speed);
  analogWrite(motorLR, speed);
}


void StrafeRight(int speed){
  ULForward();
  LLBackwards();
  URBackwards();
  LRForward();
  analogWrite(motorUL, speed);
  analogWrite(motorLL, speed);
  analogWrite(motorUR, speed);
  analogWrite(motorLR, speed);
}


void DeployKitLeft(){
	Deployer.write(150);
  delay(500);
  Deployer.write(65);
  delay(500);
  Deployer.write(90);
  delay(500);
  KitCounter++;
}

void DeployKitRight(){
  Deployer.write(30);
  delay(500);
  Deployer.write(110);
  delay(500);
  Deployer.write(90);
  delay(500);
  KitCounter++;
}
