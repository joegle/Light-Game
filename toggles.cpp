#include "toggles.h"

toggle::toggle(){}

toggle::toggle(double xx,double yy)
{
  bool state;
  x=xx;
  y=yy;
  //  c=randomColor();
}

void toggle::draw()
{
      glPushMatrix();
      glTranslated(x*20,0,y*20);
      glRotated(angle, 0, 1, 0);
      glScaled(0.25,0.25,0.25);
      glTranslated(0,1,0);
      glColor3f(1,1,0);
      glutSolidTeapot(1);
      glPopMatrix();

  
}
