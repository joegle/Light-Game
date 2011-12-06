#include "spikeTrap.h"

spikeTrap::spikeTrap(double xx,double yy)
{
  x = xx * 20;
  y = yy * 20;
  down = true;
}

void spikeTrap::draw()
{
  glPushMatrix();
    glTranslatef(x,0,y);
    for(int i = -5; i<5;i++)
    {
      for(int j = -5; j<5;j++)
      {
        glPushMatrix();
            glDisable(GL_COLOR_MATERIAL); 
            GLfloat materialSpecular[] = {0.8f, 0.8f, 0.8f, 1.0f};    
            GLfloat materialEmission[] = {0, 0, 0, 1.0f};    
            GLfloat materialColor[] = {.3, .3, .3, 1};	
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);      
            glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
            glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);        
            glMaterialf(GL_FRONT, GL_SHININESS, 15.0f);
          if(down)
            glTranslatef(0,-.8,0);
          glTranslatef(i,0,j);
          glRotatef(90,-1,0,0);
          glutSolidCone(.3,1,36,36);
        glPopMatrix();
      }
    }
  glPopMatrix();
}

