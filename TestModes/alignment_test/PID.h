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
  if(USBackA<99 && USBackB<99){
    error = USBackB-USBackA;
  } else if(USRightA<99 && USRightB<99){
    error = USRightA-USRightB;
  } else if(USLeftA<99 && USLeftB<99){
    error = USLeftB-USLeftA;
  } else if(USFrontA<99 && USFrontB<99 && USFrontCT<99){
    error = USFrontA-USFrontB;
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
