#pragma once

class Ultrasonic {
  public:
  float distance; // in cms
  uint time;      // time in microseconds received from ultrasonic sensor
  int error;     // error in reading (set while calibrating) in cm

  private:
  uint trig_pin;
  uint echo_pin;
  uint speed_of_sound;

  // constructor
  Ultrasonic(uint TRIG_PIN, uint ECHO_PIN, int ERROR);

  void Setup();
  float take_reading();
};