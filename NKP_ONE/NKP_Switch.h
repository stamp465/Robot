#define _sw 15
int sw1(){
  pinMode(_sw,INPUT);
  return digitalRead(_sw);
}
