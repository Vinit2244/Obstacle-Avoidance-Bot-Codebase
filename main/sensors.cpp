#include "headers.h"

Ultrasonic::Ultrasonic(uint TRIG_PIN, uint ECHO_PIN, int ERROR)
{
  speed_of_sound = 35000; // cmps
  trig_pin = TRIG_PIN;
  echo_pin = ECHO_PIN;
  error = ERROR;
}

void Ultrasonic::Setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  distance = 0;
  time = 0;
}

float Ultrasonic::take_reading() { // waits for 10 microseconds
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  time = pulseIn(echo_pin, HIGH);
  distance = ((float) time / 1000000) * speed_of_sound; // in cms
  distance = distance - error;
  return distance;
}