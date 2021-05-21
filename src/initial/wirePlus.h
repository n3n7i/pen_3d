
#include<Wire.h>

int regRead(byte M_addr, byte regaddr){
  Wire.beginTransmission(M_addr); // get ready to talk to MPU again
  Wire.write(regaddr);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false); // done talking to MPU for the time being
  Wire.requestFrom(M_addr,1,true);
  int byteL = 0;
  byteL = Wire.read();
  Wire.endTransmission(true);    
  return(byteL);
  }

void regWrite(byte M_addr, byte regaddr, byte regbyte){
  Wire.beginTransmission(M_addr); // be sure we talk to our MPU vs some other device  
  Wire.write(regaddr);  // PWR_MGMT_1 register
  Wire.write(regbyte);     // set to zero (wakes up the MPU-6050), three + gyro Z clock
  Wire.endTransmission(true);    
  }

void regRequest(byte M_addr, byte regaddr, byte regbytes){
  Wire.beginTransmission(M_addr); // get ready to talk to MPU again
  Wire.write(regaddr); // from fifo counter
  Wire.endTransmission(false); // done talking to MPU for the time being
  Wire.requestFrom(M_addr, regbytes, true);  // request a total of 14 registers
  }
