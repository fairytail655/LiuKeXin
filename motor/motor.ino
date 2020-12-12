#include <Kalman.h>
#include <Wire.h>
#include <Math.h>
#include <MsTimer2.h>

#define TIMEOUT 500

#define SPEED_FORWARD 65
#define SPEED_LEFT    70
#define SPEED_RIGHT   70

#define CHECK_COUNT   3

#define MODE_FORWARD  3
#define MODE_LEFT     1
#define MODE_RIGHT    2
#define MODE_STOP     0

#define STOP_COUNT    50

unsigned int pl,dl,b,pr,dr;
unsigned int ll,l,r,rr;
int d=3;
int s;

int a=0;
int bb=0;

//unsigned long lastTime;
//double Inputl, Outputl, Setpointl,Inputr, Outputr, Setpointr;
//double errSum, lastErr;
//double kpl,kil,kdl,kpr,kir,kdr;
//PID lPID(&Inputl, &Outputl, &Setpointl, kpl,kil,kdl, REVERSE);
//PID rPID(&Inputr, &Outputr, &Setpointr, kpr,kir,kdr, REVERSE);


void flash()              
{                        
  Serial.print(a);
  a=0;
}

void setup() {
  // put your setup code here, to run once:
  pl=10,dl=9,b=8,pr=11,dr=12;
  pinMode(pl,OUTPUT);
  pinMode(dl,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(pr,OUTPUT);
  pinMode(dr,OUTPUT);
  digitalWrite(b,1);
  ll=4,l=5,r=6,rr=7;
  pinMode(ll,INPUT_PULLUP);
  pinMode(l,INPUT_PULLUP);
  pinMode(r,INPUT_PULLUP);
  pinMode(rr,INPUT_PULLUP);
  Serial.begin(9600); //初始化串口，指定波特率
//  MsTimer2::set(500, flash);
//  MsTimer2::start();
//  attachInterrupt(0, blink, CHANGE);
//  attachInterrupt(1, blink2, CHANGE);
//    time = micros(); //时间初值
//    PIDl.SetTunings(kpl,kil,kdl);
//    PIDl.SetOutputLimits(-255,255);
//    PIDl.SetSampleTime(5);
//    PIDl.SetMode(AUTOMATIC);
//    PIDr.SetTunings(kpr,kir,kdr);
//    PIDr.SetOutputLimits(-255,255);
//    PIDr.SetSampleTime(5);
//    PIDr.SetMode(AUTOMATIC);
}

void blink()//中断函数
{
  a+=1;
}

void blink2()
{
  bb+=1;
}

void FORWARD()
{
   digitalWrite(b, 0);
   digitalWrite(dl, HIGH);
   analogWrite(pl,SPEED_FORWARD-8);
   digitalWrite(dr, LOW);
   analogWrite(pr,SPEED_FORWARD+5);
}

void LEFT()
{
   digitalWrite(b, LOW);
   digitalWrite(dl, LOW);
   analogWrite(pl,SPEED_LEFT);
   digitalWrite(dr, LOW);
   analogWrite(pr,SPEED_LEFT);
}

void RIGHT()
{
   digitalWrite(b, LOW);
   digitalWrite(dl, HIGH)  ;
   analogWrite(pl, SPEED_RIGHT);
   digitalWrite(dr, HIGH);
   analogWrite(pr,SPEED_RIGHT);
}

void REST()
{
  digitalWrite(b, 1);
}

void motor_control(int mode)
{
  switch (mode)
  {
    case MODE_FORWARD:
      FORWARD();
      break;
    case MODE_LEFT:
      LEFT();
      break;
    case MODE_RIGHT:
      RIGHT();
      break;
    case MODE_STOP:
      REST();
      break;
    default:
      REST();
      break;
  }
}

unsigned int beforetime=0;
int motor_mode = MODE_STOP;
char last_t = '0';
int l_val=0, ll_val=0, r_val=0, rr_val=0;
int turn_count = 0;
char forward_flag = 0;
char t = 0;
int stop_count = 0;

void loop() {
  stop_count++;
  while(Serial.available()>0)
  {
      t = Serial.read();
      if (t == '1' && last_t != '1')
        motor_mode = MODE_LEFT;
      else if(t == '2' && last_t != '2')
        motor_mode = MODE_RIGHT;
      else if(t == '3' && last_t == '0')
      {
        if (forward_flag == 0)
        {
          motor_mode = MODE_FORWARD;
          forward_flag = 1;
        }
        else
        {
          motor_mode = MODE_STOP;
          forward_flag = 0;
        }
      }
      else if ((last_t == '1' && t != '1') ||
               (last_t == '2' && t != '2'))
       {
        motor_mode = MODE_STOP;
        forward_flag = 0;
       }
      last_t = t;
      stop_count = 0;
    }
    
    if (stop_count >= STOP_COUNT)
    {
      motor_mode = MODE_STOP;
      stop_count = 0;
      forward_flag = 0;
      last_t = '0';
    }

    if (t != '1' && t != '2')
    {
      if(!digitalRead(r) || !digitalRead(l)) 
      {
          //Serial.println("stop");
          turn_count++;
      }
      else
      {
        turn_count = 0;
      }
      if (turn_count >= CHECK_COUNT)
      {
          turn_count = 0;
          motor_mode = MODE_STOP;
          forward_flag = 0;
          last_t = '0';
      }
    }

//    l_val = digitalRead(l);
//    r_val = digitalRead(r);
//    Serial.print(l_val);
//    Serial.print(' ');
//    Serial.println(r_val);
    
    motor_control(motor_mode);
    if (motor_mode == MODE_RIGHT || motor_mode == MODE_LEFT)
    {
      delay(1000);
      while(Serial.available()>0)
      {
          t = Serial.read();
      }
      motor_mode = MODE_STOP;
      forward_flag = 0;
      last_t = '0';
    }

    delay(50);
}
