#ifndef TOGGLES
#define TOGGLES

#include <GL/glut.h>
#include "utils.h"

class toggle
{
public:
  toggle(double,double);
  toggle();

  void draw();
  void flick();

  bool state;
  double x;
  double y;
  //  color c;
};

#include "toggles.cpp"
#endif
