#include <ipst.h>
byte x;  //wireless x
//ขวา ดำ 200 ขาว 700
//ซ้าย ดำ 200 ขาว 700
int right = 450;      //วัดใหม่เปลี่ยนเลขด้วย
int left = 450;
void setup() {
  OK();
  Serial1.begin(9600);
  //fd2(50, 50); delay(500); ao();
  servo(2,29);
  servo(1,0);
  delay(250);
  
  //hand();  //บังคับมือ
  
  track(75);
  goleft(50);
  track(75);
  goright(50);
  
  smallup();  bigdown();
  back();
  back();
  smalldown();

  track(50);
  track(50);
  track(50);
  track(50);
  track(50);
  track(50);
  fd(50); delay(400);
  
  goleft(65);
  ao(); delay(100);
  fd(50); delay(150);
  ao();
  goleft(65);
  
  back();
  motor(1,-60);
  motor(2,-60);
  delay(300);

  smallup();  track(70);  bigup();

  
  
  
  ao();
}
void loop () {
  glcd(1, 0, "R= %d  " ,analog(2));
  glcd(2, 0, "L= %d  " ,analog(1));
}
void track(int speed) {    //เดินหน้าจนกว่าจะเจอเส้นตัด
  while(1){
    if( analog(2)<right && analog(1)<left ){        //ดำคู่ หยุด
      break;
    }
    else if( analog(2)<right && analog(1)>left ){   //ดำขวา เลี้ยงเข้าขวา
      motor(1,speed+20);
      motor(2,speed-20);
    }
    else if( analog(2)>right && analog(1)<left ){   //ดำซ้าย เลี้ยงเข้าซ้าย
      motor(1,speed-20);
      motor(2,speed+20);
    }
    else{
      motor(1,speed);
      motor(2,speed);    
      }
  }
  if(speed>60){
    motor(1,100);
    motor(2,100);
    delay(200);
  }
  else{
    motor(1,speed);
    motor(2,speed);
    delay(200);  
  }
  ao();
}
void back() {    //ถอยหน้าจนกว่าจะเจอเส้นตัด
  while(1){
    if( analog(2)<right && analog(1)<left ){        //ดำคู่ หยุด
      break;
    }
    else if( analog(2)<right && analog(1)>left ){   //ดำขวา เลี้ยงเข้าขวา
      motor(1,-60);
      motor(2,-40);
    }
    else if( analog(2)>right && analog(1)<left ){   //ดำซ้าย เลี้ยงเข้าซ้าย
      motor(1,-40);
      motor(2,-60);
    }
    else{
      motor(1,-65);
      motor(2,-65);    
      }
  }
  motor(1,-100);
  motor(2,-100);
  delay(50);
  ao();
}
void bigdown(){
  servo (2,100);
  delay (200);
}
void bigup(){
  servo (2,29);
  delay (200);
  servo (2, -1);
}
void smalldown(){
  servo (1, 0);
  delay (1000);
}
void smallup(){
  servo (1, 105);
  delay (200);
}
void goright(int speed){
  motor(1,80);
  motor(2,-80);
  delay(100);
  while( analog(2)>right ){
    motor(1,speed);
    motor(2,-speed);
  } ao();
}
void goleft(int speed){
  motor(1,-80);
  motor(2,80);
  delay(100);
  while(analog(1)>left){
    motor(1,-speed);
    motor(2,speed);
  } ao();
}
void hand() {      //บังคับมือ
  while(1){
  while (Serial1.available() > 0)
    x = Serial1.read();
    glcd(4,0," %h ",x);
  if (x == 0x90)//เดินหน้าช้าๆ
  {
    fd2(-70, -70);
  }
  else if (x == 0xA0)//โค้งขวา
  {
    fd2(-50, -100);
  }
  else if (x == 0xC0)//โค้งซ้าย
  {
    fd2(-100, -50);
  }
  else if (x == 0xA0)//โค้งหลังขวา
  {
    fd2(100, 50);
  }
  else if (x == 0xC0)//โค้งหลังซ้าย
  {
    fd2(50, 100);
  }
  else if (x == 0x80)//เดินหน้า
  {
    fd2(-100, -100);
  }
  else if (x == 0x10)//ถอยหลัง
  {
    bk2(-80, -80);
  }
  else if (x == 0x20)//เลี้ยงขวา
  {
    sr(35);
  }
  else if (x == 0x40)//เลี้ยงซ้าย
  {
    sl(35);
  }
  else if (x == 0x08)//ขึ้น
  {
    servo (2,29);
    delay (200);
    servo (2, -1);
  }
  else if (x == 0x01)//ลง
  {
    servo (2,100);
    delay (200);
  }
  else if (x == 0x04)//อ้า
  {
    servo (1, 0);
    delay (1000);
  }
  else if (x == 0x02)//หุบ
  {
    servo (1,105);
    delay (200);
  }
  else if (x == 0xFF)//เข้า auto
  {
    break;
  }
  else ao();
  }
}
