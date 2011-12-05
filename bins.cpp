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
    glDisable(GL_COLOR_MATERIAL); //Required for the glMaterial calls to work
    
    if(!filled)  
    {	
      GLfloat materialColor[] = {c.r, c.g, c.b, c.a};
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    }  
    else  
    {	
      GLfloat materialColor[] = {0, 0, 0, 1};
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    }

    GLfloat materialSpecular[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat materialEmission[] = {0, 0, 0, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialf(GL_FRONT, GL_SHININESS, 15.0f); 
    gluCylinder( myQuad, 2.0, 2.0, 3.0, 20, 2 );
  glPopMatrix();
}
