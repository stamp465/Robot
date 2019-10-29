#include <ATX2.h>	
int L,R,Ref=500;
int power = 100;
void LL(){
  while(1){
   L = analog(1);
   R = analog(2);
   if(L<Ref && R<Ref) {
      FD(power); delay(80);
      while(analog(1)>Ref) SL(55);
      while(analog(1)<Ref) SL(55);
      break;
   }
   else if(L<Ref && R>Ref) SL(50);
   else if(L>Ref && R<Ref) SR(50);
   else if(L>Ref && R>Ref) FD(power);
  }
  AO();
}

void RR(){
  while(1){
   L = analog(1);
   R = analog(2);
   if(L<Ref && R<Ref) {
      FD(power); delay(80);
      while(analog(2)>Ref) SR(55);
      while(analog(2)>Ref) SR(55);
      break;
   }
   else if(L<Ref && R>Ref) SL(50);
   else if(L>Ref && R<Ref) SR(50);
   else if(L>Ref && R>Ref) FD(power);
  }
  AO();
}

void FF(){
  while(1){
   L = analog(1);
   R = analog(2);
   if(L<Ref && R<Ref) {
      FD(power); delay(80);
     AO();
     break;
   }
   else if(L<Ref && R>Ref) SL(50);
   else if(L>Ref && R<Ref) SR(50);
   else if(L>Ref && R>Ref) FD(power);
  }
  
}
void STOP(){
  while(1){
   L = analog(1);
   R = analog(2);
   if(L<Ref && R<Ref) {
     AO();
     break;
   }
   else if(L<Ref && R>Ref) SL(50);
   else if(L>Ref && R<Ref) SR(50);
   else if(L>Ref && R>Ref) FD(power);
  }
  
}
void setup() {
  OK();	
  FF();
  power = 50;
  LL();
  RR();
  power = 40;
  RR();
  LL();
  power = 100;
  FF();
  power = 50;
  LL();
  RR();
  power = 100;
  STOP();
  

}

void loop() {
  
}
