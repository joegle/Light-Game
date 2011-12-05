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
  c = randomColor();
}

void box::drawHeld()
{
   glPushMatrix();
    glTranslatef(x*20,z,y*20);
    glRotated(angle, 0, 1, 0);
    glScaled(0.25,0.25,0.25);
    glTranslatef(0,1,0);
    GLfloat materialColor[] = {c.r, c.g, c.b, c.a};	
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);      
    //The specular (shiny) component of the material    
    GLfloat materialSpecular[] = {0.8f, 0.8f, 0.8f, 1.0f};    
    //The color emitted by the material    
    GLfloat materialEmission[] = {0, 0, 0, 1.0f};    
    glDisable(GL_COLOR_MATERIAL); //Required for the glMaterial calls to work        
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);        
    glMaterialf(GL_FRONT, GL_SHININESS, 15.0f);
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
      GLfloat materialColor[] = {c.r, c.g, c.b, c.a};	
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);      
      //The specular (shiny) component of the material    
      GLfloat materialSpecular[] = {0.8f, 0.8f, 0.8f, 1.0f};    
      //The color emitted by the material    
      GLfloat materialEmission[] = {0, 0, 0, 1.0f};    
      glDisable(GL_COLOR_MATERIAL); //Required for the glMaterial calls to work        
      glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
      glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);        
      glMaterialf(GL_FRONT, GL_SHININESS, 15.0f);
      glutSolidTeapot(1);
   glPopMatrix();
  }
}
