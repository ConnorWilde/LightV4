#include <Adafruit_NeoPixel.h>
#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;
#define OUTPUT_READABLE_ACCELGYRO

//Batt Constants 
const int fullbatt = 168;
const int battthreshold = 152;
const int lowbatt = 150;

const int led = A2;
const int batt = A3;
const int photoresistor = A0; 
const int button = A1;
int count; 
int mode; 

Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL);

void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  pinMode(photoresistor, INPUT);

  Serial.begin(9600);
  pixels.begin(); 
  Serial.println("Starting");

   //
   #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
   #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
   #endif

   accelgyro.initialize();
  
}


void loop() {
  checkmenu();
  Serial.println(mode);
    switch (mode) {
      case 0:    //standby/off
        //Serial.println("0");
        getbattindicator();
        analogWrite(led,0);    
        break;
        
      case 1:    //Walking around mode
        //Serial.println("1");
        SetLed(0,255,0);
        analogWrite(led,2);
        break;
        
      case 2:    //climb
        //Serial.println("2");
        SetLed(0,0,255);
        analogWrite(led,35);
        break;
        
      case 3:    //meh
        //Serial.println("3");
        SetLed(255,255,255);
        analogWrite(led,100);
        break;
        
      case 4:    //descent
        //Serial.println("4");
        SetLed(175,35,255);
        analogWrite(led,255);
        break;
        
      case 5:    //auto
        //Serial.println("5");
        SetLed(0,235,175);
        autoset();
        break;
      }
    }
    /*else{
      if(battvolt < battthreshold && battvolt > lowbatt){  
        checkmenu();
        Serial.println("Low");
        switch (mode) {
          case 0:    //standby/off
            //Serial.println("0");
            getbattindicator();
            analogWrite(led,0);    
            break;
        
          case 1:    //Walking around mode
            //Serial.println("1");
            SetLed(0,255,0);
            analogWrite(led,2);
            break;

         case 2:    //climb
            //Serial.println("2");
            SetLed(0,0,255);
            analogWrite(led,35);
            break;
      }
      if(battvolt < lowbatt){  
        checkmenu();
        Serial.println("Dead");
        switch (mode) {
          case 0:    //standby/off
            //Serial.println("0");
            getbattindicator();
            analogWrite(led,0);    
            break;
        
          case 1:    //Walking around mode
            //Serial.println("1");
            SetLed(0,255,0);
            analogWrite(led,2);
            break;
            
          case 2:    //climb
            //Serial.println("2");
            SetLed(0,0,255);
            analogWrite(led,35);
            break;
          }
        }
       }
      }*/
//}



void checkmenu(){
  if((digitalRead(button) == HIGH)){
    count++;
    if(count >= 5000){
      mode++;
      Serial.println(mode);
      count = 0;
      if(mode > 5){
        mode = 0;
      }
      delay(1);
    }
  }
  
}




void SetLed(int r, int g, int b){
  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();
}  

void autoset(){
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  int offsetval1 = 1;
  int offsetval2 = 1;
  int accel = abs(ax)+abs(ay)+abs(az);
  accel = accel / offsetval1; 

  int gyro = abs(gx)+abs(gy)+abs(gz);
  gyro = gyro / offsetval2; 

  int light_out = gyro + accel + photoresistor; 
  analogWrite(led, light_out); 

  
  
}

void getbattindicator(){
  int battvolt = ((analogRead(batt)*0.359)-1.5605);


  
  if(battvolt < battthreshold){
    SetLed(255,0,0);  
  }
  else{
    int setpoint = (battvolt + battthreshold) / 2; 
    if(battvolt > setpoint){
      //green mapping
      int g = ((15.9375*battvolt)-2429.5833);
      int r = ((-15.9375*battvolt)+2670.5833);
      //Serial.print(g); Serial.print(r); 
      SetLed(r,g,0);
    }
    
  }
}
