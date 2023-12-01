#include "headers.h"

Motors::Motors()
{
}

void Motors::Setup(int left1, int left2, int right1, int right2)
{
  leftMotor[0] = left1;
  leftMotor[1] = left2;

  rightMotor[0] = right1;
  rightMotor[1] = right2;

  maxSpeed = 1000; // voltage dependent

  for(int i = 0; i < 2; i++)
  {
    pinMode(leftMotor[i], OUTPUT);
    pinMode(rightMotor[i], OUTPUT);
  }
}

void Motors::setSpeed(int leftSpeed, int rightSpeed)
{
  int leftCheck = leftSpeed < 0;
  analogWrite(leftMotor[leftCheck], abs(leftSpeed));
  analogWrite(leftMotor[leftCheck ^ 1], 0);

  int rightCheck = rightSpeed < 0;
  analogWrite(rightMotor[rightCheck], abs(rightSpeed));
  analogWrite(rightMotor[rightCheck ^ 1], 0);
}