#ifndef LIGHTS
#define LIGHTS

#include <GL/glut.h>
#include <iostream>
#include <string>

using namespace std;
class light
{
 public:
  light(int n, GLfloat x, GLfloat y, GLfloat z);
  
  void draw();
  GLenum getLightEnum(int n);
  void toggleLight(int n, bool state);

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
