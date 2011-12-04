#include "lights.h"

light::light(int n, GLfloat x, GLfloat y, GLfloat z)
{
  
  // random coord of the circuit matrix
  sx = r(0,30);
  sy = r(0,30);

  position[0] = x;
  position[1] = y;
  position[2] = z;
  position[3] = 1; // I don't know whats the 4th dimension

  // Random colorize
  color c=randomColor();
  diffuse[0] = c.r;
  diffuse[1] = c.g;
  diffuse[2] = c.b;
  diffuse[3] = c.a;

  c=randomColor();
  ambient[0] = c.r;
  ambient[1] = c.g;
  ambient[2] = c.b;
  ambient[3] = c.a;

  c=randomColor();
  specular[0] = c.r;
  specular[1] = c.g;
  specular[2] = c.b;
  specular[3] = c.a;

  lightNum = n;
}

void light::draw() 
{
  glPushMatrix();
   glLightfv(getLightEnum(lightNum), GL_POSITION, position);
   glLightfv(getLightEnum(lightNum), GL_DIFFUSE, diffuse);
   glLightfv(getLightEnum(lightNum), GL_AMBIENT, ambient);
   glLightfv(getLightEnum(lightNum), GL_SPECULAR, specular);
  glPopMatrix();
  //  glPushMatrix();

   double x=position[0];
   double y=position[1];

  glPushMatrix();
    glTranslated(x*20,0,y*20);
    glRotated(0, 0, 1, 0);
    //glScaled(.25,.25,.25);
    glTranslated(0,1,0);
    glColor3f(diffuse[0],diffuse[1],diffuse[2]);
    glutWireSphere(1, 20, 20);
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
      return GL_LIGHT0;
    }
}
