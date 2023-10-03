#pragma once

#include "headers.h"

class Grid {
  public:
  int n_rows;
  int n_cols;
  int start_x;
  int start_y;
  int end_x;
  int end_y;

  int **Array;
  int **Visited;

  Grid();
  void init(int n_rows, int n_cols, int start_x, int start_y, int end_x, int end_y);
};