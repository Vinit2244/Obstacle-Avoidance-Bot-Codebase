class Grid {
  public:
  int n_rows;
  int n_cols;
  int start_x;
  int start_y;
  int end_x;
  int end_y;

  // contructor function
  Grid(int n_rows, int n_cols, int start_x, int start_y, int end_x, int end_y) {
    n_rows = n_rows;
    n_cols = n_cols;
    start_x = start_x;
    start_y = start_y;
    end_x = end_x;
    end_y = end_y;
  }
};