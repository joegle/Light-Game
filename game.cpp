//   g++ -o test -lglut -lGLU lab4_start.cpp


#include <stdlib.h>         /* For _MAX_PATH definition */
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <string>

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

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST); //enable the depth testing
  glEnable(GL_LIGHTING); //enable the lighting
  glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
  //glEnable(GL_LIGHT1); //enable LIGHT1, our Ambient Light

  glutSetCursor(GLUT_CURSOR_NONE); 

  srand(time(NULL));
  processfile();



  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  world.LoadGLTextures();
  glEnable(GL_TEXTURE_2D);


  

  glShadeModel(GL_SMOOTH); //set the shader to smooth shader

}


void initTransformation() {
  glMatrixMode (GL_PROJECTION); //set the matrix to projection
  glLoadIdentity ();
  gluPerspective (60, (GLfloat)width / (GLfloat)height, 1.0, 1000.0); 
  
  glMatrixMode( GL_MODELVIEW);
  glLoadIdentity();
}

void drawObjects() {

  dude.look();

  //placelight();

  //  cube.draw();

  world.drawWorld();

}

void display() {
  glClearColor(0,1,1,1); 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
  initTransformation();           // Setup projection and view.
  drawObjects();
  glFlush();
  glutSwapBuffers();  // Makes the drawing appear on the screen.
}

void idle() {
  world.tick();
  glutPostRedisplay();
}


// Don't remove this
void reshape(int new_width, int new_height) {
   glViewport(0,0,new_width,new_height);
   height = new_height;
   width = new_width;
}



int main(int argc, char **argv) {
  glutInit(&argc,argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  
  glutInitWindowSize(500, 500);       // Set the size of the window here.
  glutInitWindowPosition(0, 0);    // Upper left corner of window.

  glutCreateWindow("Game"); // Title displayed in window title bar.

glutFullScreen();   
 
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
