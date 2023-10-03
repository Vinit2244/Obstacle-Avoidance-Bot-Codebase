#pragma once

#include "headers.h"

class Ultrasonic {
  private:
  uint trig_pin;
  uint echo_pin;
  uint speed_of_sound;

  public:
  float distance; // in cms
  uint time;      // time in microseconds received from ultrasonic sensor
  int error;     // error in reading (set while calibrating) in cm

  // constructor
  Ultrasonic();
  void Setup(uint TRIG_PIN, uint ECHO_PIN, int ERROR);
  float take_reading();
};