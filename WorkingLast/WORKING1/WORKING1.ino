#include <AFMotor.h>

AF_DCMotor motor1(1), motor2(4);
int crit = 200;
int sensor0 = 0;
int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int sensor4 = 0;
int sensor5 = 0;
int sensor6 = 0;
int sensor7 = 0;
int sPeed=70;


//
float Kp =0;
float Kd =0;
float Ki =0;

//
int preverror = 0;
int error = 0;
int derror = 0;
int ierror = 0;

int U;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor1.setSpeed(sPeed);
  motor1.run(RELEASE);
  motor2.setSpeed(sPeed);
  motor2.run(RELEASE);
 
}

void loop() {
  
  senser();
  
  
  
  if( sensor0==1 || sensor7==1 )
  {
    Kp = 10000000;
    Kd = 0;
    Ki = 0;  
  }
  
  
  else if(sensor2==1 || sensor3==1 || sensor4==1 || sensor5==1 )
  {
    Kp = 50;
    Kd = 100;
    Ki = 0;
  }
  
  
  
  else
  {
    Kp = 100;
    Kd = 0;
    Ki = 0;
  } 
  
  error =  (-4*sensor0) + (-3*sensor1) + (-2*sensor2) + (-1*sensor3) + (1*sensor4) + (2*sensor5) + (3*sensor6) + (4*sensor7);
  derror = error - preverror;
  ierror += error; 
  U = Kp * error + Kd * derror + Ki * ierror;  
  preverror = error;
  
  

  
  
  if(U<-sPeed) U=-sPeed;
  if(U>sPeed) U=sPeed;
  
  
  Serial.print(U);
  //Serial.print('    ');
  Serial.println (sPeed+U);
  ///////////////////////////////////////
  
  
  if(U>0)
  {
    motor1.run(BACKWARD);
    motor1.setSpeed(sPeed);
  
    motor2.run(BACKWARD);
    motor2.setSpeed(sPeed-U);
  
  }
  else if(U<0)
  {
    motor1.run(BACKWARD);
    motor1.setSpeed(sPeed+U);
  
    motor2.run(BACKWARD);
    motor2.setSpeed(sPeed);
 
  }
  else if (error=0) 
  {
    motor1.run(BACKWARD);
    motor1.setSpeed(sPeed);
  
    motor2.run(BACKWARD);
    motor2.setSpeed(sPeed);
 
  }
  
}
  


void senser()
{
 
   sensor0 = analogRead(8);
   if ( sensor0>crit ) sensor0=1;
   else sensor0=0;
   Serial.print(sensor0);
   Serial.print(' ');
  
    
   sensor1 = analogRead(9);
   Serial.print(sensor1);
   Serial.print(' ');
   if ( sensor1>crit ) sensor1=1;
   else sensor1=0;
   
   
   
   sensor2 = analogRead(10);
   Serial.print(sensor2);
   Serial.print(' ');
   if ( sensor2>crit ) sensor2=1;
   else sensor2=0;
   
   
   sensor3 = analogRead(11);
   Serial.print(sensor3);
   Serial.print(' ');
   if ( sensor3>crit ) sensor3=1;
   else sensor3=0;
   
   
   sensor4 = analogRead(12);
   Serial.print(sensor4);
   Serial.print(' ');
   if ( sensor4>crit ) sensor4=1;
   else sensor4=0;
   
   
   sensor5 = analogRead(13);
   Serial.print(sensor5);
   Serial.print(' ');
   if ( sensor5>crit ) sensor5=1;
   else sensor5=0;

   sensor6 = analogRead(14);
   Serial.print(sensor6);
   Serial.print(' ');
   if ( sensor6>crit ) sensor6=1;
   else sensor6=0;
   
   sensor7 = analogRead(15);
   Serial.print(sensor7);
   Serial.println(' ');
   if ( sensor7>crit ) sensor7=1;
   else sensor7=0;
  
}
