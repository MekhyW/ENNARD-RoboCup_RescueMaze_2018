#include <Encoder.h>
#define TileDist 2600
#define TurnDist 1900
Encoder EA(45, 43);
Encoder EB(39, 37);
Encoder DA(49, 47);
Encoder DB(51, 41);
//E=left , D=right
//A=front , B=back
int EncPulseEA=0;
int EncPulseEB=0;
int EncPulseDA=0;
int EncPulseDB=0;
int EncPulseAvg=0;
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
  UpdateEncoders();
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
