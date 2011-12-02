
// Places light
void light()
{
  light_position[1]=sin(f(world_time*100));
  light_position[0]=cos(f(world_time*100));
  light_position[2]=cos(f(world_time*100)+75);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}



// draw post at (x,y)
void post(double x,double y){

  glPushMatrix();

  glTranslated(x*20,0,y*20);

  glColor3f(0,0,1);
  glutSolidTeapot(1);

  glPopMatrix();

  
}


// Draw all the walls from the data in 'walls' in globals.h

void teapot(double x,double y){
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };

  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  
  glPushMatrix();
   glScaled(3,3,3);

   glTranslated(x,1,y);
   glColor3f(1,0,0);
   glutSolidTeapot(1);
   glPopMatrix();
}

void table(double x,double y){

  GLfloat mat_specular[] = { 0.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };

  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

   double p=1.5;
   double w=10;
   double h=3;
   glPushMatrix();

    glScaled(2,2,2);

    glScaled(0.5,h,0.5);

    glTranslated(x,0.5,y);


    glPushMatrix();
    glTranslated(w,0,w*2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,w*2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(w,0,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();


   
    glTranslated(w/2,.5,w);
    glScaled(w,.1,w*2);

    glutSolidCube(1);

    glPopMatrix();
    glPopMatrix();


}
