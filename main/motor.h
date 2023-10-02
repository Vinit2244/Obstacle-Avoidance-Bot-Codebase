#pragma once

#include "headers.h"

class Motors
{
public:
  int leftMotor[2]; // = {4, 5};
  int rightMotor[2]; // = {12, 13};
  int maxSpeed; // = 300;

  Motors(int left1, int left2, int right1, int right2);

  void Setup();
  void setSpeed(int leftSpeed, int rightSpeed);
};