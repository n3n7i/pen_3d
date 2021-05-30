
//#include <Arduino.h>

#ifndef __n3n_mathFun_h__
#define __n3n_mathFun_h__

typedef struct sample_f{
  float x;
  float y;
  float z;
  };

void dispVec(sample_f a, char Cap[]){
  Serial.print(a.x); Serial.print(" ");
  Serial.print(a.y); Serial.print(" ");
  Serial.print(a.z); Serial.print(" ");
  Serial.print(Cap);
}


class mathLib{

  public:

    mathLib(){};

    sample_f deltaVec(sample_f accel, float sec);  //a*r
    //sample_f deltaPos(sample_f vel, float sec);

    sample_f addVec(sample_f a,  sample_f b); // a+b
    sample_f subVec(sample_f a,  sample_f b); // a-b
    sample_f multVec(sample_f a, sample_f b); // a.*b

    float sumVec(sample_f a); //a.x+a.y+a.z
    sample_f newVec(float x, float y, float z);

    sample_f smoothVec(sample_f a, sample_f b, float xrate); //a+(b-a)*r
    sample_f scaledAdd(sample_f a, sample_f b, float xrate); //(a+b)*r
    sample_f addScaled(sample_f a, sample_f b, float xrate); //a+(b*r)

    sample_f minVec(sample_f a, sample_f b);
    sample_f maxVec(sample_f a, sample_f b);
    //sample_f scaleVec(sample_f a, float b);

    sample_f rotateX(float x, float y, float r);
    sample_f rotateXYZ(sample_f vec, sample_f r3);
//*/

    };
    

sample_f mathLib::deltaVec(sample_f accel, float sec){
  return (sample_f) {accel.x * sec, accel.y * sec, accel.z * sec};
  }

/*sample_f mathLib::deltaPos(sample_f vel, float sec){
  return (sample_f) {vel.x * sec, vel.y * sec, vel.z * sec};
  }*/

sample_f mathLib::addVec(sample_f a, sample_f b){
  return (sample_f) {a.x + b.x, a.y + b.y, a.z + b.z};
  }

sample_f mathLib::subVec(sample_f a, sample_f b){
  return (sample_f) {a.x - b.x, a.y - b.y, a.z - b.z};
  }

sample_f mathLib::multVec(sample_f a, sample_f b){
  return (sample_f) {a.x * b.x, a.y * b.y, a.z * b.z};
  }

float mathLib::sumVec(sample_f a){
  return a.x + a.y + a.z;
  }

sample_f mathLib::newVec(float x, float y, float z){
  return (sample_f) {x, y, z};
  }

 
sample_f mathLib::smoothVec(sample_f a, sample_f b, float xrate){
  return addVec(a, deltaVec(subVec(b, a), xrate)); 
  }

sample_f mathLib::scaledAdd(sample_f a, sample_f b, float xrate){
  return deltaVec(addVec(a, b), xrate);
  }

sample_f mathLib::addScaled(sample_f a, sample_f b, float xrate){
  return addVec(a, deltaVec(b, xrate));
  }

sample_f mathLib::minVec(sample_f a, sample_f b){
  float x,y,z;
  x=a.x; y= a.y; z = a.z;
  if(b.x<x) x = b.x;
  if(b.y<y) y = b.y;
  if(b.z<z) z = b.z;
  return newVec(x,y,z);
}

sample_f mathLib::maxVec(sample_f a, sample_f b){
  return subVec(addVec(a,b), minVec(a,b));
  }

sample_f mathLib::rotateX(float x, float y, float r){
  float s = sin(r), c = cos(r);
  return newVec(y*s + x*c, -x*s + y*c, 0.0);
  }

sample_f mathLib::rotateXYZ(sample_f vec, sample_f r3){

  sample_f vec1 = rotateX(vec.x, vec.y, r3.z); //yaw
  vec1.z = vec.z;
  
  sample_f vec2 = rotateX(vec1.y, vec1.z, r3.x); //pitch
  vec2.z = vec2.y; vec2.y = vec2.x; vec2.x = vec1.x; //vec2.y = vec2.x;
  
  sample_f vec3 = rotateX(vec2.z, vec2.x, r3.y); //roll
  vec3.z = vec3.x; vec3.x = vec3.y; vec3.y = vec2.y;

  return vec3;
}
/*sample_f mathLib::deltaPos(sample_f accel, float sec);
sample_f mathLib::addVec(sample_f a, smaple b);
sample_f mathLib::subVec(sample_f a, smaple b);
sample_f mathLib::scaleVec(sample_f a, float b);*/

#endif
