#include <ipst.h>
/*
 อ่านก่อนแก้โค้ด
 1. ตรวจสภาพหุ่นให้เรียบร้อย
 2. เริ่มแรก คอมเม้นทุกอย่าง แล้วเอา code ใน void loop ไปวัดแล้ว แล้วมาจดไว้
 3. เช็คตำแหน่ง servo ทั้ง 2 อัน แล้วจดไว้
 4. เริ่มจากการเช็ค track(x); ว่าเดินตามเส้นไหม และหยุดเมื่อเจอ ดำ ดำ ไหม ถ้ามันผิด อาจเกิดจาก
    4.1 ค่าเซ็นเซอร์ ( โอกาส 40 % )
    4.2 โค้ด ( โอกาส 60 % ) //ดูการแก้ในคอมเม้นได้เลย
 5. เช็คเลี้ยวซ้าย เลี้ยวขวา  goleft(x); goright(x); ถ้ามีปัญหาจะเกิดจาก 
    4.1 โค้ด ( โอกาส 50 % ) //ดูการแก้ในคอมเม้นได้เลย
    4.2 หุ่น ( โอกาส 50 % ) บางตัวมันมีตัวค้ำทำให้พอมีกระป๋องแล้วเลี้ยวฝืด ***ระวังด้วย***
 6. เช็คโค้ด servo ให้เรียบร้อย 
 7. ต่อโค้ดแล้วเอาไปลอง และลองปรับแก้ไขเอง
 หมายเหตุ x = เลขจำนวนเต็มใดๆ ที่ไม่เกิน 100 หรือ -100
 */
//วัดแล้วจดไว้ตรงนี้ ***เช็คด้านหน้าหุ่นให้ดีๆ*** โค้ดนี้เขียนไว้ให้ด้านหน้าหุ่นไปทางเดียวกับเซ้นเซอร์ ***เช็คมอเตอร์ด้วย***
//มอเตอร์ 1 ซ้าย มอเตอร์ 2 ขวา ***ด้านหน้าหุ่นไปทางเดียวกับเซ้นเซอร์***
//เซ็นเซอร์ขวา ดำ 200 ขาว 700    
//เซ็นเซอรซ้าย ดำ 200 ขาว 700
//servo 1 ยก 105 หุบ 0
//servo 2 ยก 29 หุบ 100
byte x;  //wireless x
//ค่าเฉลี่ยของเซ็นเซอร์ ซ้าย กับ ขวา = (ขาว+ดำ)/2
int right = 450;      //***วัดใหม่เปลี่ยนเลขด้วย***
int left = 450;

void setup() {
  
  OK();         //อย่าไปคอมเม้นนะ
  
  Serial1.begin(9600);  //อันนี้เอาไว้เชื่อมต่อกับjoystrick มั้ง
  
  //fd2(50, 50); delay(500); ao();  //ใส่ไว้ทดสอบเดินหน้าว่าตรงไหม
  
  //ปรับ servo ให้อยู่ในจุดปลอยภัย (ขึ้นอยู่กับหุ่นที่ใช้)
  servo(2,29);   
  servo(1,0);
  delay(250);
  
  //hand();  //บังคับมือ หลังจาก กด ปุ่มกลาง จะออกจากการบังคับมือมาทำโค้ดข้างล่างนี้ต่อ

  //เดินตามเส้นอัตโนมัติ
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

  
  
  
  ao(); //หยุดตอนจบ อย่าไปคอมเม้นนะ
}
void loop () {    //เอาไว้วัดค่าแสง
  glcd(1, 0, "R= %d  " ,analog(2));
  glcd(2, 0, "L= %d  " ,analog(1));
}
void track(int speed) {    //เดินหน้าจนกว่าจะเจอเส้นตัด ดำ ดำ และจะเห็นว่า มีค่า speed ด้วย ดูตัวอย่างการใช้จากโค้ดในset up ได้เลย
  while(1){
    if( analog(2)<right && analog(1)<left ){        //ดำคู่ หยุด
      break;  // ออกลูปไปทำข้างล่าง
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
  //ค่า speed จะส่งผลต่อการหยุด และเดินหน้าต่อจากการหยุด(เพื่อเลี้ยว)
  //speed>60 ใช้เดินปกติ
  //speed<=60 ใช้ตอนมีกระป๋อง เอาไว้กันกระป๋องล้ม
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
void back() {    //ถอยหน้าจนกว่าจะเจอเส้นตัด โค้ดจะตรงข้ามกับ track แต่ speed เป็นติดลบหมด อันนี้ไม่ต้องกำหนด speed เพราะกำหนดให้แล้ว ถ้าจะเปลี่ยนเปลี่ยนในนี้เลย
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
  //ถอยหลังนิดหนึ่งไว้ตั้งวงเลี้ยว
  motor(1,-100);
  motor(2,-100);
  delay(50);
  ao();
}
//code servo ตรงตามชื่อ ขอให้แปลออกกันนะ
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
void goright(int speed){  //เลี้ยวขวา
  //กระตุดขวาในเซ็นเซอร์ที่ใช้เสี้ยวเจอสีขาวแน่ๆ
  motor(1,80);
  motor(2,-80);
  delay(100);
  while( analog(2)>right ){
    motor(1,speed);
    motor(2,-speed);
  } ao();
}
void goleft(int speed){ //เลี้ยวซ้าย
  //กระตุดซ้ายในเซ็นเซอร์ที่ใช้เสี้ยวเจอสีขาวแน่ๆ
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
