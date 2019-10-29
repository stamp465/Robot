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
  beep();
  delay(500);
  pid_T(0.5,1,20,250);
  pid_T(0.5,1,40,1000);
  
  
}

void loop() {
  /*Serial.print("  readline");
    Serial.println(readline());
    delay(1);*/
  
    glcd(6, 0, "%d   ", analog(0));
    glcd(7, 0, "%d   ", analog(1));
    glcd(8, 0, "%d   ", analog(2));
    glcd(9, 0, "%d   ", analog(3));
    glcd(10, 0, "%d   ", analog(4));
    glcd(11, 0, "%d   ", analog(5));
  
  ao();
}

void Left(){
  fd(30); delay(60);  ao();   //ถ้าเลี้ยวไม่สวยเอาออก
  sl(50); delay(50); 
  while (analog(2) > ref[2]) {
    sl(30);
  } ao(); delay(50);    //ถ้าเลี้ยวไมไ่ด้ เพิ่ม delay
}

void Right(){ 
  fd(30); delay(60);  ao();   //ถ้าเลี้ยวไม่สวยเอาออก
  sr(50); delay(50); 
  while (analog(3) > ref[3]){
    sr(30);
  } ao(); delay(50);    //ถ้าเลี้ยวไมไ่ด้ เพิ่ม delay
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

void keep(){
  //servo
  servo(2,กาง);
  servo(1,ลง);
  servo(2,หุบ);
}

void put(){
  servo(2,กาง);
  servo(1,ขึ้น);
}
