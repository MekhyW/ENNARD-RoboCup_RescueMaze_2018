#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

void setup() {
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  Display("TESTE OK 123", "Tela funcionando");
  delay(1000);
  Blink_for_five();
}

void loop() {
  Display("...", String(millis()));
  delay(100);
}


void Display(String strU, String strL){
  lcd.clear();
  lcd.setCursor(floor((16-strU.length())/2), 0);
  lcd.print(strU);
  lcd.setCursor(floor((16-strL.length())/2), 1);
  lcd.print(strL);
}

void Blink_for_five(){
  for(int i=0; i<10; i++){
    lcd.setBacklight(LOW);
    delay(250);
    lcd.setBacklight(HIGH);
    delay(250);
  }
}

