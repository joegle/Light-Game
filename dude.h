#ifndef DUDE
#define DUDE

#include <iostream>
#include <vector>
#include "world.h"

using namespace std;

class dude
{
public:
  dude(world* ww);
  void foo();
  void wf(); // is never defined
  void look();
  void strafeLeft();
  void strafeRight();
  void goForward();
  void goBackward();
  void doSomething();
  void drop();
  void turn(double x);
  void setPosition(double a,double b,double c);
  void setLamp();

  //position (specifically the eye coord)
  double x;
  double y;
  double z;
  double o; //overhead angle like compass direction
  double s; //side angle; tilt of head
  bool mouseWarp;

  // Dude's lamp settings
  double lampOil;
  GLenum lamp;
  bool lampState;
  GLfloat lampPos[4];
  GLfloat lampAmb[4];
  GLfloat lampDif[4];
  GLfloat lampSpec[4];

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
