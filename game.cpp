//   g++ -o test -lglut -lGLU lab4_start.cpp


#include <cstdlib>         /* For _MAX_PATH definition */
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <string.h>

#include "globals.h"
#include "time.h"
#include "utils.h"
#include "init.h"
#include "objects.h"
#include "controls.h"

using namespace std;
// http://fly.cc.fer.hr/~unreal/theredbook/chapter03.html

// This function inits things like the globals
void init() { 
  
  width = glutGet(GLUT_WINDOW_WIDTH);
  height = glutGet(GLUT_WINDOW_HEIGHT);
  GLfloat b[] = { 0.0, 0.0, 0.0, 0 };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, b);
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST); //enable the depth testing
  glEnable(GL_LIGHTING); //enable the lighting
  glutSetCursor(GLUT_CURSOR_NONE);

  srand(time(NULL));
  processfile();
  world._toggles[0].state=1;
  glEnable(GL_LIGHT0);


  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  world.LoadGLTextures();
  glEnable(GL_TEXTURE_2D);

  glShadeModel(GL_SMOOTH); //set the shader to smooth shader

}

void output()
{
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
      glLoadIdentity();
      string strOil = convertInt(dude.lampOil);
      string stringText = "Oil ";
      stringText = stringText.append(strOil); stringText.append("%");
      glColor4f(1,1,1,1);
      glRasterPos2f(width-80, height/2);
      for (int i=0; i < stringText.length(); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stringText[i]);
      glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
}

void outputWin()
{
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
      glLoadIdentity();
      string stringText = "You've Won";
      glColor4f(1,1,1,1);
      glRasterPos2f(width/2, height/2);
      for (int i=0; i < stringText.length(); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stringText[i]);
      glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
}

void initTransformation() {
  glMatrixMode (GL_PROJECTION); //set the matrix to projection
  glLoadIdentity ();
  gluPerspective (60, (GLfloat)width / (GLfloat)height, 1.0, 1000.0); 
  glMatrixMode( GL_MODELVIEW);
  glLoadIdentity();
}

// Don't change the matrix mode transformations here!
void drawObjects() {
  
  glMatrixMode( GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(dude.x,dude.z,dude.y,
	    dude.x+sin(f(dude.o))*cos(f(dude.s)),
	    dude.z+sin(f(dude.s)),
	    dude.y+cos(f(dude.o))*cos(f(dude.s)),
	    0,1,0);

  for(int i = 0; i < world._lights.size(); i++)
  {
     world._lights[i].init();
  }

  dude.look();
  dude.setLamp();
  world.drawWorld();

}

void display() {
  glClearColor(0,0,0,0); 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawObjects();

  if (world.won)
  {
    GLfloat b[] = { 1,1, 1, 1 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, b);

    outputWin();
  }
  else
    output();

  glutSwapBuffers();  // Makes the drawing appear on the screen.
}

void idle() {
  world.tick();

  double amtBurned = .1;
  #if defined (_MSC_VER) 
	amtBurned *= 10;
  #endif 
  dude.lampOil = (dude.lampOil > 0 && dude.lampState && !oilGodMode) ? dude.lampOil-amtBurned : dude.lampOil;
  dude.lampOil = (dude.lampOil < 100 && !dude.lampState) ? dude.lampOil+amtBurned/4 : dude.lampOil;
  dude.lampOil = (oilGodMode) ? 100 : dude.lampOil;
  glutPostRedisplay();
}


// Don't remove this
void reshape(int new_width, int new_height) {
  height = new_height;
  width = new_width;

  glViewport(0,0,new_width,new_height);
  glMatrixMode (GL_PROJECTION); //set the matrix to projection
  glLoadIdentity ();
  gluPerspective (60, (GLfloat)width / (GLfloat)height, 1.0, 1000.0); 
  glMatrixMode( GL_MODELVIEW);
}

int main(int argc, char **argv) {
  glutInit(&argc,argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  
  glutInitWindowSize(800, 800);       // Set the size of the window here.
  glutInitWindowPosition(0, 0);    // Upper left corner of window.

  glutCreateWindow("Game"); // Title displayed in window title bar.

  //glutFullScreen();   
 
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  
  glutKeyboardFunc(keyboard); 
  glutSpecialFunc(special);   
  glutPassiveMotionFunc(mouseMove);
  glutIdleFunc(idle);         
  
  init();
  glutMainLoop();

  return 0;
}
