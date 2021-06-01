#include <TimerOne.h>
#include <SPI.h>
#include <SD.h>
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;




const int analog_ip = A0;
const int chipSelect = 4;

const int ambientpin = 1;

int inputVal = 0;
int light = 0;


int ambient;
int lightCal;
int lightVal;

int Mode = 2; //Street Mode


void setup() {
 // put your setup code here, to run once:
pinMode(9, OUTPUT);
Timer1.initialize(10); // Intialize timer1, and set a 100khz frequency
Serial.begin(9600);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
 while (!Serial);






}


void loop() {
  inputVal = analogRead(analog_ip);
  light = map(inputVal, 0, 680, 30, 1000);
    
  Timer1.pwm(9,light); // setup pwm on pin 9, with a 50% duty cycle
  delay(100);
  MPUget();


  ambient = analogRead(ambientpin);

  
  //Print All Values
  Serial.print(light);
  Serial.print(",");
  Serial.print(Mode);
  Serial.print(",");
  Serial.print(ambient);
  Serial.print(",");
    
  Serial.print(AcX);
  Serial.print(",");
  Serial.print(AcY);
  Serial.print(",");
  Serial.print(AcZ);
  Serial.print(",");
  Serial.print(GyX);
  Serial.print(",");
  Serial.print(GyY);
  Serial.print(",");
  Serial.print(GyZ);
  Serial.println();
  
  
  
  
  
  Wire.beginTransmission(9);
  Wire.write("test");              // sends x 
  Wire.endTransmission();
  

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  

  
}



void MPUget(){
    Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  delay(10);
}
