int MVRightChar=0;
int MVLeftChar=0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  while(Serial1.available()){
    MVLeftChar = Serial1.read();
  }
  Serial.print(MVLeftChar);
  Serial.print("   ");
  while(Serial2.available()){
    MVRightChar = Serial2.read();
  }
  Serial.println(MVRightChar);
  delay(100);
}
