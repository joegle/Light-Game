#include "toggles.h"

toggle::toggle(){}

toggle::toggle(double xx,double yy)
{
  state=false;
  x=xx;
  y=yy;
  //  c=randomColor();
}

void toggle::draw()
{
      glPushMatrix();
      glTranslated(x*20,0,y*20);
      glRotated(0, 0, 1, 0);
      glScaled(0.25,0.25,0.25);
      glTranslated(0,1,0);
      glColor3f(1,1,0);
      glutSolidTeapot(1);
      glPopMatrix();

  cout<<"pop"<<endl;

    glPushMatrix();
        glTranslated(x*20,0,y*20);
        glScalef(0.25,1.5,0.25);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glColor3f(1,0,0);
      glTranslated(x*20, 0.78, y*20);
      glColor3f(1,0,0);
      glScalef(0.15,0.15,0.15);
      glutSolidCube(0.5);
      glutSolidTeapot(1);
    glPopMatrix(); 
}
