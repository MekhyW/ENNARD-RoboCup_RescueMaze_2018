#include <Servo.h>
Servo Deployer;

void setup() {
  Deployer.attach(26);
  Deployer.write(90);
  delay(1000);
}

void DeployKitLeft(){
  Deployer.write(150);
  delay(300);
  Deployer.write(70);
  delay(300);
  Deployer.write(90);
  delay(300);
  //KitCounter--;
}

void DeployKitRight(){
  Deployer.write(30);
  delay(300);
  Deployer.write(110);
  delay(300);
  Deployer.write(90);
  delay(300);
  //KitCounter--;
}


void loop() {
  DeployKitRight();
  delay(1000);
}
