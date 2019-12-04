#define ButtonPin 30

void setup() {
  Serial.begin(9600);
  pinMode(ButtonPin, INPUT_PULLUP);
}

void loop() {
  Serial.println(digitalRead(ButtonPin));
}
