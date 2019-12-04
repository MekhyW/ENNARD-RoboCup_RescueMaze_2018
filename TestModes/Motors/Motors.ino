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

void MotorsStop(){
  digitalWrite(motorULdirA, HIGH);
  digitalWrite(motorULdirB, HIGH);
  digitalWrite(motorURdirA, HIGH);
  digitalWrite(motorURdirB, HIGH);
  digitalWrite(motorLLdirA, HIGH);
  digitalWrite(motorLLdirB, HIGH);
  digitalWrite(motorLRdirA, HIGH);
  digitalWrite(motorLRdirB, HIGH);
}

void MotorsInitialize(){
  Deployer.attach(DeployerPin);
  Deployer.write(85);
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


void setup() {
  Serial.begin(9600);
  MotorsInitialize();
  delay(1000);
  //TestMotors();
  //Avoid();
  //Wobble();
  MotorsStop();
}

void loop() {
  MoveForward(150);
  delay(2000);
  MoveForward(0);
  delay(2000);
}

void Avoid(){
  RotateRight(200);
  delay(200);
  MoveBackwards(150);
  delay(200);
  RotateLeft(200);
  delay(300);
  MoveForward(150);
  delay(200);
  RotateRight(200);
  delay(150);
}

void Wobble(){
  RotateRight(200);
  delay(200);
  MoveBackwards(150);
  delay(200);
  RotateLeft(200);
  delay(200);
  MoveForward(150);
  delay(200);
}

void TestMotors(){
  MoveForward(200);
  delay(1000);
  MoveBackwards(200);
  delay(1000);
  RotateRight(150);
  delay(1000);
  RotateLeft(150);
  delay(1000);
  MotorsStop();
}
