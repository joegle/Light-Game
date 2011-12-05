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
}

void box::drawHeld()
{
  glPushMatrix();
    glTranslatef(x*20,z,y*20);
    glRotated(angle, 0, 1, 0);
    glScaled(0.25,0.25,0.25);
    glTranslatef(0,1,0);
    glutSolidTeapot(1);
  glPopMatrix();
}

void box::draw()
{
  if(!dude && !placed)
   {
    glPushMatrix();
     glTranslatef(x*20,0,y*20);
     glRotatef(angle, 0, 1, 0);
     glScaled(0.25,0.25,0.25);
     glTranslatef(0,1,0);
     glutSolidTeapot(1);
   glPopMatrix();
  }
}
