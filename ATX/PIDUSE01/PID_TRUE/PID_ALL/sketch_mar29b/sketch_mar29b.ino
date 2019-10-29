#include<popx2.h>                         //8 V
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
int senL = (270 + 920) / 2;
int senR = (110 + 590) / 2;
void setup() {
  OK();
  glcd(1, 1, "start");
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
  motor(1, 30);
  motor(2, 30);
  delay(350);

  //
}

void loop() {
  //glcd(1,1,"***%d***",analog(4));
  //glcd(3,1,"***%d***",analog(5));
  pidT(0.4, 2, 30, 100);
  pidT(0.4, 2, 40, 400);
  pidST70(0.2, 3.5, 25, 5400);
  //pidST70(0.4, 3.5, 40, 3500);
  square(6, 35, 10);
  pid_BB(0.4, 4, 25);
  fd(30); delay(250);
  while (true) {
    if (analog(4) < 250 || analog(5) < 250) {
      fd(30);
    }
    else {
      ao();
      break;
    }
  }
  square(2, 35, 10);
  pidST90(0.4, 4, 30, 1500);
  pidST90(0.4, 4, 40, 1000);

  pidT(0.4, 2, 50, 50);
  pidT(0.4, 2, 38, 1100);
  pidT(0.4, 3, 47, 3000);
  pid_BB(0.7, 4, 55);

  pidT(0.4, 2, 35, 2500);
  pidT(0.4, 3, 40, 6500);
  pidST70(0.4, 4, 35, 7000);



  square(1, 30, 30);
  square(1, 30, 30);
  exit_white(250);
  pidST70(0.2, 3.5, 25, 5000);
  pid_BB(0.4, 4, 30);

  fd(30); delay(50);
  ao(); delay(50); sr(50); delay(50);
  sr(30);
  while (true) {
    position = qtra.readLine(sensorValues);
    if (sensorValues[0] > 500) {
      sl(80); delay(15); ao(); delay(50);
      pidT(0.4, 2, 20, 200);
      break;
    }
  }
  ////////////////////////////////////////////////////////////////////////
  pidT(0.4, 2, 30, 100);
  pidT(0.4, 2, 40, 400);
  pidST70(0.2, 3.5, 25, 5400);
  //pidST70(0.4, 3.5, 40, 3500);
  square(6, 35, 10);
  pid_BB(0.4, 4, 25);
  fd(30); delay(250);
  while (true) {
    if (analog(4) < 250 || analog(5) < 250) {
      fd(30);
    }
    else {
      ao();
      break;
    }
  }
  square(2, 35, 10);
  pidST90(0.4, 4, 30, 1500);
  pidST90(0.4, 4, 40, 1000);

  pidT(0.4, 2, 50, 50);
  pidT(0.4, 2, 38, 1100);
  pidT(0.4, 3, 47, 3000);
  pid_BB(0.7, 4, 55);

  pidT(0.4, 2, 35, 2500);
  pidT(0.4, 3, 40, 6500);
  pidST70(0.4, 4, 35, 7000);



  square(1, 30, 30);
  square(1, 30, 30);
  exit_white(250);
  pidST70(0.2, 3.5, 25, 5000);
  pid_BB(0.4, 4, 30);

  fd(30); delay(50);
  ao(); delay(50); sl(50); delay(50);
  sl(30);
  while (true) {
    position = qtra.readLine(sensorValues);
    if (sensorValues[5] > 300) {
      sr(80); delay(15); ao(); delay(50);
      break;
    }
  }

  fd(50); delay(200);


  while (1) {
    ao();
  }
}
