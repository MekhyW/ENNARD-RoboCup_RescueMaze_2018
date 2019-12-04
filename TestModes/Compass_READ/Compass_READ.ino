#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
#include <Wire.h>
#include <HMC5883L.h>

HMC5883L compass;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  
  // Initialize Initialize HMC5883L
  Serial.println("Initialize HMC5883L");
  while (!compass.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
  }

  // Set measurement range
  compass.setRange(HMC5883L_RANGE_1_3GA);

  // Set measurement mode
  compass.setMeasurementMode(HMC5883L_CONTINOUS);

  // Set data rate
  compass.setDataRate(HMC5883L_DATARATE_30HZ);

  // Set number of samples averaged
  compass.setSamples(HMC5883L_SAMPLES_8);

  // Set calibration offset. See HMC5883L_calibration.ino
  compass.setOffset(-34, -124);
  
  TestCompass();
  Serial.println(millis());
}

void Display(String strU, String strL){
  lcd.clear();
  lcd.setCursor(floor((16-strU.length())/2), 0);
  lcd.print(strU);
  lcd.setCursor(floor((16-strL.length())/2), 1);
  lcd.print(strL);
}

void loop()
{
  TestCompass();
}

void TestCompass(){
  Vector norm = compass.readNormalize();
  float heading = atan2(norm.YAxis, norm.XAxis);
  if (heading < 0)
  {
    heading += 2 * PI;
  }
  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }
  float headingDegrees = heading * 180/M_PI; 

  Display(String(headingDegrees), "");
  delay(2000);
}

