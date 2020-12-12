//连线方法
//MPU-UNO
//VCC-VCC
//GND-GND
//SCL-A5
//SDA-A4

#include <Kalman.h>
#include <Wire.h>
#include <Math.h>
#include <I2Cdev.h>
#include "MPU6050.h"

#define MPUleftpin  7
#define MPUrightpin 8

float fRad2Deg = 57.295779513f; //将弧度转为角度的乘数
const int MPU = 0x68; //MPU-6050的I2C地址
const int nValCnt = 7; //一次读取寄存器的数量

const int nCalibTimes = 1000; //校准时读数的次数
int calibData[nValCnt]; //校准数据

unsigned long nLastTime = 0; //上一次读数的时间
float fLastRoll = 0.0f; //上一次滤波得到的Roll角
float fLastPitch = 0.0f; //上一次滤波得到的Pitch角
Kalman kalmanRoll; //Roll角滤波器
Kalman kalmanPitch; //Pitch角滤波器
MPU6050 accelgyro;

void setup(){
  Serial.begin(9600); //初始化串口，指定波特率
  pinMode(MPUleftpin,OUTPUT);
  pinMode(MPUrightpin,OUTPUT);
  digitalWrite(MPUleftpin,LOW);
  digitalWrite(MPUrightpin,HIGH);
  Wire.begin(); //初始化Wire库

  nLastTime = micros(); //记录当前时间
  accelgyro.initialize();
}

void loop(){
  int readouts[nValCnt];
  ReadAccGyr(readouts); //读出测量值
  Serial.println();
  delay(10);
}

//从MPU6050读出加速度计三个分量、温度和三个角速度计
//保存在指定的数组中
void ReadAccGyr(int *pVals) {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.requestFrom(MPU, nValCnt * 2, true);
  Wire.endTransmission(true);
  for (long i = 0; i < nValCnt; ++i) {
    pVals[i] = Wire.read() << 8 | Wire.read();
  }
  for (long i = 0; i < nValCnt; ++i) if(i!=3){
    Serial.print(pVals[i]);
    Serial.print(" ");
  }
}
