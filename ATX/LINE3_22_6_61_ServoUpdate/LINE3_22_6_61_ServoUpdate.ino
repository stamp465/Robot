#include <ATX2.h>   //Battery 8.3>8.2 V
#include <gp2d120.h>
int light = 150;
int power = 60;
int dist;
float i=4;
void setup()
{
  OK();// Wait for OK button
  // Track();  Right();  Left(); Back(); GoToKeep(); GoToPut(); Stop();
    //servoHome();  servoUp();  servoDown();
    servoHome();
    Track();
    Track();
    Left();
    GoToKeep();
    //servoDown();
    servoUp();
    Back();
    motor(1, 100);
    motor(2, -100);
    delay(10);
    ao();
    Right();
    Track();
    Track();
    GoToPut();
    servoDown();
    servoHome();
    Back();



    
    i = 4;
    Right();
    motor(1, 100);
    motor(2, -100);
    delay(20);
    ao();
    GoToKeep();
    //servoDown();
    servoUp();
    Back();
    Right();
    motor(1, 100);
    motor(2, -100);
    delay(10);
    /*Back();
    Track();
    Track();
    Right();
    Back();
    Right();
    Track();
    Left();*/
    /*motor(1, 100);
    motor(2, -100);
    delay(20);
    ao();*/
    Track();
    Right();
    Track();
    Track();
    Right();
    Track();
    GoToPut();
    servoDown();
    servoHome();
    Back();




    i = 3.5;
    Right();
    motor(1, 80);
    motor(2, -80);
    delay(10);
    ao();
    Track();
    Left();
    GoToKeep();
    //servoDown();
    servoUp();
    Back();
    /*Right();
    motor(1, 80);
    motor(2, -80);
    delay(20);
    ao();
    Track();
    Right();
    Track();
    Right();
    Track();
    Track();
    GoToPut();
    servoDown2();
    servoHome();
    Back();*/
    Left();
    /*motor(1, -80);
    motor(2, 80);
    delay(20);*/
    Track();
    Left();
    Track();
    Right();
    GoToPut();
    motor(1, 80);
    motor(2, -80);
    delay(10);
    ao();
    servoDown();
    servoHome();
    Back();





    i=3.5;
    Right();
    motor(1, 80);
    motor(2, -80);
    delay(10);
    ao();
    Track();
    Left();
    GoToKeep();
    //servoDown();
    servoUp();
    Back();
    Left();
    Track();
    Left();
    Track();
    Track();
    GoToPut();
    servoDown();
    servoHome();
    Back();






    Right();
    motor(1, 80);
    motor(2, -80);
    delay(10);
    ao();
    Track();
    Track();
    Stop();
}
void loop(){
//view();  
//glcd(0,1,"%d",dist);
}
void Stop() {
    while (true) {
    if (analog(1) < light && analog(2) > light) {
      motor(1, 30);
      motor(2, 100);
    }
    if (analog(1) > light && analog(2) < light) {
      motor(1, 100);
      motor(2, 30);
    }
    if (analog(3) < light || analog(4) < light) {
     /* while(analog(3) > light && analog(4) > light)
      {
        motor(1, power);
        motor(2, power);
      }*/
      motor(1, power);
      motor(2, power);
      delay(4);
      motor_stop(ALL);
      break;
    }  //ถ้ายportซ้ายสุด(0)หรือขวาสุดเจอสีดำหรือp1และp2เจอดำทั้งคู่ให้ออกลูป
    else {
      motor(1, power);
      motor(2, power);
    }
  }
}
void GoToKeep(){
  
    while (true) {
    if (analog(1) < light && analog(2) > light) {
      motor(1, 30);
      motor(2, 100);
    }
    if (analog(1) > light && analog(2) < light) {
      motor(1, 100);
      motor(2, 30);
    }
    if(getdist(5)<=i)
    {
        motor_stop(ALL);
        break;
    }
    else {
      motor(1, 15);
      motor(2, 15);  
    }
  }
}
void GoToPut(){
  
    while (true) {
    if (analog(1) < light && analog(2) > light) {
      motor(1, 30);
      motor(2, 100);
    }
    if (analog(1) > light && analog(2) < light) {
      motor(1, 100);
      motor(2, 30);
    }
    if(getdist(5)<=3&&getdist(5)<4)
    {
      motor(1, 20);
      motor(2, 20);
      delay(50);
        motor_stop(ALL);
      break;
    }
    else {
      motor(1, 20);
      motor(2, 20);  
    }
  }
}
void Track() {
  while (true) {
    if (analog(1) < light && analog(2) > light) {
      motor(1, 30);
      motor(2, 100);
    }
    if (analog(1) > light && analog(2) < light) {
      motor(1, 100);
      motor(2, 30);
    }
    if (analog(1) < light && analog(2) < light) {
     /* while(analog(3) > light && analog(4) > light)
      {
        motor(1, power);
        motor(2, power);
      }*/
      motor(1, power);
      motor(2, power);
      delay(50);
      motor_stop(ALL);
      break;
    }  //ถ้ายportซ้ายสุด(0)หรือขวาสุดเจอสีดำหรือp1และp2เจอดำทั้งคู่ให้ออกลูป
    else {
      motor(1, power);
      motor(2, power);
    }
  }
  /*motor(1, 100);
  motor(2, 100);
  delay(40);
  motor_stop(ALL);
  delay(40);*/
}
void Left() {
  motor(1, -70);
  motor(2, 70);
  delay(50);
  while (analog(1) > light) { //ขณะที่เจอขาว
    motor(1, -70);
    motor(2, 70);
  }
  motor(1, 100);
  motor(2, -100);
  delay(20);
  motor_stop(ALL);
}
void Right() {
  motor(1, 70);
  motor(2, -70);
  delay(50);
  //motor_stop(ALL);
  while (analog(2) > light) {
    motor(1, 50);
    motor(2, -50);
  }
  motor(1, -100);
  motor(2,  100);
  delay(20);
  motor_stop(ALL);
}
void Back() {
   while (true) {
    if (analog(1) < light && analog(2) > light) {
      motor(1, -100);
      motor(2, -30);
    }
    if (analog(1) > light && analog(2) < light) {
      motor(1, -30);
      motor(2, -100);
    }
    if (analog(3) < light || analog(4) < light) {
      motor(1, -power);
      motor(2, -power);
      delay(10);
      motor_stop(ALL);
      break;
    }  //ถ้ายportซ้ายสุด(0)หรือขวาสุดเจอสีดำหรือp1และp2เจอดำทั้งคู่ให้ออกลูป
    else {
      motor(1, -power+40);
      motor(2, -power+40);
    }
  }
  
}
void view() {
 
    setTextSize(1);
    glcd(0, 1, "S0=*%d*", analog(1));
    glcd(2, 1, "S1=*%d*", analog(2));
    glcd(4, 1, "S2=*%d*", analog(3));
    glcd(6, 1, "S3=*%d*", analog(4));
  
}
void servoHome() {
  servo(1, 100);
  servo(2, 0);
  servo(8, 100);
}

void servoUp() {
  servo(8, 35);
  delay(300);
  servo(1, 20);
  servo(2, 90);
  delay(300);
  servo(8, 100);
}


void servoDown() {
  delay(200);
  servo(8, 0);
  //delay(500);
  servo(8, 10);
  delay(300);
  servo(1, 40);
  servo(2, 70);
  delay(100);
  servo(1, 50);
  servo(2, 60);
  delay(100);
  servoHome();
}
void servoDown2(){
  servo(8, 40);
  delay(300);
  servo(8, 30);
  delay(300);
  servo(8, 20);
  delay(300);
  servo(8, 10);
  delay(300);
  servo(2, 118);
  delay(300);
  servo(1, 95);
  delay(300);
  servo(2, 88);
  delay(300);
  servo(1, 115);
  delay(300);
  servoHome();
}


