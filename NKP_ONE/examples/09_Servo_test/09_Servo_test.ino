#include <NKP_ONE.h>   //เรียกใช้ชุดคำสั่งทั้งหมด
void setup() {
  NKP_ONE();     //ประกาศใช้ชุดคำสั่ง
  IO15();       //รอจนกว่าจะกด SW1 เพื่อทำงาน
}
void loop() {
  servo(1,0);    //สั่งให้ Servo ตัวที่ 1 หมุนไปยังตำแหน่ง 0 องศา
  delay(1000);  //หน่วงเวลา 1 วินาที
  servo(1,90);  //สั่งให้ Servo ตัวที่ 1 หมุนไปยังตำแหน่ง 90 องศา
  delay(1000);  //หน่วงเวลา 1 วินาที
  servo(1,180); //สั่งให้ Servo ตัวที่ 1 หมุนไปยังตำแหน่ง 180 องศา
  delay(1000);  //หน่วงเวลา 1 วินาที
  servo(2,180); //สั่งให้ Servo ตัวที่ 2 หมุนไปยังตำแหน่ง 180 องศา
  delay(1000);  //หน่วงเวลา 1 วินาที
  servo(2,90);  //สั่งให้ Servo ตัวที่ 2 หมุนไปยังตำแหน่ง 90 องศา
  delay(1000);  //หน่วงเวลา 1 วินาที
  servo(2,0);  //สั่งให้ Servo ตัวที่ 2 หมุนไปยังตำแหน่ง 0 องศา
  delay(1000);  //หน่วงเวลา 1 วินาที

  
}
