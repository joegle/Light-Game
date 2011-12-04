#include "bins.h"

bin::bin(double xx, double yy)
{
  filled = false;
  x = xx;

  y = yy;
  c = randomColor();
}


void bin::draw()
{
  GLUquadric *myQuad;
  myQuad=gluNewQuadric();

  glPushMatrix();

  glTranslated(x*20,0,y*20);
  glRotated(-90,1,0,0);
  glScaled(0.25,0.25,0.25);
  glTranslated(0,1,0);

  /*if(!filled)
    glColor3f(c.r,c.g,c.b);
  else
    glColor3f(0,0,0);*/

  gluCylinder( myQuad, 2.0, 2.0, 3.0, 20, 2 );
  //  glutSolidTeapot(1);

  glPopMatrix();
}
