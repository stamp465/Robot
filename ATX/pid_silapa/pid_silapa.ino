#include <ATX2.h>	
int Max_Light[12] = {1000, 1000, 1000, 1000, 1000, 1000 , 1000, 1000, 1000, 1000, 1000, 1000};     //ใส่ค่าแสงที่ได้ค่ามากจาก  Sensor (เจอสีขาว)
int Min_Light[12] = {600 , 600 , 600 , 300 , 600 , 300 , 300 , 300 , 300  , 300 , 300 , 300};      //ใส่ค่าแสงที่ได้ค่ามากจาก  Sensor (เจอสีดำ)
int ref[12] = {((Max_Light[0]+Min_Light[0])/2)
              ,((Max_Light[1]+Min_Light[1])/2)
              ,((Max_Light[2]+Min_Light[2])/2)
              ,((Max_Light[3]+Min_Light[3])/2)
              ,((Max_Light[4]+Min_Light[4])/2)
              ,((Max_Light[5]+Min_Light[5])/2)
              ,((Max_Light[6]+Min_Light[6])/2)
              ,((Max_Light[7]+Min_Light[7])/2)
              ,((Max_Light[8]+Min_Light[8])/2)
              ,((Max_Light[9]+Min_Light[9])/2)};

int number_Sensor = 5;
int setpoint = 0;
int state_on_Line = 0;
float Kp = 3;//4 3
float Ki = 0;
float Kd = 40;//14 40
float present_position;
float errors = 0;
float output = 0;
float integral ;
float  derivative ;
float previous_error ;
int Percent_Light[12];
int power = 50;
void servoHome() {
  //servo(1, 180);
  //servo(2, 70);
  servo(1, 70);
  servo(2, 100);
  servo(8, 80);
  delay(250);
}
 void servoUp() {
  servo(1, 100);
  servo(2, 70);
  delay(100);
  servo(8, 15);
  delay(250);
  Keep();
  servo(8, 80);
  delay(250);
}
void servoDown() {
  servo(8, 15);
  delay(350);
  Put();
  delay(250);
  servo(8, 80);
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
void GoToPut(int A){
  if(A==1){           //สำหรับช่องใหญ่ เดินหน้าวาง
    fd(50); delay(100); ao();
    servoDown();
    
  }
  else if(A==2){      //สำหรับช่องใหญ่  วางซ้าย
    
  }
  else if(A==3){      //สำหรับช่องใหญ่  วางขวา
    
  }
  else if(A==4){      //สำหรับช่องเล็ก
    
  }
  else if(A==5){      //สำหรับช่องเล็ก
    
  }
  else if(A==6){      //สำหรับช่องเล็ก
    
  }
}

long Position() {
  long sum_value_total = 0;
  long divide_value_total = 0;
  Percent_Light[0] = map(analog(0), Min_Light[0], Max_Light[0], 100, 0);
  Percent_Light[1] = map(analog(1), Min_Light[1], Max_Light[1], 100, 0);
  Percent_Light[2] = map(analog(2), Min_Light[2], Max_Light[2], 100, 0);
  Percent_Light[3] = map(analog(3), Min_Light[3], Max_Light[3], 100, 0);
  Percent_Light[4] = map(analog(4), Min_Light[4], Max_Light[4], 100, 0);
 /* Percent_Light[6] = map(analog(7), Min_Light[6], Max_Light[6], 100, 0);
  Percent_Light[7] = map(analog(8), Min_Light[7], Max_Light[7], 100, 0);
  Percent_Light[8] = map(analog(9), Min_Light[8], Max_Light[8], 100, 0);*/

sum_value_total =  0 * Percent_Light[0]     +  25 * Percent_Light[1] + 50 * Percent_Light[2]
                     + 75 * Percent_Light[3] +  100 * Percent_Light[4] ;//15 30 45 60
  /*
  sum_value_total =  0 * Percent_Light[1]     +  15 * Percent_Light[2] + 30 * Percent_Light[3]
                     + 45 * Percent_Light[4] +  60 * Percent_Light[5] +  75 * Percent_Light[6]
                     + 90 * Percent_Light[7] +  105 * Percent_Light[8];*/
  divide_value_total = Percent_Light[0] + Percent_Light[1] + Percent_Light[2] 
                       + Percent_Light[3] + Percent_Light[4];

  if (divide_value_total != 0) {
    return (sum_value_total / divide_value_total) ;
  }
}

void view(int a){
  if(a==1){
  glcd(0,1,"A0 = %d    ",analog(0));
  glcd(1,1,"A1 = %d    ",analog(1));
  glcd(2,1,"A2 = %d    ",analog(2));
  glcd(3,1,"A3 = %d    ",analog(3));
  glcd(4,1,"A4 = %d    ",analog(4));
  }

  if(a==2){
  glcd(0,1,"A5 = %d    ",analog(5));
  glcd(1,1,"A6 = %d    ",analog(6));
  
  glcd(2,1,"A7 = %d    ",analog(7));
  glcd(3,1,"A8 = %d    ",analog(8));
  glcd(4,1,"A9 = %d    ",analog(9));
  }
}

void Run_Long() {                              //เดินตามเส้นจนกว่า sensor ด้านหน้าจะเจอเส้นตัด //เส้นยาว
  do  {
    if (analog(0) < ref[0] )state_on_Line = 1;
    if (state_on_Line == 1 && analog(1) < ref[1])state_on_Line = 0;
    if (analog(4) < ref[4] )state_on_Line = 2;
    if (state_on_Line == 2 && analog(3) < ref[3])state_on_Line = 0;
    switch (state_on_Line) {
      case 0: {
          present_position = Position();
        } break;
      case 1: {
          present_position = 5.0;
        } break;
      case 2: {
          present_position = 60.0;
        } break;
    }
    setpoint = 100/2;
    errors = setpoint - present_position;
    integral = integral + errors ;
    derivative = (errors - previous_error) ;
    output = Kp * errors + Ki * integral + Kd * derivative;
    previous_error = errors;
    int speed_max = 65;//50
    int speed_motor_forword = speed_max + output;
    int speed_motor_backward = speed_max - output;
    if (speed_motor_forword > 75)speed_motor_forword = 75;//60
    if (speed_motor_forword < 0 )speed_motor_forword = 0;
    if (speed_motor_backward > 75)speed_motor_backward = 75;//60
    if (speed_motor_backward < 0 )speed_motor_backward = 0;
    if (Position() > 0) {
      motor(2, speed_motor_forword);
      motor(1, speed_motor_backward);
    }
    else {
      motor(2, speed_motor_backward);
      motor(1, speed_motor_forword);
    }
  }while(!((analog(0) < ref[0] && analog(1) < ref[1]) || (analog(3) < ref[3] && analog(4) < ref[4])));
  ao();
  while(true){
    if(analog(5)<ref[5]||analog(9)<ref[9]){
      ao();
      delay(100);
      break;
    }
    else{
      motor(1, -power);
      motor(2, -power);
    }
  }
  //while ((analog(2) > ref[1]  && analog(9) > ref[8])||(analog(2) < ref[1]  && analog(9) > ref[8])||(analog(2) > ref[1]  && analog(9) < ref[8]));

}
void Run() {                              //เดินตามเส้นจนกว่า sensor ด้านหน้าจะเจอเส้นตัด
  do  {
    if (analog(0) < ref[0] )state_on_Line = 1;
    if (state_on_Line == 1 && analog(1) < ref[1])state_on_Line = 0;
    if (analog(4) < ref[4] )state_on_Line = 2;
    if (state_on_Line == 2 && analog(3) < ref[3])state_on_Line = 0;
    switch (state_on_Line) {
      case 0: {
          present_position = Position();
        } break;
      case 1: {
          present_position = 5.0;
        } break;
      case 2: {
          present_position = 60.0;
        } break;
    }
    setpoint = 100/2;
    errors = setpoint - present_position;
    integral = integral + errors ;
    derivative = (errors - previous_error) ;
    output = Kp * errors + Ki * integral + Kd * derivative;
    previous_error = errors;
    int speed_max = 65;//50
    int speed_motor_forword = speed_max + output;
    int speed_motor_backward = speed_max - output;
    if (speed_motor_forword > 90)speed_motor_forword = 90;//100
    if (speed_motor_forword < 0 )speed_motor_forword = 0;
    if (speed_motor_backward > 90)speed_motor_backward = 90;//100
    if (speed_motor_backward < 0 )speed_motor_backward = 0;
    if (Position() > 0) {
      motor(2, speed_motor_forword);
      motor(1, speed_motor_backward);
    }
    else {
      motor(2, speed_motor_backward);
      motor(1, speed_motor_forword);
    }
  }while(!((analog(0) < ref[0] && analog(1) < ref[1]) || (analog(3) < ref[3] && analog(4) < ref[4])));
  ao();
  //while ((analog(2) > ref[1]  && analog(9) > ref[8])||(analog(2) < ref[1]  && analog(9) > ref[8])||(analog(2) > ref[1]  && analog(9) < ref[8]));

}

void ssr(){
  delay(200);
  while(analog(3)>ref[3])
  sr(50);
  while(analog(2)>ref[2])
  sr(30);
  ao();
  fd(30);
  delay(100);
  ao();
  delay(200);
  }
void ssl(){
  delay(200);
  while(analog(0)>ref[0])
  sl(50);
  while(analog(1)>ref[1])
  sl(30);
  ao();
  fd(30);
  delay(100);
  ao();
  delay(200);
  }
 void s (){
  Run(); ao();
  }
void slong(){
  Run_Long(); ao();
}
void setup() {

OK();
slong();
ssl();
s();
ssl();
s();  ssr();  s();  ssl();  s();  ssl();  s();  ssr();  s();

}

void loop() {
//view(2);
/*s();
ssl();
s();
ssl();
s();
ssr();
s();
while(1){}*/

}
