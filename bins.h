#ifndef BINS
#define BINS

#include <GL/glut.h>
#include "utils.h"

class bin
{
public:
  bin(double,double);
  
  void draw();

  double x;
  double y;
  bool filled;

  color c;
};

#include "bins.cpp"
#endif