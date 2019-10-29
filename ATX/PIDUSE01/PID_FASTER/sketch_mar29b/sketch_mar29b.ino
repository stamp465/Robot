#include<popx2.h>                         //7.9 V
#include <QTRSensors.h>

#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             2  // emitter is controlled by digital pin 2
QTRSensorsAnalog qtra((unsigned char[]) {
  24, 25, 26, 27, 30, 18
},
NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
int power_motor, error, last_error, leftMotorSpeed, rightMotorSpeed, position;
int senL = (180 + 750) / 2;
int senR = (140 + 690) / 2;
int c = 0;
void setup() {
  OK();
  //glcd(1, 1, "start");
  //for (int i=0; i<200;i++){
  qtra.calibrate();
  //}
  qtra.calibratedMinimumOn[0] = 960;
  qtra.calibratedMinimumOn[1] = 963;
  qtra.calibratedMinimumOn[2] = 944;
  qtra.calibratedMinimumOn[3] = 949;
  qtra.calibratedMinimumOn[4] = 959;
  qtra.calibratedMinimumOn[5] = 961;
  qtra.calibratedMaximumOn[0] = 1003;
  qtra.calibratedMaximumOn[1] = 1004;
  qtra.calibratedMaximumOn[2] = 1000;
  qtra.calibratedMaximumOn[3] = 1002;
  qtra.calibratedMaximumOn[4] = 1003;
  qtra.calibratedMaximumOn[5] = 1007;
  while(1){
    if(sw_ok()) break;
    if(sw1()) c++;
    glcd(1,1,"  %d  ",c%7);
    delay(100);
  }
  glcd(1,7,"  %d  ",c%7);
  int checkgo = c&7;
  if(checkgo==0){
    startt();
  }
  else if(checkgo==1){
    r1check1();
  }
  else if(checkgo==2){
    r1check2();
  }
  else if(checkgo==3){
    r1check3();
  }
  else if(checkgo==4){
    r2check1();
  }
  else if(checkgo==5){
    r2check2();
  }
  else if(checkgo==6){
    r2check3();
  }
  //
}

void loop() {
                     //glcd(1,1,"***%d***",analog(4));
                     //glcd(3,1,"***%d***",analog(5));
  while (1) {
    ao();
  }
}
