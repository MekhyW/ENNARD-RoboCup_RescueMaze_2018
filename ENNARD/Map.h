#define ButtonPin 30
byte trapmap[2][30][30] = {0};
byte heatmap[2][30][30] = {0};
byte floodfill[2][30][30] = {0};
byte floodfillbackup[2][30][30] = {0};
int currentfloor=1;
int PositionX = 15;
int PositionY = 15;
int PositionXBackup = 15;
int PositionYBackup = 15;
int ForwardX=15;
int ForwardY=16;
int LeftX=14;
int LeftY=15;
int RightX=16;
int RightY=15;
int BackwardsX=15;
int BackwardsY=14;


void PressToStart(bool First){
  if(First==true){
    pinMode(ButtonPin, INPUT_PULLUP);
    Display("Press to", "begin rescue");
  } else {
    Display("(Paused)", "");
    delay(3000);
  }
	while(digitalRead(ButtonPin) == HIGH){
		delay(1);
	}
  if(First==true){
    Display("STARTING...", "");
  } else {
    ReadCompass();
    Display("RESUMING...", String(Compass));
  }
  delay(1000);
}


void CheckBackup(){
  if(digitalRead(ButtonPin) == LOW){
    memcpy(floodfill, floodfillbackup, sizeof(floodfill));
    PositionX=PositionXBackup;
    PositionY=PositionYBackup;
    MotorsStop();
    ResetEncoders();
    PressToStart(false);
  }
}


void UpdateBackup(){
  memcpy(floodfillbackup, floodfill, sizeof(floodfillbackup));
  if(EncPulseAvg<=TileDist/2){
    PositionXBackup=PositionX;
    PositionYBackup=PositionY;
  } else {
    PositionXBackup=ForwardX;
    PositionYBackup=ForwardY;
  }
  MotorsStop();
  Display("Checkpoint detected", "Backup updated");
  delay(1000);
}


void RelativeXY(){
  if(Quadrant==1){
    LeftX=PositionX;
    LeftY=PositionY-1;
    RightX=PositionX;
    RightY=PositionY+1;
    ForwardX=PositionX-1;
    ForwardY=PositionY;
    BackwardsX=PositionX+1;
    BackwardsY=PositionY;
  } else if(Quadrant==2){
    LeftX=PositionX;
    LeftY=PositionY+1;
    RightX=PositionX;
    RightY=PositionY-1;
    ForwardX=PositionX+1;
    ForwardY=PositionY;
    BackwardsX=PositionX-1;
    BackwardsY=PositionY;
  } else if(Quadrant==3){
    LeftX=PositionX-1;
    LeftY=PositionY;
    RightX=PositionX+1;
    RightY=PositionY;
    ForwardX=PositionX;
    ForwardY=PositionY+1;
    BackwardsX=PositionX;
    BackwardsY=PositionY-1;
  } else if(Quadrant==4){
    LeftX=PositionX+1;
    LeftY=PositionY;
    RightX=PositionX-1;
    RightY=PositionY;
    ForwardX=PositionX;
    ForwardY=PositionY-1;
    BackwardsX=PositionX;
    BackwardsY=PositionY+1;
  }
}

void CalculateDisplacement(){
    if(Quadrant==1){
      PositionX--;
    } else if(Quadrant==2){
      PositionX++;
    } else if(Quadrant==3){
      PositionY++;
    } else if(Quadrant==4){
      PositionY--;
    }
    RelativeXY();
    if(floodfill[currentfloor][PositionX][PositionY]==0){
      floodfill[currentfloor][PositionX][PositionY]=floodfill[currentfloor][BackwardsX][BackwardsY]+1;
    }
}
