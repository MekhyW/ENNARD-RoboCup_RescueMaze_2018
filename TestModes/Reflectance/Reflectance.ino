#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
#define ReflectionAPin A7
#define ReflectionBPin A6
#define TrapLimit 1000
#define CheckpointLimit 100
int ReflectLeft=500;
int ReflectRight=500;

void ReflectionInitialize(){
  pinMode(ReflectionAPin, INPUT);
  pinMode(ReflectionBPin, INPUT);
}

void ReadReflection(){
  ReflectLeft = (ReflectLeft*0.4)+(analogRead(ReflectionAPin)*0.6);
  ReflectRight = (ReflectRight*0.4)+(analogRead(ReflectionBPin)*0.6);
}

void setup() {
  Serial.begin(9600);
  ReflectionInitialize();
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
}

void loop() {
  ReadReflection();
  Display(String(ReflectLeft), String(ReflectRight));
  delay(100);
}


void Display(String strU, String strL){
  lcd.clear();
  lcd.setCursor(floor((16-strU.length())/2), 0);
  lcd.print(strU);
  lcd.setCursor(floor((16-strL.length())/2), 1);
  lcd.print(strL);
}
