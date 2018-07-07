#ifndef SPIKETRAP
#define SPIKETRAP

#include <GLUT/glut.h>
#include "utils.h"

class spikeTrap{
  public:
  spikeTrap(double xx,double yy);
  void draw();
  
  bool down;
  double x, y;
};

#include "spikeTrap.cpp"
#endif
