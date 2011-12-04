#include "toggles.h"

toggle::toggle(){}

toggle::toggle(double xx,double yy)
{
  state=false;
  x=xx;
  y=yy;
  //  c=randomColor();
}

void toggle::flick()
{
  state = !state;
}

void toggle::draw()
{
    glPushMatrix();
      glTranslatef(x*20,0.5,y*20);
      glScalef(0.25,1.5,0.25);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(x*20, 1.28, y*20);
      glScalef(0.15,0.15,0.15); 

      if(state) // Draw button down
	glTranslatef(0,-0.4,0);

      glutSolidCube(0.5);

    glPopMatrix();

}
