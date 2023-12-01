#include "esp32-hal.h"
#include "headers.h"

Gyroscope::Gyroscope()
{
}

void Gyroscope::Setup(int SCL_pin, int SDA_pin)
{
  SCL = SCL_pin;
  SDA = SDA_pin;
  this->errors[0]= 0;
  this->errors[1]= 0;
  this->errors[2]= 0;
  this->errors[3]= 0;
  this->errors[4]= 0;
  this->errors[5]= 0;
  this->errors[6]= 0;

  /*Taken directly from examples*/
  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) 
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
      delay(10);
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  Serial.println(mpu.getAccelerometerRange());

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  Serial.println(mpu.getGyroRange());

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  Serial.println(mpu.getFilterBandwidth());

  // now take 5000 readings to set errors
  int count = 0;
  while(count++ < 2000)
  {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    errors[0] += g.gyro.x;
    errors[1] += g.gyro.y;
    errors[2] += g.gyro.z;
    errors[3] += a.acceleration.x;
    errors[4] += a.acceleration.y;
    errors[5] += a.acceleration.z;
    delayMicroseconds(100);
  }
  errors[0] /= 2000;
  errors[1] /= 2000;
  errors[2] /= 2000;
  errors[3] /= 2000;
  errors[4] /= 2000;
  errors[5] /= 2000;
  Serial.println("gyro setup");
}

void Gyroscope::getAngularReading(double *angularVelXYZ)
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  angularVelXYZ[0] = g.gyro.x - errors[0];
  angularVelXYZ[1] = g.gyro.y - errors[1];
  angularVelXYZ[2] = g.gyro.z - errors[2];
}

void Gyroscope::getLinearReading(double *accelerationXYZ)
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  accelerationXYZ[0] = a.acceleration.x - errors[3];
  accelerationXYZ[1] = a.acceleration.y - errors[4];
  accelerationXYZ[2] = a.acceleration.z - errors[5];
}