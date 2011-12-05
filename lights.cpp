#include "lights.h"

light::light(int n, GLfloat x, GLfloat y, GLfloat z)
{
  position[0] = x;
  position[1] = y;
  position[2] = z;
  position[3] = 0; // 0 = directional light, 1 = positional light

  // Random colorize
  color c=randomColor();
  diffuse[0] = 0.7;
  diffuse[1] = 0.7; 
  diffuse[2] = 0.7;
  diffuse[3] = 0.7;

  c=randomColor();
  ambient[0] = 0.0;
  ambient[1] = 0.0;
  ambient[2] = 0.0;
  ambient[3] = 0.0;

  c=randomColor();
  specular[0] = 0.7;
  specular[1] = 0.7;
  specular[2] = 0.7;
  specular[3] = 0.7;

  lightNum = n;
}

void light::draw() 
{
	float LightDir[3] = {0.0f, -1.0f, 0.0f}; // towards the viewer 
  glPushMatrix();
   glLightfv(getLightEnum(lightNum), GL_SPOT_DIRECTION, LightDir); 
   glLightfv(getLightEnum(lightNum), GL_POSITION, position);
   glLightfv(getLightEnum(lightNum), GL_DIFFUSE, diffuse);
   glLightfv(getLightEnum(lightNum), GL_AMBIENT, ambient);
   glLightfv(getLightEnum(lightNum), GL_SPECULAR, specular);
  glPopMatrix();

  double x=position[0];
  double y=position[1];
}

GLenum light::getLightEnum(int n)
{
  switch (n)
    {
    case 0:
      return GL_LIGHT0;
      break;
    case 1:
      return GL_LIGHT1;
      break;
    case 2:
      return GL_LIGHT2;
      break;
    case 3:
      return GL_LIGHT3;
      break;
    case 4:
      return GL_LIGHT4;
      break;
    case 5:
      return GL_LIGHT5;
      break;
    case 6:
      return GL_LIGHT6;
      break;
    case 7:
      return GL_LIGHT7;
      break;
    default:
      return GL_LIGHT0;
    }
}

void light::toggleLight(int n, bool state)
{
  if (state)
  {
    glEnable(getLightEnum(n));
  }
  else
    glDisable(getLightEnum(n));

}
