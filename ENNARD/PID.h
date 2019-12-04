#define Kp 100
#define Ki 0
#define Kd 0
float previous_error=0;
float P=0;
float I=0;
float previous_I=0;
float D=0;
float PID_value=0;
float error=0;

void CalculatePID(){
  if(USLeftA<30 && USRightA<30){
  	error=USRightA-USLeftA;
  } else if(USBackA<99 && USBackB<99){
    error = USBackB-USBackA;
  } else if(USFrontA<99 && USFrontB<99 && USFrontCT<99){
    error = USFrontA-USFrontB;
  } else if(USLeftA<99 && USLeftB<99){
    error = USLeftB-USLeftA+(15-USLeftA);
  } else if(USRightA<30 && USRightB<30){
    error = USRightA-USRightB+(USRightA-15);
  } else {
    error = 0;
  }
  if(abs(error)<=0.6){
    error=0;
  }
  P = error;
  I = I + error;
  D = error - previous_error;
  PID_value = round((Kp*P)+(Ki*I)+(Kd*D));
  previous_error=error;
}
