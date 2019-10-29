#include <ATX2.h>	// ATX2 Board
void setup() { 
  OK();
  L90();
  R90();
  R90();
  L90();
  FD(50); delay(1000); AO();
}

void loop() {
  
}
void L90(){
while(1){
  if(in(24)==0||in(25)==0)
    {
    FD(0);delay(200);
    BK(30);delay(100);
    SL(60);delay(450);
    BK(30);delay(700);
    break;
    }
    else FD(60);
}
}

void R90(){
while(1){
  if(in(24)==0||in(25)==0)
    {
    FD(0);delay(200);
    BK(30);delay(100);
    SR(70);delay(550);
    BK(30);delay(700);
    break;
    }
    else FD(60);
}
}
