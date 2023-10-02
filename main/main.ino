#include "headers.h"
#include "defs.h"

Robo robot(_GRID_ROWS, _GRID_COLS, _GRID_SQUARE_SIDE_LEN, _START_X, _START_Y, _END_X, _END_Y, _ROBO_LEN, _ROBO_WIDTH, _TRIG1, _ECHO1, _ERROR1,
 _TRIG2, _ECHO2, _ERROR2, _TRIG3, _ECHO3, _ECHO3, _LEFTMOTOR1, _LEFTMOTOR2, _RIGHTMOTOR1, _RIGHTMOTOR2, _SCL, _SDA, gyro_errors);

void setup() {
  Serial.begin(115200);
  robot.Algorithm();
  robot.Victory();
}

void loop() {
}