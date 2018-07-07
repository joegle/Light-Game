#ifndef BOXES
#define BOXES

#include <GLUT/glut.h>
#include "utils.h"

class box
{
public:
  box(double,double);
  box();
  void draw();
  void drawHeld();
  
  bool dude; //does the dude have it
  bool placed;
  double x;
  double y;
  double z;
  double angle;

  color c;
};

#include "boxes.cpp"
#endif
