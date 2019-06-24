#include <QTRSensors.h>
#include<popx2.h>
#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             2  // emitter is controlled by digital pin 2
int power_motor, error, last_error, leftMotorSpeed, rightMotorSpeed, position;
QTRSensorsAnalog qtra((unsigned char[]) {24, 25, 26, 27, 28, 29}, NUM_SENSORS,NUM_SAMPLES_PER_SENSOR,EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
void setup()
{
  OK(); 
  sound(1000, 1000);
  glcd(1, 1, "start1");
  for (int i = 0; i < 200;i++)
  {
    qtra.calibrate();
  }
  glcd(1, 1, "finish1");
  sound(500, 250);
  glcdClear();
  
}
void loop()
{
  
}
void pid(float kp, float kd, int bs ) {
    position = qtra.readLine(sensorValues);
    error = map(position, 0, 5000, -100, 100);
  power_motor = (error * kp) + ((error - last_error) * kd);
  last_error = error;
  leftMotorSpeed = bs + power_motor;
  rightMotorSpeed = bs - power_motor;
  if (leftMotorSpeed <= -90) {
    leftMotorSpeed = -90;
  }
  if (leftMotorSpeed >= 90) {
    leftMotorSpeed = 90;
  }
  if (rightMotorSpeed <= -90) {
    rightMotorSpeed = -90;
  }
  if (rightMotorSpeed >= 90) {
    rightMotorSpeed = 90;
  }
  motor(1, leftMotorSpeed);
  motor(2, rightMotorSpeed);
}
void pid_T(float kp, float kd, int bs, int times) {
  long A = millis();
  while ((millis() - A) < times) {
    pid(kp, kd, bs);
  }
  ao();
}
void pid_2(float kp, float kd, int bs ) {
    position = qtra.readLine(sensorValues);
    error = map(position, 0, 5000, -100, 100);
  power_motor = (error * kp) + ((error - last_error) * kd);
  last_error = error;
  leftMotorSpeed = bs + power_motor;
  rightMotorSpeed = bs - power_motor;
  if (leftMotorSpeed <= -70) {
    leftMotorSpeed = -70;
  }
  if (leftMotorSpeed >= 70) {
    leftMotorSpeed = 70;
  }
  if (rightMotorSpeed <= -70) {
    rightMotorSpeed = -700;
  }
  if (rightMotorSpeed >= 70) {
    rightMotorSpeed = 70;
  }
  motor(1, leftMotorSpeed);
  motor(2, rightMotorSpeed);
}
void pid_2T(float kp, float kd, int bs, int times) {
  long A = millis();
  while ((millis() - A) < times) {
    pid_2(kp, kd, bs);
  }
}
void pid_S(float kp, float kd, int bs) {
  position = qtra.readLine(sensorValues);
  error = map(position, 0, 5000, 100, -100);
  power_motor = (error * kp) + ((error - last_error) * kd);
  last_error = error;
  leftMotorSpeed = bs + power_motor;
  rightMotorSpeed = bs - power_motor;
  if (leftMotorSpeed <= -70) {
    leftMotorSpeed = -70;
  }
  if (leftMotorSpeed >= 70) {
    leftMotorSpeed = 70;
  }
  if (rightMotorSpeed <= -70) {
    rightMotorSpeed = -70;
  }
  if (rightMotorSpeed >= 70) {
    rightMotorSpeed = 70;
  }
  if (position < 10) {
    //sr(sp);
    motor(1, 40); motor(2, -40);
    while (position < 1000) {
      position = qtra.readLine(sensorValues);
    }
  }

  if (position > 6990 ) {
    // sl(sp);
    motor(1, -40); motor(2, 40);
    while (position > 6000) {
      position = qtra.readLine(sensorValues);
    }
  }
  motor(1, leftMotorSpeed);
  motor(2, rightMotorSpeed);
}
void pid_ST(float kp, float kd, int bs, int times) {
  long A = millis();
  while ((millis() - A) < times) {
    pid_S(kp, kd, bs);
  }
}
