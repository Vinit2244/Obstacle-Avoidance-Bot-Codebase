#include "headers.h"

Robo::Robo(int GRID_ROWS, int GRID_COLS, int GRID_SQUARE_SIDE_LEN, int START_X, int START_Y, int END_X, int END_Y, int ROBO_LEN, int ROBO_WIDTH, int TRIG1, int ECHO1, int ERROR1, int TRIG2, int ECHO2, int ERROR2, int TRIG3, int ECHO3, int ERROR3)
{
  grid_rows   = GRID_ROWS;
  grid_cols   = GRID_COLS;
  
  grid_square_side_len = GRID_SQUARE_SIDE_LEN;
  start_x = START_X;
  start_y = START_Y;

  end_x = END_X;
  end_y = END_Y;

  robo_len    = ROBO_LEN;
  robo_width  = ROBO_WIDTH;

  trig_pin1   = TRIG1;
  echo_pin1   = ECHO1;
  error1      = ERROR1;

  trig_pin2   = TRIG2;
  echo_pin2   = ECHO2;
  error2      = ERROR2;

  trig_pin3   = TRIG3;
  echo_pin3   = ECHO3;
  error3      = ERROR3;
}