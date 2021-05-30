
#include "mathFun.h"

#define vecf3 sample_f

class IMU_Pcomp{
  public:
    IMU_Pcomp(){};
    mathLib ML;

    sample_f inp[3];

    sample_f inp_max[2];
    sample_f inp_min[2];
    sample_f inp_bias[2];

    float Gyro_xparam[2];
    sample_f Gyro_inp[3];
    sample_f Gyro_bias[3];
    boolean GyCal;

    sample_f xyz_Orient[3];
    sample_f xyz_Rot;
    sample_f xyz_Rlimits[2];
    sample_f xyz_AsG;
    sample_f xyz_AsO;
    sample_f xyz_AsV;
    
    sample_f r_accel[3];
    sample_f orient[3];
    sample_f posit[3];
    sample_f veloc[3];

    float G_mag[3];
    float G_scale[3];

    void setInp(vecf3 a, vecf3 b, vecf3 c);
    void setInp_G(vecf3 a, vecf3 b);
    void printObj(vecf3 data[]);
    void centerA();
    void G_magnitude();
    void Calib_Ac();
    void Gyro_Ac();
    void Gyro_Avg();
    void Gyro_param(float s1, float s2);

    void init_xyz();
    void update_xyz();
    void Est_AsubG();
    };


void IMU_Pcomp::setInp(vecf3 a, vecf3 b, vecf3 c){
  inp[0] = a; inp[1] = b; inp[2] = c;
  }

void IMU_Pcomp::setInp_G(vecf3 a, vecf3 b){
  Gyro_inp[0] = a; Gyro_inp[1] = b;
  }


void IMU_Pcomp::printObj(vecf3 data[]){
  dispVec(data[0], "");
  dispVec(data[1], "");
  dispVec(data[2], "\n");
  }

void IMU_Pcomp::centerA(){
  r_accel[2] = ML.scaledAdd(inp[0], inp[1], 0.5);
  r_accel[0] = ML.subVec(inp[0], r_accel[2]);
  r_accel[1] = ML.subVec(inp[1], r_accel[2]);
  }

void IMU_Pcomp::G_magnitude(){
  G_mag[0] = sqrt(ML.sumVec(ML.multVec(inp[0], inp[0])));
  G_mag[1] = sqrt(ML.sumVec(ML.multVec(inp[1], inp[1])));
  G_mag[2] = sqrt(ML.sumVec(ML.multVec(r_accel[2], r_accel[2])));

  for(int i=0; i<3; i++)
    G_scale[i] = G_mag[i] / 2048.0;    
  }

void IMU_Pcomp::Calib_Ac(){

  if(1750 < G_mag[2] && G_mag[2] < 2250){
  if(1500 < G_mag[0] && G_mag[0] < 2500){
    inp_min[0] = ML.minVec(inp[0], inp_min[0]);
    inp_max[0] = ML.maxVec(inp[0], inp_max[0]);
    inp_bias[0] = ML.smoothVec(inp_bias[0], ML.addVec(inp_min[0], inp_max[0]), 0.5);}
    
  if(1500 < G_mag[1] && G_mag[1] < 2500){
    inp_min[1] = ML.minVec(inp[1], inp_min[1]);
    inp_max[1] = ML.maxVec(inp[1], inp_max[1]);
    inp_bias[1] = ML.smoothVec(inp_bias[1], ML.addVec(inp_min[1], inp_max[1]), 0.5);
    }
  }
  }

void IMU_Pcomp::Gyro_param(float s1, float s2){
  Gyro_xparam[0] = s1;
  Gyro_xparam[1] = s2;
  GyCal = false;
  }

void IMU_Pcomp::Gyro_Ac(){
  Gyro_bias[0] = ML.smoothVec(Gyro_bias[0], Gyro_inp[0], Gyro_xparam[0]);
  Gyro_bias[1] = ML.smoothVec(Gyro_bias[1], Gyro_inp[1], Gyro_xparam[0]);
  Gyro_inp[2] = ML.scaledAdd(ML.subVec(Gyro_inp[0], Gyro_bias[0]), ML.subVec(Gyro_inp[1], Gyro_bias[1]), 0.5);
  Gyro_bias[2] = ML.smoothVec(Gyro_bias[2], Gyro_inp[2], Gyro_xparam[1]);  

  if(sqrt(ML.sumVec(ML.multVec(Gyro_bias[2], Gyro_bias[2]))) < 0.5){
    Gyro_param(0.0, 0.0);
    GyCal = true;
    }
  }

void IMU_Pcomp::Gyro_Avg(){
  Gyro_inp[2] = ML.scaledAdd(ML.subVec(Gyro_inp[0], Gyro_bias[0]), ML.subVec(Gyro_inp[1], Gyro_bias[1]), 0.5);
  }

void IMU_Pcomp::init_xyz(){
  xyz_Orient[0] = ML.newVec(1.0, 0.0, 0.0); // Right?
  xyz_Orient[1] = ML.newVec(0.0, 1.0, 0.0); // Ahead?
  xyz_Orient[2] = ML.newVec(0.0, 0.0, 1.0); // Above?

  xyz_Rot = ML.newVec(0.0, 0.0, 0.0);

  float halfPi = 3.14/2.0; // +-90 degrees
  
  xyz_Rlimits[0] = ML.newVec(-halfPi, -halfPi, -halfPi); // Above?
  xyz_Rlimits[1] = ML.newVec(halfPi, halfPi, halfPi);
}

void IMU_Pcomp::update_xyz(){
  sample_f delta_r = ML.deltaVec(Gyro_inp[2], (3.14/180.0)*(1.0/16.4)*(1.0/20.0));//ML.subVec(Gyro_inp[2], xyz_Rot);

  xyz_Rot = ML.addVec(xyz_Rot, delta_r);
  xyz_Rot = ML.maxVec(ML.minVec(xyz_Rot, xyz_Rlimits[1]), xyz_Rlimits[0]);

  xyz_Orient[0] = ML.rotateXYZ(xyz_Orient[0], delta_r);
  xyz_Orient[1] = ML.rotateXYZ(xyz_Orient[1], delta_r);
  xyz_Orient[2] = ML.rotateXYZ(xyz_Orient[2], delta_r);
}


void IMU_Pcomp::Est_AsubG(){

  xyz_AsG = ML.subVec(ML.deltaVec(r_accel[2], 1.0/2000.0), xyz_Orient[2]);

  xyz_AsO = ML.addVec(ML.addVec(ML.deltaVec(xyz_Orient[0], xyz_AsG.x), ML.deltaVec(xyz_Orient[1], xyz_AsG.y)),
                      ML.deltaVec(xyz_Orient[2], xyz_AsG.z));

  xyz_AsV = ML.addScaled(xyz_AsV, xyz_AsO, 0.5);
  
}

//dispVec(filter.xyz_Orient[2], " :|: ");
   // dispVec(filter.xyz_Rot, "\n");
