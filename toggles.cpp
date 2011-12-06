#include "toggles.h"

toggle::toggle(double xx,double yy)
{
  state=false;
  x=xx;
  y=yy;
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
		GLfloat materialColor[] = {.3, .3, .3, 1};	
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);      
    GLfloat materialSpecular[] = {0, 0, 0, 1};    
		GLfloat materialEmission[] = {0, 0, 0, 1};    
		glDisable(GL_COLOR_MATERIAL); //Required for the glMaterial calls to work        
		glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
		glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);        
		glMaterialf(GL_FRONT, GL_SHININESS, 15.0f);
    glutSolidCube(1.0);
  glPopMatrix();

  glColor3f(1.0,0,0);
  glPushMatrix();
    glTranslatef(x*20, 1.28, y*20);
    glScalef(0.15,0.15,0.15); 
    if(state) // Draw button down
	    glTranslatef(0,-0.4,0);
		GLfloat btn_materialColor[] = {1, 0, 0, 1};	
		
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, btn_materialColor);      
        GLfloat btn_materialSpecular[] = {0, 0, 0, 1};    
		GLfloat btn_materialEmission[] = {0, 0, 0, 1};    
		glDisable(GL_COLOR_MATERIAL); //Required for the glMaterial calls to work        
		glMaterialfv(GL_FRONT, GL_SPECULAR, btn_materialSpecular);
		glMaterialfv(GL_FRONT, GL_EMISSION, btn_materialEmission);        
		glMaterialf(GL_FRONT, GL_SHININESS, 15.0f);
    glutSolidCube(0.5);
  glPopMatrix();
}
