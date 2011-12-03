#include "boxes.h"

box::box(){}

box::box(double xx,double yy)
{
  placed=false;
  dude=false;
  x=xx;
  y=yy;
  z=0;
  angle=0;
  c=randomColor();
}

void box::drawHeld()
{
  glPushMatrix();
  glTranslated(x*20,z,y*20);
  glRotated(angle, 0, 1, 0);
  glScaled(0.25,0.25,0.25);
  glTranslated(0,1,0);
  glColor3f(c.r,c.g,c.b);
  glutSolidTeapot(1);
  glPopMatrix();
}

void box::draw()
{
  if(!dude && !placed)
    {
      glPushMatrix();
      glTranslated(x*20,0,y*20);
      glRotated(angle, 0, 1, 0);
      glScaled(0.25,0.25,0.25);
      glTranslated(0,1,0);
      glColor3f(c.r,c.g,c.b);
      glutSolidTeapot(1);
      glPopMatrix();
  }
  
}