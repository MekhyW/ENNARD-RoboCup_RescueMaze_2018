#include <MPU6050.h>
#include <HMC5883L.h>
MPU6050 accelgyro;
HMC5883L compass;
int16_t GyroscopeX=0;
int16_t GyroscopeY=0;
int16_t GyroscopeZ=0;
int16_t AccelerationX=0;
int16_t AccelerationY=0;
int16_t AccelerationZ=0;
float Inclination=90;
float Compass=0;
float CompassError=0;
int Quadrant=3; //1=left 2=right 3=up 4=down


void ReadCompass(){
  Vector norm = compass.readNormalize();
  float heading = atan2(norm.YAxis, norm.XAxis);
  if (heading < 0){
    heading += 2 * PI;
  }
  if(heading > 2 * PI){
    heading -= 2 * PI;
  }
  heading *= 180/M_PI;
  Compass = heading;
  Compass -= CompassError;
  if(Compass>=315 || Compass<=45){
    Quadrant=3;
  } else if(Compass>=45 && Compass<=135){
    Quadrant=2;
  } else if(Compass>=135 && Compass<=225){
    Quadrant=4;
  } else {
    Quadrant=1;
  }
}

void ReadAccel(){
  accelgyro.getMotion6(&AccelerationX, &AccelerationY, &AccelerationZ, &GyroscopeX, &GyroscopeY, &GyroscopeZ);
  Inclination = map(AccelerationY, -16600, 17000, 0, 180);
}


void IMUInitialize(){
	Wire.begin();
	accelgyro.initialize();
	accelgyro.setSleepEnabled(false);
	compass.begin();
  	compass.setRange(HMC5883L_RANGE_1_3GA);
  	compass.setMeasurementMode(HMC5883L_CONTINOUS);
  	compass.setDataRate(HMC5883L_DATARATE_30HZ);
  	compass.setSamples(HMC5883L_SAMPLES_8);
  	compass.setOffset(-34, -124);
  	for(int cont=0;cont<100;cont++){
      ReadCompass();
    }
    Quadrant=1;
    CompassError=Compass;
}
