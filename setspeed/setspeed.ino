#include "defs.h"

void setup() {
  for (int i = 0; i < 2; i++) 
  {
    pinMode(leftMotor[i], OUTPUT);
    pinMode(rightMotor[i], OUTPUT);
  }

  pinMode(left_trigger, OUTPUT);
  pinMode(right_trigger, OUTPUT);
  pinMode(center_trigger, OUTPUT);
  pinMode(left_echo, INPUT);
  pinMode(right_echo, INPUT);
  pinMode(center_echo, INPUT);

  Serial.begin(115200);

  wifi_mqtt_setup();  
}

void loop() {

  mqtt_loop();
  float left_distance = take_reading(left_trigger, left_echo);
  float center_distance = take_reading(center_trigger, center_echo);
  float right_distance = take_reading(right_trigger, right_echo);

  Serial.print("left distance: ");
  Serial.println(left_distance);
  Serial.print("right distance: ");
  Serial.println(right_distance);
  Serial.print("center distance: ");
  Serial.println(center_distance);

  // publish to thingspeak
  publish(left_distance, right_distance, center_distance);

  // actuation
  int l = 1;
  int c = 1;
  int r = 1;

  if (left_distance < danger)
  {
    l = 0;
  }

  if (center_distance < danger)
  {
    c = 0;
  }

  if (right_distance < danger)
  {
    r = 0;
  }

  int result = 4 * l + 2 * c + r;

  if (result == 0b000)
  {
    stop();
    status = STOP;
  }
  else if (result == 0b001)
  {
    go_right(HIGH_T);
    status = RIGHT;
  }
  else if (result == 0b010)
  {
    go_straight();
    status = FORWARD;
  }
  else if (result == 0b011)
  {
    go_right(LOW_T);
    status = RIGHT;
  }
  else if (result == 0b100)
  {
    go_left(HIGH_T);
    status = LEFT;
  }
  else if (result == 0b101)
  {
    // Prioritized right
    go_right(HIGH_T);
    status = RIGHT;
  }
  else if (result == 0b110)
  {
    go_left(LOW_T);
    status = LEFT;
  }
  else if (result == 0b111)
  {
    go_straight();
    status = FORWARD;
  }
}