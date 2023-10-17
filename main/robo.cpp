#include "headers.h"

Robo::Robo()
{
  
}

void Robo::Setup(int GRID_ROWS, int GRID_COLS, int GRID_SQUARE_SIDE_LEN, int START_X, int START_Y, int END_X, int END_Y, int ROBO_LEN, int ROBO_WIDTH, int TRIG1, int ECHO1, 
int ERROR1, int TRIG2, int ECHO2, int ERROR2, int TRIG3, int ECHO3, int ERROR3, int LEFTMOTOR1, int LEFTMOTOR2, int RIGHTMOTOR1, int RIGHTMOTOR2,
 int SCL, int SDA)
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

  // start condition
  curX = start_x;
  curY = start_y;
  curOrientation = 0;

  repulsiveForceConst = 10;
  repulsiveForceConst = 20;

  grid.init(GRID_ROWS, GRID_COLS, START_X, START_Y, END_X, END_Y);
  Left.Setup(TRIG1, ECHO1, ERROR1);
  Right.Setup(TRIG2, ECHO2, ERROR2);
  Forward.Setup(TRIG3, ECHO3, ERROR3);
  gyro.Setup(SCL, SDA);
  motors.Setup(LEFTMOTOR1, LEFTMOTOR2, RIGHTMOTOR1, RIGHTMOTOR2);

  grid.Visited[curX][curY] = 1;

  Serial.println("setup done");
}

void Robo::setObstacleCells()
{
  
  int LeftObstacleDist = (int)(Left.take_reading() / grid_square_side_len);
  int RightObstacleDist = (int)(Right.take_reading() / grid_square_side_len);
  int ForwardObstacleDist = (int)(Forward.take_reading() / grid_square_side_len);

  Serial.println("hello1");
  Serial.print(LeftObstacleDist);
  Serial.print(RightObstacleDist);
  Serial.println(ForwardObstacleDist);
  Serial.println("hello2");
  
  if(curOrientation == 0) // facing along +X
  {
      if(0 <= curX - LeftObstacleDist < grid_rows) grid.Array[curX - LeftObstacleDist][curY] = 1;
      if(0 <= curY + ForwardObstacleDist < grid_cols) grid.Array[curX][curY + ForwardObstacleDist] = 1;
      if(0 <= curX + RightObstacleDist < grid_rows) grid.Array[curX + RightObstacleDist][curY] = 1;
  }
  else if(curOrientation == 1) // facing along +X
  {
    if(0 <= curY + LeftObstacleDist < grid_cols) grid.Array[curX][curY + LeftObstacleDist] = 1;
    if(0 <= curX + ForwardObstacleDist < grid_rows) grid.Array[curX + ForwardObstacleDist][curY] = 1;
    if(0 <= curY - RightObstacleDist < grid_cols) grid.Array[curX][curY - RightObstacleDist] = 1;
  }
  else if(curOrientation == 2) // facing along -Y
  {
    if(0 <= curX + LeftObstacleDist < grid_rows) grid.Array[curX + LeftObstacleDist][curY] = 1;
    if(0 <= curY + ForwardObstacleDist < grid_cols) grid.Array[curX][curY + ForwardObstacleDist] = 1;
    if(0 <= curX - RightObstacleDist < grid_rows) grid.Array[curX - RightObstacleDist][curY] = 1;
  }
  else if(curOrientation == 3) // facing along -X
  {
    if(0<= curY - LeftObstacleDist < grid_cols) grid.Array[curX][curY - LeftObstacleDist] = 1;
    if(0<= curX - ForwardObstacleDist < grid_rows) grid.Array[curX - ForwardObstacleDist][curY] = 1;
    if(0<= curY + RightObstacleDist < grid_cols) grid.Array[curX][curY + RightObstacleDist] = 1;
  }

  Serial.println("hey");
}

pair<double, double> Robo::GetNetForce()
{
  pair<double, double> netForce = std::make_pair(0.0, 0.0);

  // add repulsive forces from obstacles
  for(int i = 0; i < grid.n_rows; i++)
  {
    for(int j = 0; j < grid.n_cols; j++)
    {
      if(grid.Array[i][j] == 1)
      {
        double ObstDistSq = ((curX - i) * (curX - i) + (curY - j) * (curY - j));
        double ObstDist = std:: pow(ObstDistSq, 0.5);
        double ObstForceMag = repulsiveForceConst / ObstDistSq;
        netForce.first += ObstForceMag * ((curX - i) / ObstDist); // X component, along with direction
        netForce.second += ObstForceMag * ((curY - j) / ObstDist); // Y component, along with direction
      }
    }
  }

  // add attractive force from target
  double TargetDistSq = ((curX - end_x) * (curX - end_x) + (curY - end_y) * (curY - end_y));
  double TargetDist = std:: pow(TargetDistSq, 0.5);
  double TargetForceMag = attractiveForceConst / TargetDistSq;
  netForce.first += TargetForceMag * ((curX - end_x) / TargetDist); // X component, along with direction
  netForce.second += TargetForceMag * ((curY - end_y) / TargetDist); // Y component, along with direction
  
  return netForce;
}

void Robo::Rotate(int angleToRotate)
{
  if(angleToRotate == 0)
    return;
  double angleRotated = 0.0;
  
  double absCurAngle = angleRotated ? angleRotated : -angleRotated;
  double absTotalAngle = angleToRotate ? angleToRotate : -angleToRotate;

  double angularVel[3];

  if(angleToRotate > 0) // towards right
    motors.setSpeed(motors.maxSpeed / 2, -motors.maxSpeed / 2);
  else if(angleToRotate < 0) // towards right
    motors.setSpeed(-motors.maxSpeed / 2, motors.maxSpeed / 2);

  while(absCurAngle < absTotalAngle)
  {
    delay(2); // move motors for 2 ms

    gyro.getAngularReading(angularVel);
    angleRotated += angularVel[2] * 0.002; // degrees
  }

  motors.setSpeed(0, 0); 

  // do we need to move some distance back to adjust position?
}

void Robo::MoveOneCellForward()
{
  double currentDistMoved = 0.0;
  double curVelY = 0.0;
  double accel[3];

  motors.setSpeed(motors.maxSpeed / 2, motors.maxSpeed / 2);

  while(currentDistMoved < grid_square_side_len)
  {
    delay(2);
    gyro.getLinearReading(accel);

    // second equation of motion : s = u * t + (1 / 2) * a * t * t
    currentDistMoved += curVelY * 2 + 0.5 * accel[1] * 2 * 2;
    // first equation of motion: v = u + a * t
    curVelY = curVelY + 2 * accel[1];
  }

  motors.setSpeed(0, 0);
}

void Robo::Move(pair<int, int> nextCell)
{
  // first find out the orientation required before moving one block forward
  int orientReq;
  if(nextCell.second == curY - 1)
    orientReq = 2; // -Y
  else if(nextCell.second == curY + 1)
    orientReq = 0; // +Y
  else if(nextCell.first == curX - 1)
    orientReq = 3; // -X
  else if(nextCell.first == curX + 1)
    orientReq = 1; // +X

  // fix for -90
  int orientChange = (orientReq - curOrientation) % 4;
  if(orientChange == 3)
    orientChange = -1;
  
  int angleToRotate = orientChange * 90;

  Rotate(angleToRotate);
  MoveOneCellForward();

  // update position and orientation
  curX = nextCell.first;
  curY = nextCell.second;
  curOrientation = orientReq;

  grid.Visited[curX][curY] = 1;
}

void Robo::Algorithm()
{
  while(!(curX == end_x && curY == end_y))
  {
    
    // take reading and set obstacles
    setObstacleCells();
    Serial.println("obstacles set");

    pair<double, double> netF = GetNetForce();
    
    // decide next cell (giving priority to neighbours along Y direction)
    pair<int, int> nextCell;
    if(netF.second < 0 &&  0 <= (curY - 1) < grid_cols && grid.Array[curX][curY - 1] == 0)
      nextCell = std::make_pair(curX, curY - 1);
    else if(netF.second > 0 &&  0 <= (curY + 1) < grid_cols && grid.Array[curX][curY + 1] == 0)
      nextCell = std::make_pair(curX, curY + 1);
    else if(netF.first < 0 &&  0 <= (curX - 1) < grid_rows && grid.Array[curX - 1][curY] == 0)
      nextCell = std::make_pair(curX - 1, curY);
    else if(netF.first > 0 &&  0 <= (curX + 1) < grid_rows && grid.Array[curX + 1][curY] == 0)
      nextCell = std::make_pair(curX + 1, curY);
    else // nowhere to move
      Confused();

    Move(nextCell);
  }
}

void Robo::Confused()
{
  motors.setSpeed(motors.maxSpeed, -motors.maxSpeed); // do clockwise wheelies
  while(1){}
}

void Robo::Victory()
{
  motors.setSpeed(-motors.maxSpeed, motors.maxSpeed); // do counterclockwise wheelies
  while(1){}
}