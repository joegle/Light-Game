#ifndef LIGHTS
#define LIGHTS

#include <GL/glut.h>
#include <iostream>
#include <string>

using namespace std;
class light
{
 public:
  light(int n,double,double,double);
  
  void draw();
  GLenum getLightEnum(int n);
  
  int sx;
  int sy;
  
  int lightNum;
  GLfloat position[4];
  GLfloat diffuse[4];
  GLfloat ambient[4];
  GLfloat specular[4];

 private:
};

#include "lights.cpp"
#endif
