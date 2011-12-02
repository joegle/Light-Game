
// Places light
void light()
{
  light_position[1]=sin(f(world_time*100));
  light_position[0]=cos(f(world_time*100));
  light_position[2]=cos(f(world_time*100)+75);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}


void floor(){
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
  //  GLfloat mat_emission[] = { .2,0.1, 0.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };

  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  //glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

   glPushMatrix();
   glTranslatef(0,0,0);
   glScalef(60,60,60);

   glColor3f(1,0,1);


   glBegin(GL_QUADS);                      
   glTexCoord2f(-1.0, 1.0);   glVertex3f(-1.0f,0, 1.0f);     
   glTexCoord2f(1.0, 1.0);   glVertex3f( 1.0f,0, 1.0f);     
   glTexCoord2f(1.0, -1.0);   glVertex3f( 1.0f,0,-1.0f);     
   glTexCoord2f(-1.0, -1.0);   glVertex3f(-1.0f,0,-1.0f);     

   glEnd();   

   glPopMatrix();

}

void teapot(int x,int y){
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

void table(int x,int y){

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
