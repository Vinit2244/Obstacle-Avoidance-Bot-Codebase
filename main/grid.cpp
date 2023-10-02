#include "headers.h"

Grid::Grid(int n_rows, int n_cols, int start_x, int start_y, int end_x, int end_y)
{
  this->n_rows = n_rows;
  this->n_cols = n_cols;
  this->start_x = start_x;
  this->start_y = start_y;
  this->end_x = end_x;
  this->end_y = end_y;

  Array = new int* [n_rows];
  for (int i = 0; i < n_rows; i++)
    Array[i] = new int [n_cols];
  
  Visited = new int* [n_rows];
  for (int i = 0; i < n_rows; i++)
    Visited[i] = new int [n_cols];

  for(int i = 0; i < n_rows; i++)
  {
    for(int j = 0; j < n_cols; j++)
    {
      Array[i][j] == 0;
      Visited[i][j] == 0;
    }
  }
}