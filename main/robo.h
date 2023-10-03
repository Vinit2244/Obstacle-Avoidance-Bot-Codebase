#pragma once
#include "headers.h"

class Robo {
  public:
  int robo_len;
  int robo_width;

  int start_x;
  int start_y;
  int end_x;
  int end_y;

  int grid_rows;
  int grid_cols;
  int grid_square_side_len;

  int trig_pin1;
  int echo_pin1;
  int error1;

  int trig_pin2;
  int echo_pin2;
  int error2;

  int trig_pin3;
  int echo_pin3;
  int error3;

  // objects
  Ultrasonic Left;
  Ultrasonic Right;
  Ultrasonic Forward;
  Grid grid;
  Gyroscope gyro;
  Motors motors;

  int curX;
  int curY;
  int curOrientation; // 0 along +Y, 1 along +X, 2 along -Y, 3 along -X

  float repulsiveForceConst;
  float attractiveForceConst;

  // constructor
  Robo();
  void Setup(int GRID_ROWS, int GRID_COLS, int GRID_SQUARE_SIDE_LEN, int START_X, int START_Y, int END_X, int END_Y, int ROBO_LEN, int ROBO_WIDTH, int TRIG1, int ECHO1, int ERROR1, int TRIG2, int ECHO2, int ERROR2, int TRIG3, int ECHO3, int ERROR3, int LEFTMOTOR1, int LEFTMOTOR2, int RIGHTMOTOR1, int RIGHTMOTOR2, int SCL, int SDA, int gyro_errors[6]);

  void setObstacleCells();
  pair<double, double> GetNetForce();
  void Rotate(int angleToRotate);
  void MoveOneCellForward();
  void Move(pair<int, int> nextCell);
  void Confused();
  void Victory();
  void Algorithm();

};