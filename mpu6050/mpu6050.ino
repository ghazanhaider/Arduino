// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
const int MPU2_addr=0x69;

int16_t ax,ay,az,bx,by,bz,count; //Tmp,GyX,GyY,GyZ,count;
void setup(){
  Wire.begin();
  Wire.setClock(400000);

// MPU 1  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0x0B);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1A);  // CONFIG register
  Wire.write(0x01);     // DLPF_CFG LPF set to 184Hz
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1C);  // ACCEL_CONFIG reg
  Wire.write(0x18);     // AFS_SEL set to 16g
  Wire.endTransmission(true);

// MPU 2
  Wire.beginTransmission(MPU2_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0x0B);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU2_addr);
  Wire.write(0x1A);  // CONFIG register
  Wire.write(0x01);     // DLPF_CFG LPF set to 184Hz
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU2_addr);
  Wire.write(0x1C);  // ACCEL_CONFIG reg
  Wire.write(0x18);     // AFS_SEL set to 16g
  Wire.endTransmission(true);
  
  Serial.begin(115200);
  count=0;
}

void loop(){

// MPU 1  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,6,true);  // request a total of 14 registers
  ax=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  ay=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  az=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

// MPU 2
  Wire.beginTransmission(MPU2_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU2_addr,6,true);  // request a total of 14 registers
  bx=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  by=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  bz=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  Serial.print("ax:");  Serial.print(ax);
  Serial.print(",ay:"); Serial.print(ay);
  Serial.print(",az:"); Serial.print(az);
  Serial.print(",bx:"); Serial.print(bx);
  Serial.print(",by:"); Serial.print(by);
  Serial.print(",bz:"); Serial.println(bz);
  //delay(3);
} 
