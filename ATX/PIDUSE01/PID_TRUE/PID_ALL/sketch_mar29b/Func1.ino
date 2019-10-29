void pid(float kp,float kd,int bs){
  position = qtra.readLine(sensorValues);
 error = map(position,0,5000,100,-100);
 power_motor = (error *kp ) + ((error - last_error)*kd);
 last_error = error;
 leftMotorSpeed = bs + power_motor;
 rightMotorSpeed =bs - power_motor;
 if (leftMotorSpeed <= -100){
  leftMotorSpeed = -100;
  }
  if (leftMotorSpeed >= 100){
  leftMotorSpeed = 100;
  }
   if (rightMotorSpeed <= -100){
  leftMotorSpeed = -100;
  }
   if (rightMotorSpeed >= 100){
  leftMotorSpeed = 100;
  }
  motor(1,leftMotorSpeed);
  motor(2,rightMotorSpeed);
}
void pidT(float kp,float kd,int bs,int times){
  long A=millis();
  while((millis()-A)<times)
  {
    pid(kp,kd,bs);
  }
}
void pidS70(float kp,float kd,int bs){
 position = qtra.readLine(sensorValues);
 error = map(position,0,5000,100,-100);
 power_motor = (error *kp ) + ((error - last_error)*kd);
 last_error = error;
 leftMotorSpeed = bs + power_motor;
 rightMotorSpeed =bs - power_motor;
  if (leftMotorSpeed <= -80){
  leftMotorSpeed = -80;
  }
  if (leftMotorSpeed >= 80){
  leftMotorSpeed = 80;
  }
   if (rightMotorSpeed <= -80){
  leftMotorSpeed = -80;
  }
   if (rightMotorSpeed >= 80){
  leftMotorSpeed = 80;
  }
  if(position<5)
  {
  motor(1,40);
  motor(2,-35);
  while(position<500)
  {
    position=qtra.readLine(sensorValues);
  }
}
if(position>4995)
{
  motor(1,-35);
  motor(2,40);
  while(position>4500)
  {
    position=qtra.readLine(sensorValues);
  }
}
  motor(1,leftMotorSpeed);
  motor(2,rightMotorSpeed);
}
void pidS90(float kp,float kd,int bs){
 position = qtra.readLine(sensorValues);
 error = map(position,0,5000,100,-100);
 power_motor = (error *kp ) + ((error - last_error)*kd);
 last_error = error;
 leftMotorSpeed = bs + power_motor;
 rightMotorSpeed =bs - power_motor;
  if (leftMotorSpeed <= -80){
  leftMotorSpeed = -80;
  }
  if (leftMotorSpeed >= 80){
  leftMotorSpeed = 80;
  }
   if (rightMotorSpeed <= -80){
  leftMotorSpeed = -80;
  }
   if (rightMotorSpeed >= 80){
  leftMotorSpeed = 80;
  }
  if(position<5)
  {
  motor(2,40);
  motor(1,-30);
  while(position<500)
  {
    position=qtra.readLine(sensorValues);
  }
}
if(position>4995)
{
  motor(1,-30);
  motor(2,40);
  while(position>4500)
  {
    position=qtra.readLine(sensorValues);
  }
}

  motor(1,leftMotorSpeed);
  motor(2,rightMotorSpeed);
}
void pidS(float kp,float kd,int bs){
 position = qtra.readLine(sensorValues);
 error = map(position,0,5000,100,-100);
 power_motor = (error *kp ) + ((error - last_error)*kd);
 last_error = error;
 leftMotorSpeed = bs + power_motor;
 rightMotorSpeed =bs - power_motor;
      if (leftMotorSpeed <= -100){
  leftMotorSpeed = -100;
  }
  if (leftMotorSpeed >= 100){
  leftMotorSpeed = 100;
  }
   if (rightMotorSpeed <= -100){
  leftMotorSpeed = -100;
  }
   if (rightMotorSpeed >= 100){
  leftMotorSpeed = 100;
  }
  if(position<30)
  {
  motor(1,70);
  motor(2,0);
  while(position<500)
  {
    position=qtra.readLine(sensorValues);
  }
}
if(position>4970)
{
  motor(1,0);
  motor(2,70);
  while(position>4500)
  {
    position=qtra.readLine(sensorValues);
  }
}

  motor(1,leftMotorSpeed);
  motor(2,rightMotorSpeed);
}

void pidST(float kp,float kd,int bs,int times){
  long A=millis();
  while((millis()-A)<times)
  {
    pidS(kp,kd,bs);
  }
}
void pidST70(float kp,float kd,int bs,int times){
  long A=millis();
  while((millis()-A)<times)
  {
    pidS70(kp,kd,bs);
  }
}
void pidST90(float kp,float kd,int bs,int times){
  long A=millis();
  while((millis()-A)<times)
  {
    pidS90(kp,kd,bs);
  }
}
void pid_BB(float kp,float kd,int bs){
  while (1){
    pid(kp,kd,bs);
    if(sensorValues[5]>500)break;
  }
} 
void pidST_k(float kp,float kd,int bs,int times){  
  long A=millis();
  while((millis()-A)<times)
  {
     position = qtra.readLine(sensorValues);
 error = map(position,0,5000,100,-100);
if(error >95||error<-95) error = 0;
 power_motor = (error *kp ) + ((error - last_error)*kd);
 last_error = error;
 leftMotorSpeed = bs + power_motor;
 rightMotorSpeed =bs - power_motor;
  if (leftMotorSpeed <= -80){
  leftMotorSpeed = -80;
  }
  if (leftMotorSpeed >= 80){
  leftMotorSpeed = 80;
  }
   if (rightMotorSpeed <= -80){
  leftMotorSpeed = -80;
  }
   if (rightMotorSpeed >= 80){
  leftMotorSpeed = 80;
  }
  if(position<10)
  {
  motor(1,40);
  motor(2,-35);
  while(position<500)
  {
    position=qtra.readLine(sensorValues);
  }
}
if(position>4990)
{
  motor(1,-35);
  motor(2,40);
  while(position>4500)
  {
    position=qtra.readLine(sensorValues);
  }
}
//if(sensorValues[0]>500)break;
  motor(1,leftMotorSpeed);
  motor(2,rightMotorSpeed);
  }
}    

void square(int line,int sp,int fdd) {
  int  count = 0;
  while (true) {
    position = qtra.readLine(sensorValues);
    if (count >= line)break;
    if (analog(4) < 250) {
      fd(fdd); delay(50);
      ao(); delay(50); sl(50); delay(50);
      sl(30);
      while (true) {
        position = qtra.readLine(sensorValues);
        if (sensorValues[5] > 300) {
          sr(80); delay(15); ao(); delay(50);
          pidT(0.4, 2, 20, 200); count++;
          break;
        }
      }
    }
    else if (analog(5) < 250) {
      fd(fdd); delay(50);
      ao(); delay(50); sr(50); delay(50);
      sr(30);
      while (true) {
        position = qtra.readLine(sensorValues);
        if (sensorValues[0] > 500) {
          sl(80); delay(15); ao(); delay(50);
          pidT(0.4, 2, 20, 200); count++;
          break;
        }
      }
    }
    else if (sensorValues[1] > 500) {//¢ÇÒà¨Í´Ó
      motor(1, 30); motor(2, 15);
    }
    else if (sensorValues[4] > 500) {//«éÒÂà¨Í´Ó
      motor(1, 15); motor(2, 30);
    }
    else {
      fd(sp);
    }
  }
}
void square_stop(int line,int sp) {
  int  count = 0;
  while (true) {
    position = qtra.readLine(sensorValues);
    if (count >= line)break;
    if (analog(4) < 250) {
      ao(); delay(50);
    }
    else if (analog(5) < 250) {
      ao(); delay(50); 
    }
    else if (sensorValues[1] > 500) {//¢ÇÒà¨Í´Ó
      motor(1, 30); motor(2, 15);
    }
    else if (sensorValues[4] > 500) {//«éÒÂà¨Í´Ó
      motor(1, 15); motor(2, 30);
    }
    else {
      fd(sp);
    }
  }
}
void exit_white(int times){
  long A=millis();
  while((millis()-A)<times)
  {
    if (sensorValues[1] > 500) {//¢ÇÒà¨Í´Ó
      motor(1, 30); motor(2, 15);
    }
    else if (sensorValues[4] > 500) {//«éÒÂà¨Í´Ó
      motor(1, 15); motor(2, 30);
    }
    else {
      fd(30);
    }
  }
}
void squareSP(int line) {
  while (true) {
    position = qtra.readLine(sensorValues);
    if (analog(4) < 250) {
       pidT(0.4, 2, 30,  line*200);
       break;
    }
    else if (analog(5) < 250) {
       pidT(0.4, 2, 30,  line*200);
       break;
    }
    else if (sensorValues[1] > 500) {//¢ÇÒà¨Í´Ó
      motor(1, 30); motor(2, 15);
    }
    else if (sensorValues[4] > 500) {//«éÒÂà¨Í´Ó
      motor(1, 15); motor(2, 30);
    }
    else {
      fd(30);
    }
  }
}
