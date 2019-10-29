#include <ATX2.h>   //Battery 8.3-8.25 V
#include <gp2d120.h>
int light[8] = {320,320,585,275,415,340,340,395};
int power = 50;       //8.3 = 45 8.2 = 50
int power_forsmall_Line = power - 30; //8.3v = -35 8.2v = -20...25...30
int dist=3;
//servo 2 ยิ่งเพิ่มยิ่งแคบ
//servo 1 ยิ่งเพิ่มยิ่งห่าง
//servo 8 ยิ่งเพิ่มยิ่งขั้น
int i;
void Color(){
  //sen8 black = 80   / white = 560   / avg = 320
  //sen1 black = 80   / white = 560   / avg = 320
  //sen2 black = 180  / white = 990   / avg = 585
  //sen10 black = 50   / white = 500   / avg = 275
  //sen4 black = 90   / white = 740   / avg = 415
  //sen5 black = 100  / white = 580   / avg = 340
  //sen6 black = 90   / white = 590   / avg = 340
  //sen7 black = 100  / white = 690   / avg = 395
}
class NormalGo{
  public :
    void Go(){
        while (true) {
        if (analog(6) < light[6] || analog(7) < light[7]){
          motor_stop(ALL);
          break;
        }  
        else {
          fd(power-15);
        }
      }
    }
    void Track(){
      while (true) {
        if ((analog(1) < light[1] && analog(2) < light[2])||(analog(1) < light[1] && analog(8) < light[0])|| (analog(10) < light[3] && analog(2) < light[2])){
            motor_stop(ALL);
          break;
        }  //ถ้ายportซ้ายสุด(0)หรือขวาสุดเจอสีดำหรือp1และp2เจอดำทั้งคู่ให้ออกลูป
        else {
          motor(1, power);
          motor(2, power);
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
      while (true) {
         if (analog(6) < light[6] || analog(7) < light[7]){
          motor_stop(ALL);
          break;
        }  //ถ้ายportซ้ายสุด(0)หรือขวาสุดเจอสีดำหรือp1และp2เจอดำทั้งคู่ให้ออกลูป
        else {
          int a = 30;
          if(power==45) a = 30;
          motor(1, power-a);
          motor(2, power-a);
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
      //Exit();
    }
    void Left() {
      while (analog(1) < light[1]&&analog(10) > light[3]) { //ขณะที่เจอดำ
        motor(1, -35);
        motor(2, 35);
      }
      while (analog(1) > light[1]) { //ขณะที่เจอขาว
        motor(1, -35);
        motor(2, 35);
      }
      while (analog(1) < light[1]) { //ขณะที่เจอดำ
        motor(1, -35);
        motor(2, 35);
      }
      motor_stop(ALL);
   }
    void Right() {
      while (analog(2) < light[2]&&analog(8) > light[0]) { //ขณะที่เจอดำ
        motor(1, 35);
        motor(2, -35);
      }
      while (analog(2) > light[2]) { //ขณะที่เจอขาว
        motor(1, 35);
        motor(2, -35);
      }
      while (analog(2) < light[2]) { //ขณะที่เจอดำ
        motor(1, 35);
        motor(2, -35);
      }
      motor_stop(ALL);
    }
    void Track_forsmallline(){
      while (true) {
        if ((analog(1) < light[1] && analog(2) < light[2])||(analog(1) < light[1] && analog(8) < light[0])|| (analog(10) < light[3] && analog(2) < light[2])){
            motor_stop(ALL);
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
      while (true) {
         if (analog(6) < light[6] || analog(7) < light[7]){
          motor_stop(ALL);
          break;
        }  //ถ้ายportซ้ายสุด(0)หรือขวาสุดเจอสีดำหรือp1และp2เจอดำทั้งคู่ให้ออกลูป
        else {
          motor(1, power_forsmall_Line);
          motor(2, power_forsmall_Line);
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
      //Exit();
    }
    void GoToKeep(){
      while (true) {
        if (analog(1) < light[1] && analog(2) > light[2]) {
          motor(1, 30);
          motor(2, 100);
        }
        if (analog(1) > light[1] && analog(2) < light[2]) {
          motor(1, 100);
          motor(2, 30);
        }
        i=8;
        if(getdist(3)<=i)
        {
          motor_stop(ALL);
          break;
        }
        else {
          motor(1, power-15);
          motor(2, power-15);  
        }
      }
    }
    void GoToKeep_Small(){
      while (true) {
        if (analog(1) < light[1] && analog(2) > light[2]) {
          motor(1, 30);
          motor(2, 100);
        }
        if (analog(1) > light[1] && analog(2) < light[2]) {
          motor(1, 100);
          motor(2, 30);
        }
        i=5;
        if(getdist(3)<=i)
        {
          motor_stop(ALL);
          break;
        }
        else {
          motor(1, power-20);
          motor(2, power-20);  
        }
      }
    }
    void GoToKeep_45_Right(){
      i =5;
      while (true) {
        if(getdist(3)<=i)
        {
          motor_stop(ALL);
          break;
        }
        else
        {
          motor(1, 35);
          motor(2, -35);
        }
        
      }
    }
    void GoToKeep_45_Left(){
      i =5;
      while (true) {
        if(getdist(3)<=i)
        {
          motor_stop(ALL);
          break;
        }
        else
        {
          motor(1, -35);
          motor(2, 35);
        }
        
      }
    }
}Go;
class SmallGo{
  public :
    void Track(){
      while (true) {
        if (analog(6) < light[6] || analog(7) < light[7]){
          motor_stop(ALL);
          break;
        }  
        else {
          motor(1, power-20);
          motor(2, power-20);
        }
      }
      while (true) {
        if (analog(6) > light[6] && analog(7) > light[7]){
          motor_stop(ALL);
          break;
        }  
        else {
          int a = 35;
          motor(1, power-a);
          motor(2, power-a);
        }
      }
    }
    void Left() {
      while (analog(4) < light[4]) { //ขณะที่เจอดำ
        motor(1, -40);
        motor(2, 40);
      }
      while (analog(4) > light[4]) { //ขณะที่เจอขาว
        motor(1, -35);
        motor(2, 35);
      }
      while (analog(4) < light[4]) { //ขณะที่เจอดำ
        motor(1, -30);
        motor(2, 30);
      }
       motor_stop(ALL);
    }
    void Right() {
      while (analog(5) < light[5]) { //ขณะที่เจอดำ
        motor(1, 40);
        motor(2, -40);
      }
      while (analog(5) > light[5]) { //ขณะที่เจอขาว
        motor(1, 35);
        motor(2, -35);
      }
      while (analog(5) < light[5]) { //ขณะที่เจอดำ
        motor(1, 30);
        motor(2, -30);
      }
      motor_stop(ALL);
    }
    void Exit(){
      while (true) {
        if (analog(6) > light[6] && analog(7) > light[7]){
          motor_stop(ALL);
          break;
        }  
        else {
          motor(1, power-15);
          motor(2, power-15);
        }
      }
    }
    void Track_forsmallline(){
      while (true) {
        if ((analog(1) < light[1] && analog(2) < light[2])||(analog(1) < light[1] && analog(8) < light[0])|| (analog(10) < light[3] && analog(2) < light[2])){
            motor_stop(ALL);
          break;
        }  //ถ้ายportซ้ายสุด(0)หรือขวาสุดเจอสีดำหรือp1และp2เจอดำทั้งคู่ให้ออกลูป
        else {
          motor(1, power);
          motor(2, power);
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
      while (true) {
         if (analog(6) < light[6] || analog(7) < light[7]){
          motor_stop(ALL);
          break;
        }  //ถ้ายportซ้ายสุด(0)หรือขวาสุดเจอสีดำหรือp1และp2เจอดำทั้งคู่ให้ออกลูป
        else {
          motor(1, power_forsmall_Line);     //8.3 = 10  8.2 = 20...15
          motor(2, power_forsmall_Line);     //8.3 = 10
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
      //Exit();
    } 
    void Set(){
        while (analog(4) < light[4]) { //ขณะที่เจอดำ
          motor(1, -35);
          motor(2, 35);
        }
        while (analog(5) < light[5]) { //ขณะที่เจอดำ
          motor(1, 35);
          motor(2, -35);
        }
        motor_stop(ALL);
        fd(50); delay(200); ao();
      
    }
    void Set2(){
        while (analog(4) < light[4]) { //ขณะที่เจอดำ
          motor(1, -35);
          motor(2, 35);
        }
        while (analog(5) < light[5]) { //ขณะที่เจอดำ
          motor(1, 35);
          motor(2, -35);
        }
        motor_stop(ALL);
      
    }

}Small;
void setup(){
  OK();// Wait for OK button
  //GoToKeep(); GoToPut(); Stop();      //servoHome();  servoUp();  servoDown(); 
  //Go.Track(); Go.Left();  Go.Right();   Go.Track_forsmallline();
  //Small.Track(); Small.Left();  Small.Right();   Small.Exit();
  //servoHome();  Keep(); Put();
  //Go.Track_forsmallline();  Go.Right();  Go.Track();  Small.Left(); Small.Track(); Small.Right(); Small.Track(); 
  //Small.Exit(); Small.Track(); Small.Right(); Small.Track();  //Small.Left();

  

  servoHome();
  Small.Exit();
  
  ao();
  
}
void loop(){
  //view();  
  //glcd(0,1,"%d",getdist(6));
  //glcdClear();
}

void GoToPut(){
  
    while (true) {
    if (analog(1) < light[1] && analog(2) > light[2]) {
      motor(1, 30);
      motor(2, 100);
    }
    if (analog(1) > light[1] && analog(2) < light[2]) {
      motor(1, 100);
      motor(2, 30);
    }
    if(getdist(5)<=3)
    {
      motor(1, 20);
      motor(2, 20);
      delay(200);
        motor_stop(ALL);
      break;
    }
    else {
      motor(1, 25);
      motor(2, 25);  
    }
  }
}
void Back() {
   while (true) {
    if (analog(1) < light[1] && analog(2) > light[2]) {
      motor(1, -100);
      motor(2, -30);
    }
    if (analog(1) > light[1] && analog(2) < light[2]) {
      motor(1, -30);
      motor(2, -100);
    }
    if (analog(6) < light[6] || analog(7) < light[7]) {
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
    glcd(0, 1, "S8=*%d*", analog(8));
    glcd(1, 1, "S1=*%d*", analog(1));
    glcd(2, 1, "S2=*%d*", analog(2));
    glcd(3, 1, "S10=*%d*", analog(10));
    
    glcd(5, 1, "S4=*%d*", analog(4));
    glcd(6, 1, "S5=*%d*", analog(5));
    glcd(7, 1, "S6=*%d*", analog(6));
    glcd(8, 1, "S7=*%d*", analog(7));
  
}
void servoHome() {
  servo(1, 160);
  servo(2, 0);
  servo(8, 130);
  delay(250);
}
void servoUp() {
  servo(8, 130);
  delay(250);
}
void servoDown() {
  servo(8, 35);
  delay(500);
}
void servoKeep(){
  servo(1,110);
  servo(2,40);
  delay(250);
}
void servoPut(){
  servo(1, 160);
  servo(2, 0);
  delay(250);
}
void Keep(){
  servoDown();
  servoKeep();
  servoUp();
}
void Put(){
  servoDown();
  servoPut();
  servoHome();
}
