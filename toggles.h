#ifndef TOGGLES
#define TOGGLES

#include <GL/glut.h>
#include "utils.h"
#include "globals.h"

class toggle
{
public:
  toggle(double,double);

  void draw();
  void flick();
  
  bool state;
  double x;
  double y;
};

#include "toggles.cpp"
#endif
