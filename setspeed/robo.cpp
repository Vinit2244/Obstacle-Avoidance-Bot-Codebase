#include "defs.h"

int status = 0;

int HIGH_T = 250; // in miliseconds
int LOW_T = 20; // in miliseconds

const int leftMotor[2] = { 4, 5 };
const int rightMotor[2] = { 13, 12 };
const int maxSpeed = 1000;

float danger = 30; // cms

void set_speed(int leftSpeed, int rightSpeed)
{
  int leftCheck = leftSpeed < 0;
  analogWrite(leftMotor[leftCheck], abs(leftSpeed));
  analogWrite(leftMotor[leftCheck ^ 1], 0);

  int rightCheck = rightSpeed < 0;
  analogWrite(rightMotor[rightCheck], abs(rightSpeed));
  analogWrite(rightMotor[rightCheck ^ 1], 0);
}

float take_reading(int trig_pin, int echo_pin)
{
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  int time = pulseIn(echo_pin, HIGH);
  float distance = ((float)time / 1000000) * speed_of_sound;  // in cms
  return (distance / 2);
}

void stop()
{
  if (status == STOP)
  {
    // do nothing
  }
  else
  {
    set_speed(0, 0);
  }
}

void go_left(int turn_time)
{
  if (status == LEFT)
  {
    // do nothing
  }
  else
  {
    set_speed(-maxSpeed, maxSpeed);
  }
  delay(turn_time);
}

void go_right(int turn_time)
{
  if (status == RIGHT)
  {
    // do nothing
  }
  else
  {
    set_speed(maxSpeed, -maxSpeed);
  }
  delay(turn_time);
}

void go_straight()
{
  if (status == FORWARD)
  {
    // do nothing
  }
  else
  {
    set_speed(maxSpeed, maxSpeed);
  }
}