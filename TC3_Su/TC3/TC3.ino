#include<popx2.h>
#define Ki 0
#include "NKP_TCSensor.h"
#include <gp2d120.h>
//infaraid
//glcd(1,1,"***%d***",getdist(0));
//Set sensor analog 1 2 3 4
uint8_t numSensor = 4;
uint16_t setpoint;
float present_position;
float errors = 0;
float output = 0;
float integral ;
float derivative ;
float previous_error ;
int ref[10];

void setup(){
  OK();
  Serial.begin(115200);
  setSensorPins((const int[]) {
    25, 26, 27 , 28
  }, 4);
  /*setSensorMax((const int[]) {1, 2, 3, 4});
  setSensorMin((const int[]) {5, 6, 7, 8});*/
  for (int i = 0; i < 5000; i++) {
    setCalibrate();
  }
  for (uint8_t i = 0; i < 4; i++)
    {
    Serial.print(ReadSensorMinValue(i));
    Serial.print(' ');
    }
    Serial.println();
  for (uint8_t i = 0; i < 4; i++)
    {
    Serial.print(ReadSensorMaxValue(i));
    Serial.print(' ');
    }
    Serial.println();
    delay(1000);

  for (int i = 0; i < 4; i++)
  {
    glcd(i, 0, "%d    ", ReadSensorMaxValue(i));
    glcd(i, 5, "%d    ", ReadSensorMinValue(i));
    ref[i+1] = (ReadSensorMinValue(i)+ReadSensorMaxValue(i))/2;
  }
  
  beep();
  
  sw_ok_press();
  
}

void loop() {
  /*Serial.print("  readline");
    Serial.println(readline());
    delay(1);*/
  /*
    glcd(0, 0, "%d   ", analog(0));
    glcd(1, 0, "%d   ", analog(1));
    glcd(2, 0, "%d   ", analog(2));
    glcd(3, 0, "%d   ", analog(3));
    glcd(4, 0, "%d   ", analog(4));
    glcd(5, 0, "%d   ", analog(5));
  */
  ao();
}

void Left(){
  fd(30); delay(60);  ao(); sl(50); delay(50);  ao();
  while (analog(3) > ref[3]);
}

void Right(){
  fd(30); delay(60);  ao(); sr(50); delay(50);  ao();
  while (analog(2) > ref[2]);
}

void Return(){
  //หมุนเส้นตรงยาวไม่เจอเส้นตัดระหว่างหมุน
  fd(30); delay(60);  ao(); sl(50); delay(50);  ao();
  while (analog(3) > ref[3]);
  pid_T(1 , 1 , 30, 100);   //เอาตัวที่เสถียรสุด  
}

void pid(float Kp , float Kd , int speed_max){
  present_position = readline() / ((numSensor - 1) * 10) ;
  setpoint = 50.0;
  errors = setpoint - present_position;
  integral = integral + errors ;
  derivative = (errors - previous_error) ;
  output = Kp * errors + Ki * integral + Kd * derivative;
  previous_error = errors;
  if (output > 100 )output = 100;
  else if (output < -100)output = -100;
  motor(1, speed_max - output);
  motor(2, speed_max + output);
  delay(1);
}

void pid_T(float Kp , float Kd , int speed_max, long mil){
  long a = millis();
  while (a + mil > millis())pid(Kp , Kd , speed_max);
}

void pid_B(float Kp , float Kd , int speed_max){
  while (1)
  {
    pid(Kp, Kd, speed_max);
    if ((analog(4) < ref[4] && analog(3) < ref[3]) || (analog(1) < ref[1] && analog(2) < ref[2]))
    {
      break;
    }
  }
}

void squarest(int num) {
  int x = 0;
  while (1) {
    if (num == 0)  break;
    else {
      if ( analog(0) < 500 ) {   //ซ้าย
        fd(30); delay(100);
        ao(); num -= 1; x = 0;
        sl(50); delay(50);  ao();
        while (analog(3) > ref[3])  sl(30);
        ao();
      }
      else if ( analog(5) < 500 ) {  //ขวา
        fd(30); delay(100);
        ao(); num -= 1; x = 0;
        sr(50); delay(50);  ao();
        while (analog(2) > ref[2])  sr(30);
        ao();

      }
      else if (analog(1) > ref[1] && analog(4) < ref[4]) {
        motor(1, 40);
        motor(2, 10);
      }
      else if (analog(1) < ref[1] && analog(4) > ref[4]) {
        motor(1, 10);
        motor(2, 40);
      }
      else {
        motor(1, 20 + x);
        motor(2, 20 + x);
      }
      x += 3;
      if (x > 20) x = 20;
    }
  }
}

void square(int num){
  while (num--)
  {
    while (1)
    {
      pid(0.6, 3, 35);
      if (analog(0) < 400)
      {
        fd(30); delay(60);  ao(); sl(50); delay(50);  ao();
        while (analog(3) > ref[3]);
        ao();break;
      }
      if (analog(5) < 400)
      {
        fd(30); delay(60);  ao(); sr(50); delay(50);  ao();
        while (analog(2) > ref[2]);
        ao();break;
      }
    }
  }
}

void pid_BB(float Kp , float Kd , int speed_max){
  while (analog(5) > 300 && analog(0) > 300)pid(Kp, Kd, speed_max);
  while (analog(5) < 300 || analog(0) < 300)pid(Kp, Kd, speed_max);
  ao();
  //pid_T(Kp,Kd,speed_max,100);
}

void pid_BB2(float Kp , float Kd , int speed_max){
  while (analog(5) > 300 || analog(0) > 300)pid(Kp, Kd, speed_max);
  while (analog(5) < 300 && analog(0) < 300)pid(Kp, Kd, speed_max);
  ao();
  //pid_T(Kp,Kd,speed_max,100);
}

void gotokeep(float Kp , float Kd , int speed_max){
  while (1)
  {
    pid(Kp, Kd, speed_max);
    if ( getdist(6)<5 ){
      ao(); break;
    }
  }
  
}

void gotoput(){
  //servo
}

