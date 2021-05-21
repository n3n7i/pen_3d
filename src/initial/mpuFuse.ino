
// based on MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain

//#include "wirePlus.h"

#include<Arduino.h>
#include "libFuse.h"

const int MPU_addr=0x69;  // I2C address of the MPU-6050
const int MPU_addrB=0x68;

IMU mpuA(0x69);
IMU mpuB(0x68);

void setup(){
  Wire.begin(); // initiate i2c system
  delay(50);
  Serial.begin(57600); // initialize serial port to 9600 bps so you can see your debug messages in Arduino IDE via debug channel
  delay(50);
  mpuA.setup_IMU();
  mpuB.setup_IMU();
  }

/* //param dependent
  gScale = 16.4;
  aScale = 2048.0; 
  gScale_rel = 1.0/15.0;
  aScale_rel = 980.0/10.0; 
*/


int fico = 0;//regRead(0x75);

//int ififo = 0;

void loop(){ // main program loop

  mpuA.fifo_Data();
  mpuB.fifo_Data();

  short xDiff;
  short val1, val2;

  for(int i=0; i<6; i+=1){

    xDiff = abs(mpuA.xreadData[i] - mpuB.xreadData[i]);

    /*Serial.print(val1);
    Serial.print(" ");
    Serial.print(val2);
    Serial.print(" ");
    */
    Serial.print(xDiff);
    Serial.print("| ");
    }
  Serial.println("");

  delay(50);
  }
