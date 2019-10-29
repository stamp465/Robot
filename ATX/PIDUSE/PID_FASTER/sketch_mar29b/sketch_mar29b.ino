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
  motor(1, 40);
  motor(2, 40);
  delay(250);
  //
}

void loop() {
                     //glcd(1,1,"***%d***",analog(4));
                     //glcd(3,1,"***%d***",analog(5));
  pid_BB(0.4, 2, 20);
  go();

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
  go();

  fd(30); delay(50);
  ao(); delay(50); sl(50); delay(50);
  sl(30);
  while (analog(4)>300) {
    sl(50);
  }
  while (analog(4)<300) {
    sl(50);
  }
  fd(50); delay(200);

  
  while (1) {
    ao();
  }
}
