#include "gyro.h"

Gyroscope::Gyroscope(int SCL_pin, int SDA_pin int errors[6])
{
  SCL = SCL_pin;
  SDA = SDA_pin;
  errors[0]= errors[0];
  errors[1]= errors[1];
  errors[2]= errors[2];
  errors[3]= errors[3];
  errors[4]= errors[4];
  errors[5]= errors[5];
  errors[6]= errors[6];
}

void Gyroscope::Setup()
{
  /*Taken directly from examples*/
  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  Serial.println(mpu.getAccelerometerRange());

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  Serial.println(mpu.getGyroRange());

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  Serial.println(mpu.getFilterBandwidth());
}

void Gyroscope::getReading(int *accelerationXYZ, int *angularVelXYZ)
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  accelerationXYZ[0] = a.acceleration.x;
  accelerationXYZ[1] = a.acceleration.y;
  accelerationXYZ[2] = a.acceleration.z;

  angularVelXYZ[0] = g.gyro.x;
  angularVelXYZ[1] = g.gyro.y;
  angularVelXYZ[2] = g.gyro.z;
}