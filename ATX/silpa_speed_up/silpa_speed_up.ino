#include <ATX2.h>   //Battery 8.3-8.25 V
#include <gp2d120.h>
#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
int light[10] = {550,400,320,550,300,450,      650,650,650,650};
int power = 90;       //
int power_forsmall_Line = power - 30; //8.3v = -35 8.2v = -20...25...30
int dist=5;
//servo 2 ยิ่งเพิ่มยิ่งแคบ
//servo 1 ยิ่งเพิ่มยิ่งห่าง
//servo 8 ยิ่งเพิ่มยิ่งขั้น
int i=7;
void Color(){
  //sen0 white = 970    / black = 110      / avg = 550
  //sen1 white = 730    / black = 70      / avg = 400
  //sen2 white = 580    / black = 60      / avg = 320
  //sen3 white = 980    / black = 140      / avg = 550
  //sen4 white = 540    / black = 70      / avg = 300
  //sen5 white = 825    / black = 100      / avg = 450

  
  //sen6 white = 1000    / black = 300      / avg = 650
  //sen7 white = 1000    / black = 300      / avg = 650
  //sen8 white = 1000    / black = 300      / avg = 650
  //sen9 white = 1000    / black = 300      / avg = 650

}
void view(int a){
  if(a==1){
  glcd(0,1,"A0 =*%d***",analog(0));
  glcd(1,1,"A1 =*%d***",analog(1));
  glcd(2,1,"A2 =*%d***",analog(2));
  glcd(3,1,"A3 =*%d***",analog(3));
  glcd(4,1,"A4 =*%d***",analog(4));
  glcd(5,1,"A5 =*%d***",analog(5));
  }

  if(a==2){
  glcd(1,1,"A6 = %d    ",analog(6));
  glcd(2,1,"A7 = %d    ",analog(7));
  glcd(3,1,"A8 = %d    ",analog(8));
  glcd(4,1,"A9 = %d    ",analog(4));
  }
}
void servoHome() {
  //servo(1, 180);
  //servo(2, 70);
  servo(1, 70);
  servo(2, 90);
  servo(8, 130);
  delay(250);
}
void servoUp() {
  servo(1, 140);
  servo(2, 30);
  delay(100);
  servo(8, 60);
  delay(250);
  Keep();
  servo(8, 130);
  delay(250);
}
void servoDown() {
  servo(8, 60);
  delay(350);
  Put();
  delay(250);
  servo(8, 130);
  delay(250);
  servoHome();
  delay(250);
}
void Keep(){
  servo(1, 50);
  servo(2, 114);
  delay(250);
}
void Put(){
  servo(1, 80);
  servo(2, 90);
  delay(250);
}

    void Exit(){
      while (true) {
        if (analog(4) > light[4] && analog(5) > light[5] ){  
            motor_stop(ALL);
            delay(100);
          break;
        }  
        else {
          motor(1, power-35);
          motor(2, power-35);
        }

      }
    }
    void Set(){
        while (analog(0) < light[0]) { //ขณะที่เจอดำ
          motor(1, -50);
          motor(2, 50);
        }
        //delay(100);
        while (analog(1) < light[1]) { //ขณะที่เจอดำ
          motor(1, -35);
          motor(2, 35);
        }
        //delay(100);
        while (analog(3) < light[3]) { //ขณะที่เจอดำ
          motor(1, 50);
          motor(2, -50);
        }
        //delay(100);
        while (analog(2) < light[2]) { //ขณะที่เจอดำ
          motor(1, 35);
          motor(2, -35);
        }
        //delay(100);
        motor_stop(ALL);
        delay(100);
    }
    void Track(){
      while (true) {
        if ((analog(3) < light[3] && analog(2) < light[2])||(analog(1) < light[1] && analog(2) < light[2])||(analog(1) < light[1] && analog(0) < light[0]) ){  //
            motor_stop(ALL);
            delay(100);
          break;
        }  //ถ้ายportซ้ายสุด(0)หรือขวาสุดเจอสีดำหรือp1และp2เจอดำทั้งคู่ให้ออกลูป
        else {
          motor(1, power-10);
          motor(2, power-10);
        }
        if (analog(1) < light[1] && analog(2) > light[2]) {
          motor(1, 30);
          motor(2, 100);
        }
        if (analog(1) > light[1] && analog(2) < light[2]) {
          motor(1, 100);
          motor(2, 30);
        }
      }
      /*while (true) {
        if (analog(4) < light[4] || analog(5) < light[5] ){  
            motor_stop(ALL);
            delay(100);
          break;
        }  
        else {
          motor(1, power-10);
          motor(2, power-10);
        }
      }*/
      //Exit();
    }
    void Track_S(){
      while (true) {
        if ((analog(3) < light[3] && analog(2) < light[2])||(analog(1) < light[1] && analog(2) < light[2])||(analog(1) < light[1] && analog(0) < light[0]) ){  //
            motor_stop(ALL);
            delay(100);
          break;
        }  //ถ้ายportซ้ายสุด(0)หรือขวาสุดเจอสีดำหรือp1และp2เจอดำทั้งคู่ให้ออกลูป
        else {
          motor(1, power-5);
          motor(2, power-5);
        }
        if (analog(1) < light[1] && analog(2) > light[2]) {
           motor(1, 30);
          motor(2, 100);
        }
        if (analog(1) > light[1] && analog(2) < light[2]) {
          motor(1, 100);
          motor(2, 30);
        }
        if (analog(0) < light[0]) {
           motor(1, 20);
          motor(2, 80);
        }
        if ( analog(3) < light[3]) {
          motor(1, 80);
          motor(2, 20);
        }
      }
      while (true) {
        if (analog(4) < light[4] || analog(5) < light[5] ){  
            motor_stop(ALL);
            delay(100);
          break;
        }  
        else {
          motor(1, power-5);
          motor(2, power-5);
        }

      }
      //Set();
    }
    void Track_SS(){
      while (true) {
        if ((analog(3) < light[3] && analog(2) < light[2])||(analog(1) < light[1] && analog(2) < light[2])||(analog(1) < light[1] && analog(0) < light[0]) ){  //
            motor_stop(ALL);
            delay(100);
          break;
        }  //ถ้ายportซ้ายสุด(0)หรือขวาสุดเจอสีดำหรือp1และp2เจอดำทั้งคู่ให้ออกลูป
        else {
          motor(1, power-35);
          motor(2, power-35);
        }
        if (analog(1) < light[1] && analog(2) > light[2]) {
           motor(1, 30);
          motor(2, 100);
        }
        if (analog(1) > light[1] && analog(2) < light[2]) {
          motor(1, 100);
          motor(2, 30);
        }
        if (analog(0) < light[0]) {
           motor(1, 20);
          motor(2, 80);
        }
        if ( analog(3) < light[3]) {
          motor(1, 80);
          motor(2, 20);
        }
      }
      while (true) {
        if (analog(4) < light[4] || analog(5) < light[5] ){  
            motor_stop(ALL);
            delay(100);
          break;
        }  
        else {
          motor(1, power-5);
          motor(2, power-5);
        }

      }
      //Set();
    }
    void Track_Small(){
      while (true) {
        if (analog(4) < light[4] || analog(5) < light[5] ){  
            motor_stop(ALL);
            delay(100);
          break;
        }  
        else {
          motor(1, power-35);
          motor(2, power-35);
        }

      }
      Exit();
    }
    void Back(){
      while (true) {
        if ((analog(3) < light[3] && analog(2) < light[2])||(analog(1) < light[1] && analog(2) < light[2])||(analog(1) < light[1] && analog(0) < light[0]) ){  //
            motor_stop(ALL);
            delay(100);
          break;
        } 
        else {
          motor(1, -power);
          motor(2, -power);
        }
        if (analog(1) < light[1] && analog(2) > light[2]) {
           motor(1, -30);
          motor(2, -100);
        }
        if (analog(1) > light[1] && analog(2) < light[2]) {
          motor(1, -100);
          motor(2, -30);
        }

      }
      while (true) {
        if ((analog(3) > light[3] && analog(2) > light[2])||(analog(1) > light[1] && analog(2) > light[2])||(analog(1) > light[1] && analog(0) > light[0]) ){  //
            motor_stop(ALL);
            delay(100);
          break;
        } 
        else {
          motor(1, -power);
          motor(2, -power);
        }
        if (analog(1) < light[1] && analog(2) > light[2]) {
           motor(1, -30);
          motor(2, -100);
        }
        if (analog(1) > light[1] && analog(2) < light[2]) {
          motor(1, -100);
          motor(2, -30);
        }

      }
      //Exit();
    }
    void Back_S(){
      while (true) {
        if (analog(4) < light[4] || analog(5) < light[5]){  //
            motor_stop(ALL);
            delay(100);
          break;
        } 
        else {
          motor(1, -power);
          motor(2, -power);
        }
        if (analog(1) < light[1] && analog(2) > light[2]) {
           motor(1, -30);
          motor(2, -100);
        }
        if (analog(1) > light[1] && analog(2) < light[2]) {
          motor(1, -100);
          motor(2, -30);
        }

      }
      Set();  ao();
      //Exit();
    }
    void Left(int a) {
      motor(1, -50);
      motor(2, 50);
      delay(150);
      while (analog(1) > light[1]) { //ขณะที่เจอขาว
        motor(1, -40);
        motor(2, 40);
      }
      while (analog(1) < light[1]) { //ขณะที่เจอดำ
        motor(1, -30);
        motor(2, 30);
      }
      motor_stop(ALL);
      delay(100);
      if(a==0)  Set();
   }
    void Right(int a) {
      motor(1, 50);
      motor(2, -50);
      delay(150);
      while (analog(2) > light[2]) { //ขณะที่เจอขาว
        motor(1, 40);
        motor(2, -40);
      }
      while (analog(2) < light[2]) { //ขณะที่เจอขาว
        motor(1, 30);
        motor(2, -30);
      }
      motor_stop(ALL);
      delay(100);    
      if(a==0)  Set();  
    }
    void gotokeep(){
      int asd=power;
      power=55;
      
      servo(1, 140);
      servo(2, 30);
      delay(250);
      servo(8, 70);
      delay(100);
      ao();
      while (true) {
         
       
       
        if (getdist(6)<= 5){
          motor_stop(ALL);
          delay(100);
          break;
        }
        /*if ((analog(3) < light[3] && analog(2) < light[2])||(analog(1) < light[1] && analog(2) < light[2])||(analog(1) < light[1] && analog(0) < light[0]) ){  //
            motor_stop(ALL);
            delay(100);
          break;
        }  //ถ้ายportซ้ายสุด(0)หรือขวาสุดเจอสีดำหรือp1และp2เจอดำทั้งคู่ให้ออกลูป*/
        else {
          motor(1, power-20);
          motor(2, power-20);
        }
        if (analog(1) < light[1] && analog(2) > light[2]) {
           motor(1, 30);
          motor(2, 100);
        }
        if (analog(1) > light[1] && analog(2) < light[2]) {
          motor(1, 100);
          motor(2, 30);
        }
      }
      Keep();
      servo(8, 130);
      delay(250);
      power = asd;
    }
    void rightkeep(){
      while (getdist(6)>6) { //ขณะที่เจอขาว
        motor(1, 40);
        motor(2, -40);
      }
      motor_stop(ALL);
      delay(100); 
      servoUp();
      while (analog(1)>light[1]) { //ขณะที่เจอขาว
        motor(1, -30);
        motor(2, 30);
      }
      while (analog(1)<light[1]) { //ขณะที่เจอขาว
        motor(1, -30);
        motor(2, 30);
      }
    }
    void leftkeep(){
      //Left(0);
      //delay(100);
      while (getdist(6)>6) { //ขณะที่เจอขาว
        motor(1, -40);
        motor(2, 40);
      }
      motor_stop(ALL);
      delay(100); 
      servoUp();
      while (analog(2)>light[2]) { //ขณะที่เจอขาว
        motor(1, 40);
        motor(2, -40);
      }
      while (analog(2)<light[2]) { //ขณะที่เจอขาว
        motor(1, 30);
        motor(2, -30);
      }
      ao();
      //Set();
    }
    void backkeep(){
      while (true) {
        if (analog(4) < light[4] || analog(5) < light[5] ){  
            motor_stop(ALL);
            delay(100);
          break;
        }  
        else {
          motor(1, -power+30);
          motor(2, -power+30);
        }

      }
      gotokeep();
    }
    void gotoput(int a){
      
      if(a==1){
      fd(30); delay(350); ao(); delay(100);
      servoDown();
      while (true) {
        if (analog(4) < light[4] || analog(5) < light[5] ){  
            motor_stop(ALL);
            delay(100);
          break;
        }  
        else {
          motor(1, -power+30);
          motor(2, -power+30);
        }

      }
      //servoDown();
    }

    if(a==2){
      
      //bk(35); delay(200); ao(); delay(50);
      motor(1, -50);
      motor(2, 50);
      delay(110);
      ao();
      delay(150);
      servoDown();
      delay(150);
      motor(1, 50);
      motor(2, -50);
      delay(110);
      ao();
    }

    if(a==3){
      //bk(35); delay(200); ao(); delay(50);
      motor(1, 50);
      motor(2, -50);
      delay(110);
      ao();
      delay(150);
      servoDown();
      delay(150);
      motor(1, -50);
      motor(2, 50);
      delay(110);
      ao();
    }
    if(a==4){
       
      servoDown();
      ao();
    }
    if(a==5){
      while (true) {
        if ((analog(3) < light[3] && analog(2) < light[2])||(analog(1) < light[1] && analog(2) < light[2])||(analog(1) < light[1] && analog(0) < light[0])){  
            motor_stop(ALL);
            delay(100);
          break;
        }  
        else {
          motor(1, -30);
          motor(2, -30);
        }
      }
      servoDown();
      power = 60;
      Track_Small();
      power = 90;
    }
    ao(); delay(200); 
    }
    void rightput(){
      while (analog(3) > light[3]) { //ขณะที่เจอขาว
        motor(1, 30);
        motor(2, -30);
      }
      //fd(30); delay(300); ao(); delay(100);
      /*while (true) {
        if (analog(0) < light[0] ){  
            motor_stop(ALL);
            delay(100);
          break;
        }  
        else {
          motor(1, -power+30);
          motor(2, -power+30);
        }
      }*/
      ao();
      delay(100);
      servoDown();
    
}
    void leftput(){
      while (analog(0) > light[0]) { //ขณะที่เจอขาว
        motor(1, -30);
        motor(2, 30);
      }
      /*fd(30); delay(200); ao(); delay(100);
      while (true) {
        if (analog(3) < light[3] ){  
            motor_stop(ALL);
            delay(100);
          break;
        }  
        else {
          motor(1, -power+30);
          motor(2, -power+30);
        }
      }*/
      ao();
      delay(100);
      servoDown();
    
}
    void Return(int a) {   //Try power++
      motor(1, 50);
      motor(2, -50);
      delay(150);
      ao();
      while (analog(3) > light[3]) { //ขณะที่เจอขาว
        motor(1, 40);
        motor(2, -40);
      }
      //ao();
      while (analog(3) < light[3]) { //ขณะที่เจอดำ
        motor(1, 40);
        motor(2, -40);
      }
      
      motor_stop(ALL);
      delay(100);
      if(a==0)  Set();
   }
    void ex_sq(int a){ //track มาแล้วนะ
      if(a==1){ //ซ้าย
        Left(1);  Track_Small();  Right(1); Track_Small();  Left(0);
      }
      if(a==2){ //บน
        Left(1);  Track_Small();  Right(1); Track_SS(); Track_Small();  Right(1); Track_Small();  Left(0); 
      }
      if(a==3){ //ขวา
        Right(1); Track_Small();  Left(1);  Track_Small();  Right(0);
      }
      if(a==4){ //กลับที่เดิม
         Left(1);  Track_Small();  Right(1); Track_SS(); Track_Small();  Right(1); Track_SS();  Track_Small();  Right(1); Track_SS(); Track_Small();  Right(1); Track_Small();  Left(0);   
      }
      if(a==5){ //สี่เหลี่ยมใหญ่
        Right(0); Track_SS();  Left(0); Track_S();  Left(0);  Track_SS(); Right(0);
      }
      if(a==6){ //สี่เหลี่ยมเล็ก2ทาง
        Right(1); Track_Small();  Left(0); Track_SS();  Left(1);  Track_Small(); Right(0);
      }
    }
void setup(){
    //GoToKeep(); GoToPut(); Stop();      //servoHome();  servoUp();  servoDown(); 
    // Track(); Left(...);  Right(...);   Track_S();  Track_Small(); gotokeep  rightkeep leftkeep backkeep gotoput rightput leftput Return ex_sq
    OK();
    glcdClear();
    //fd(70); delay(500); ao();
    servoHome();  
    Track_SS(); ex_sq(2); Track_SS(); Right(0);  Track_SS(); Right(0);  Track_SS(); Left(0);  Track_SS();  leftkeep();  //Right(0);
    Track_S();  Right(0); Track_SS(); Left(0);  Track_SS(); Right(0); Track_S();  Left(0);  Track_SS(); gotoput(1); 
    Right(0); Right(0); Track_SS(); Track_SS(); ex_sq(6); Track_SS(); Right(0); backkeep(); Right(0); Track_SS(); ex_sq(6); Track_SS(); Track_SS(); gotoput(2);
    Right(0); Right(0); Track_SS(); Left(0);  Track_SS();  ex_sq(1);  Track_SS(); Track_SS(); Track_SS(); Left(1);  backkeep(); Left(0);
    Track_SS(); Track_SS(); Track_SS(); ex_sq(3); Track_S();  Track_S();  Set();  Track_SS(); gotoput(5); power = 60; ex_sq(2); 
}

void loop(){
  //view(1);  
  //glcd(5,1,"*%d*",getdist(6));
  
  //servo(2,knob(180));
  //glcd(0,0,"%d  ",knob(180));
}
