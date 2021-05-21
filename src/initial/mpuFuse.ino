
// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain

//#include "wirePlus.h"

#include<Arduino.h>
#include "libFuse.h"

//#include<Wire.h>

const int MPU_addr=0x69;  // I2C address of the MPU-6050
const int MPU_addrB=0x68;

/*
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; // declare accellerometer and gyro variables

int16_t AcX2,AcY2,AcZ2,GyX2,GyY2,GyZ2;

float AcX3,AcY3,AcZ3,GyX3,GyY3,GyZ3;

float aScale, gScale;

float aScale_rel, gScale_rel;

float cS = 1.0;

int16_t stepC =0;

byte icBuffer[20], icBuffer2[20], icBuffer3[10];

*/

IMU mpuA(0x69);
IMU mpuB(0x68);

/*
int regRead(byte M_addr, int regaddr){
  Wire.beginTransmission(M_addr); // get ready to talk to MPU again
  Wire.write(regaddr);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false); // done talking to MPU for the time being
  Wire.requestFrom(M_addr,1,true);
  int byteL = 0;
  byteL = Wire.read();
  Wire.endTransmission(true);    
  return(byteL);
  }

void regWrite(byte M_addr, int regaddr, int regbyte){
  Wire.beginTransmission(M_addr); // be sure we talk to our MPU vs some other device  
  Wire.write(regaddr);  // PWR_MGMT_1 register
  Wire.write(regbyte);     // set to zero (wakes up the MPU-6050), three + gyro Z clock
  Wire.endTransmission(true);    
}

*/

/*

void setup_Mpu(byte M_addr){

  //Wire.beginTransmission(M_addr); // be sure we talk to our MPU vs some other device    
//  Wire.write(0x6B);  // PWR_MGMT_1 register
//  Wire.write(0x00);     // set to zero (wakes up the MPU-6050), three + gyro Z clock
//  Wire.endTransmission(true);  

  regWrite(M_addr, 0x6B, 0);

  delay(25);

 int whomi = regRead(M_addr, 0x75);

  regWrite(M_addr, 0x1C, 0x03<<3); // xl: +-16g // 2048lsb/g
  regWrite(M_addr, 0x1B, 0x03<<3); // gyro: +-2000deg // 16.4lsb/deg
  regWrite(M_addr, 0x1A, 0x02);    // lowpass: 20Hz (0x04)
  regWrite(M_addr, 0x19, 0x20);    // sampdiv 1000/32
  
  regWrite(M_addr, 0x23, 0x78); // xyzg fifo
  regWrite(M_addr, 0x6A, 0x40); // fifo en

  delay(25);

  regWrite(M_addr, 0x6B, 0x02);

  Serial.print("whomi: ");
  Serial.println(whomi);

}
*/

  //Wire.beginTransmission(MPU_addr);
/*  Wire.write(0x19); // 27-36khz / sample rate -1 
  Wire.write(0xFF); // ~500Hz
  
  Wire.write(0x1A); // low pass config
  Wire.write(0x01); // ~90Hz
  
  Wire.write(0x1B); // gyro config
  Wire.write(0x02<<3); // 500 deg/sec
//*/  
  //Wire.write(0x1C); // accel config
  //Wire.write(0x03<<3); // +- 4g

  //Wire.endTransmission(true);  
  
  //Wire.write(0x6B);  // PWR_MGMT_1 register
  //Wire.write(0x03);     // set to zero (wakes up the MPU-6050), three + gyro Z clock

/**/
  
  //Wire.endTransmission(true); // done talking over to MPU device, for the moment

void setup(){
  Wire.begin(); // initiate i2c system

  delay(50);
  Serial.begin(57600); // initialize serial port to 9600 bps so you can see your debug messages in Arduino IDE via debug channel
  delay(50);

  //setup_Mpu(MPU_addr);
  
  //setup_Mpu(MPU_addrB);

  mpuA.setup_IMU();
  mpuB.setup_IMU();

  //Serial.print("whomi: ");
  //Serial.println(whomi, HEX);
/*
  gScale = 16.4;
  aScale = 2048.0; 

  gScale_rel = 1.0/15.0;
  aScale_rel = 980.0/10.0; 
*/

  //regWrite(0x6A, 0x40); // fifo en
}

int fico = 0;//regRead(0x75);

//int ififo = 0;

void loop(){ // main program loop
  //Wire.beginTransmission(MPU_addr); // get ready to talk to MPU again
  //Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)

  mpuA.fifo_Data();
  mpuB.fifo_Data();

  short xDiff;
  short val1, val2;

  for(int i=0; i<6; i+=1){

    //xDiff = (mpuA.readData[i]<<8 | mpuA.readData[i+1]) - (mpuB.readData[i]<<8 | mpuB.readData[i+1]);

    //val1 = mpuA.readData[i]<<8|mpuA.readData[i+1];
    //val2 = mpuB.readData[i]<<8|mpuB.readData[i+1];

    //xDiff = abs(val1 - val2);

    xDiff = abs(mpuA.xreadData[i] - mpuB.xreadData[i]);
    /*Serial.print(mpuA.readData[i]<<8|mpuA.readData[i+1],HEX);
    Serial.print(" ");
    Serial.print(mpuB.readData[i]<<8 | mpuB.readData[i+1],HEX);
    Serial.print(" x");
    Serial.print(xDiff);
    Serial.print(" ");*/
    Serial.print(val1);
    Serial.print(" ");
    Serial.print(val2);
    Serial.print(" ");
    Serial.print(xDiff);
    Serial.print("| ");
    }
  Serial.println("");

  delay(50);
  }
/*  Wire.beginTransmission(MPU_addr); // get ready to talk to MPU again
  Wire.write(0x72); // from fifo counter
  Wire.endTransmission(false); // done talking to MPU for the time being
  Wire.requestFrom(MPU_addr,2,true);  // request a total of 14 registers

*/

  //regRequest(MPU_addr, 0x72, 2);
  //ififo = Wire.read()<<8 | Wire.read();
  //Wire.endTransmission(true);

  //Serial.print("ififo=");
  //Serial.print(ififo);
  

  /*if(ififo >= 12){
  
  Wire.beginTransmission(MPU_addr);
  ///

  
  Wire.write(0x74); // from fifo
  Wire.endTransmission(false); // done talking to MPU for the time being
  Wire.requestFrom(MPU_addr,12,true);  // request a total of 14 registers
  // all the fancy <<8| stuff is to bit shift the first 8 bits to
  // the left & combine it with the next 8 bits to form 16 bits
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  //Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  // the above lines have gathered Accellerometer values for X, Y, Z
  //  as well as Gyroscope values for X, Y, Z

  Wire.endTransmission(true);

*/
 /*
  AcX2= (AcX + AcX2*(cS-1)) / cS;
  AcY2= (AcY + AcY2*(cS-1)) / cS;
  AcZ2= (AcZ + AcZ2*(cS-1)) / cS;

  GyX2= (GyX + GyX2*(cS-1)) / cS;
  GyY2= (GyY + GyY2*(cS-1)) / cS;
  GyZ2= (GyZ + GyZ2*(cS-1)) / cS;
  */

/*
  AcX3= (AcX3 + AcX2/aScale);
  AcY3= (AcY3 + AcY2/aScale);
  AcZ3= (AcZ3 + (AcZ2/aScale +0.2));

  GyX3= (GyX3 + (GyX2/gScale + 2.24)/360.0);
  GyY3= (GyY3 + (GyY2/gScale - 0.97)/360.0);
  GyZ3= (GyZ3 + (GyZ2/gScale + 0.81)/360.0);

  stepC++;

  if((stepC % 1)==0){

  fico = regRead(MPU_addr, 0x72)<<8;

  fico |= regRead(MPU_addr, 0x73);

  //Serial.print(" fifo: "); Serial.print(fico);
  
  Serial.print("AcX = "); Serial.print((AcX2 / aScale) * aScale_rel ); // share accellerometer values over debug channel 
  Serial.print(",AcY = "); Serial.print((AcY2 / aScale) * aScale_rel);
  Serial.print(",AcZ = "); Serial.print((AcZ2 / aScale + 0.2) * aScale_rel);
  //Serial.print(", Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet

  
  
  Serial.print(", GyX = "); Serial.print((GyX2 / gScale + 2.24) * gScale_rel); // share gyroscope values over debug channel
  Serial.print(", GyY = "); Serial.print((GyY2 / gScale - 0.96) * gScale_rel);
  Serial.print(", GyZ = "); Serial.println((GyZ2 / gScale + 0.8 ) * gScale_rel);
// */
  /*Serial.print("Step: "); Serial.print(stepC);
  Serial.print("AcX2 = "); Serial.print(AcX3 / stepC); // share accellerometer values over debug channel 
  Serial.print(" | AcY = "); Serial.print(AcY3 / stepC);
  Serial.print(" | AcZ = "); Serial.print(AcZ3 / stepC);
  //Serial.print(" | Tmp = "); Serial.print(Tmp);  ///340.00+36.53equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX3);// /stepC); // share gyroscope values over debug channel
  Serial.print(" | GyY = "); Serial.print(GyY3);// /stepC);
  Serial.print(" | GyZ = "); Serial.println(GyZ3);// /stepC);

  }}
*/


/*
  delay(25); // delay a bit to not overwhelm you the user/programmer as you view the results
}
*/
