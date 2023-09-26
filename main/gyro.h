#pragma once

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
  Gyroscope(int SCL_pin, int SDA_pin int errors[6]);
  void Setup();
  void getReading(int *accelerationXYZ, int *angularVelXYZ);
}