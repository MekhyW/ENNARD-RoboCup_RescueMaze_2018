#define ReflectionAPin A7
#define ReflectionBPin A6
#define TrapLimit 1000
#define CheckpointLimit 110
int ReflectLeft=500;
int ReflectRight=500;

void ReflectionInitialize(){
	pinMode(ReflectionAPin, INPUT);
	pinMode(ReflectionBPin, INPUT);
}

void ReadReflection(){
  ReflectLeft = (analogRead(ReflectionAPin)*0.6)+(ReflectLeft*0.4);
  ReflectRight = (analogRead(ReflectionBPin)*0.6)+(ReflectRight*0.4);
}

void ReadReflectionPure(){
  ReflectLeft = analogRead(ReflectionAPin)+20;
  ReflectRight = analogRead(ReflectionBPin);
}

