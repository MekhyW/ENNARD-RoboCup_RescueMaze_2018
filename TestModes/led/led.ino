void TurnLED_ON(){
  digitalWrite(LED_BUILTIN, HIGH);
}

void TurnLED_OFF(){
  digitalWrite(LED_BUILTIN, LOW);
}

void PingLED(){
  TurnLED_ON();
  delay(100);
  TurnLED_OFF();
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(1);
  delay(2000);
}
