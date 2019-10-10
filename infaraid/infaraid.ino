#include <popx2.h>   //Battery 8.3-8.25 V
#include <gp2d120.h>

void setup(){
  OK();
}
void loop(){
  glcd(1,1,"***%d***",getdist(0));
}
    
  
