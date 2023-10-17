#pragma once

#include "headers.h"

class Gyroscope
{
private:
  int SCL;
  int SDA;
  int XCL;
  int XDA;
  int ADO;
  int INT;
  int errors[6];
  Adafruit_MPU6050 mpu;

public:
  Gyroscope();
  void Setup(int SCL_pin, int SDA_pin);
  void getAngularReading(double *angularVelXYZ);
  void getLinearReading(double *accelerationXYZ);
};