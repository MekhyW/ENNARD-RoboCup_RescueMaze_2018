#include <Encoder.h>
#define TileDist 2900
#define TurnDist 2450
Encoder EA(43, 45);
Encoder EB(37, 39);
Encoder DA(47, 49);
Encoder DB(41, 51);
//E=left , D=right
//A=front , B=back
int EncPulseEA=0;
int EncPulseEB=0;
int EncPulseDA=0;
int EncPulseDB=0;
float EncPulseAvg=0;
bool Locked=false;
int EncPulseEAbackup=0;
int EncPulseEBbackup=0;
int EncPulseDAbackup=0;
int EncPulseDBbackup=0;


void UpdateEncoders(){
  if(Locked==false){
    EncPulseEA=abs(EA.read());
    EncPulseEB=abs(EB.read());
    EncPulseDA=abs(DA.read());
    EncPulseDB=abs(DB.read());
    EncPulseAvg=(EncPulseEA+EncPulseEB+EncPulseDA+EncPulseDB)/4;
  }
}


void LockEncoders(){
  Locked=true;
  EncPulseEAbackup = EncPulseEA;
  EncPulseEBbackup = EncPulseEB;
  EncPulseDAbackup = EncPulseDA;
  EncPulseDBbackup = EncPulseDB;
}

void UnlockEncoders(){
  Locked=false;
  EA.write(EncPulseEAbackup);
  EB.write(EncPulseEBbackup);
  DA.write(EncPulseDAbackup);
  DB.write(EncPulseDBbackup);
}

void ResetEncoders(){
  EA.write(0);
  EB.write(0);
  DA.write(0);
  DB.write(0);
  EncPulseEA=0;
  EncPulseEB=0;
  EncPulseDA=0;
  EncPulseDB=0;
  EncPulseAvg=0;
}


void setup() {
  Serial.begin(9600);
  EB.write(0);
  UpdateEncoders();
  LockEncoders();
  UnlockEncoders();
}

void loop() {
  Serial.println(EncPulseEB);
  UpdateEncoders();
}
