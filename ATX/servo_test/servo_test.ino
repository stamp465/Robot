#include <ATX2.h>
void servoHome() {
  servo(1, 100);
  servo(2, 0);
  servo(8, 100);
}

void servoUp() {
  servo(8, 30);
  delay(1000);
  servo(1, 20);
  servo(2, 90);
  delay(500);
  servo(8, 100);
}


void servoDown() {
  delay(500);
  servo(8, 0);
  //delay(500);
 // servo(8, 10);
  delay(500);
  servo(1, 40);
  servo(2, 70);
  servoHome();
}
int x;
void setup() {
  OK();
//servo(2,55);
servoHome();
  servoUp();
  servoDown();
  servoHome();
  


}
void loop() {
 //x=knob(180);
 //servo(8,40);
 //glcd(1,1,"%d   ",x);  


}
