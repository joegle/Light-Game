#ifndef LIGHTS
#define LIGHTS

#include <GL/glut.h>
#include <iostream>
#include <string>

using namespace std;
class Lights
{
  public:
    Lights(int n, GLfloat pos[], GLfloat diff[], GLfloat amb[], GLfloat spec[]);

    void draw();
    GLenum getLightEnum(int n);
  
  private:
    int lightNum;
    GLfloat position[4];
    GLfloat diffuse[4];
    GLfloat ambient[4];
    GLfloat specular[4];
};

#include "lights.cpp"
#endif