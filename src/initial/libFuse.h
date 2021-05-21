
#include "wirePlus.h"

#define libfuse_MAXvar 6
#define libfuse_MAXrD libfuse_MAXvar*2

class IMU{
  public:
    IMU(byte addr){ xAddr = addr;}
    byte xAddr;
    //byte readData[libfuse_MAXrD];
    short xreadData[libfuse_MAXvar];
    void setup_IMU();
    void fifo_Data();
    //void fifo_Data();
    };

void IMU::setup_IMU(){
  regWrite(xAddr, 0x6B, 0);
  delay(100);
  regWrite(xAddr, 0x1C, 0x03<<3); // xl: +-16g // 2048lsb/g
  regWrite(xAddr, 0x1B, 0x03<<3); // gyro: +-2000deg // 16.4lsb/deg
  regWrite(xAddr, 0x1A, 0x06);    // lowpass: 20Hz (0x04)?
  regWrite(xAddr, 0x19, 0x40);    // sampdiv 1000/32 (1khz/32)
  regWrite(xAddr, 0x23, 0x78); // xyzg fifo
  //regWrite(xAddr, 0x23, 0x00); // xyzg fifo disable
  regWrite(xAddr, 0x6A, 0x04); // fifo reset
  regWrite(xAddr, 0x6A, 0x40); // fifo en
  //delay(25);
  //regWrite(xAddr, 0x6B, 0x00); //def clock
  regWrite(xAddr, 0x38, 0x01); //data ready flag enable
  }


void IMU::fifo_Data(){
  regRequest(xAddr, 0x72, 2);
  int ififo = Wire.read()<<8 | Wire.read();
  Wire.endTransmission(true);
  if(ififo >= 12){
    regRequest(xAddr, 0x74, 12);
    int j=0;
    byte b1, b2;
    for(int i=0; i<12; i+=2){
      b1 = Wire.read(); b2 = Wire.read();
      xreadData[j] = b1<<8|b2;
      j++;
      }    
    Wire.endTransmission(true);
    }
  }
