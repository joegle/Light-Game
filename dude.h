#ifndef DUDE
#define DUDE

#include <iostream>
#include <vector>
#include "world.h"

using namespace std;

class dude
{
public:
  dude(world*);
  void foo();
  void wf();
  void look();
  void strafeLeft();
  void strafeRight();
  void goForward();
  void goBackward();
  void doSomething();
  void drop();
  
  void turn(double x);
  void setPosition(double a,double b,double c);

  //position (specifically the eye coord)
  double x;
  double y;
  double z;
  
  double o; //overhead angle like compass direction
  double s; //side angle; tilt of head
  
private:
  vector<bin> _bins;
  double forward_step;
  double backward_step;
  world* w;
  bool carrying;
  box load;
};

#include "dude.cpp"
#endif
