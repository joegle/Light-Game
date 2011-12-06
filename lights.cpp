#include "lights.h"

light::light(int n, GLfloat x, GLfloat y, GLfloat z)
{
  position[0] = x*20;
  position[1] = y*20;
  position[2] = z; // always 3 from file
  position[3] = 1; // 0 = directional light, 1 = positional light (the one we want)

  // Random colorize
  color c=randomColor();
  diffuse[0] = 0.0;
  diffuse[1] = 0.0; 
  diffuse[2] = 0.0;
  diffuse[3] = 1.0;

  c=randomColor();
  ambient[0] = 1.0;
  ambient[1] = 1.0;
  ambient[2] = 1.0;
  ambient[3] = 1.0;

  c=randomColor();
  specular[0] = 0.0;
  specular[1] = 0.0;
  specular[2] = 0.0;
  specular[3] = 0;

  lightNum = n;
}

void light::draw() 
{
	double attenuation = 0.12;
	#if defined (_MSC_VER) 
		attenuation /= 2;
	#endif 
  glPushMatrix();
   glLightfv(getLightEnum(lightNum), GL_DIFFUSE, diffuse);
   glLightfv(getLightEnum(lightNum), GL_AMBIENT, ambient);
   glLightfv(getLightEnum(lightNum), GL_SPECULAR, specular);
   glLightf(getLightEnum(lightNum), /*GL_QUADRATIC_ATTENUATION*/GL_LINEAR_ATTENUATION,attenuation);
  glPopMatrix();

 }

void light::init()
{
  glPushMatrix();
    glLightfv(getLightEnum(lightNum), GL_POSITION, position);
  glPopMatrix();
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
      break;
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
