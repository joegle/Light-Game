//   g++ -o test -lglut -lGLU lab4_start.cpp

#include <stdlib.h>         /* For _MAX_PATH definition */
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <GL/glut.h>

#include "globals.h"
#include "utils.cpp"
#include "init.cpp"   // this will process the input.in and initilize globals (input.cpp)
#include "controls.cpp"
#include "objects.cpp"

using namespace std;




// http://fly.cc.fer.hr/~unreal/theredbook/chapter03.html


int width;   // Current width of window; value is maintained by reshape().
int height;  // Current height of window; value is maintained by reshape().


// This function inits things like the globals
void init() {
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST); //enable the depth testing
  glEnable(GL_LIGHTING); //enable the lighting
  glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
  //glEnable(GL_LIGHT1); //enable LIGHT1, our Ambient Light

  processfile();

  player.x=0;
  player.y=0;
  player.z=1;

  glShadeModel(GL_SMOOTH); //set the shader to smooth shader

}


void initTransformation() {
  glMatrixMode (GL_PROJECTION); //set the matrix to projection
  glLoadIdentity ();
  gluPerspective (60, (GLfloat)width / (GLfloat)height, 1.0, 1000.0); 
  
  glMatrixMode( GL_MODELVIEW);
  glLoadIdentity();
}


void tests(){
  wall(0,0,0,.5);
  wall(0,0,1,1);
  wall(.5,0,1.5,0);

  post(0,0);
  post(1,1);
  post(0.5,0.5);
  post(2,0.5);

 
  teapot(10,10);
  table(-20,20);

  table(10,10);
}

void drawObjects() {
  

  // polar coords
  gluLookAt(player.x,player.z,player.y,
	    player.x+sin(f(player.o))*cos(f(player.s)),
	    player.z+sin(f(player.s)),
	    player.y+cos(f(player.o))*cos(f(player.s)),
	    0,1,0);

  light();
  floor();
  drawWalls();

  tests();
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
  world_time += 0.001;
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
  
  glutInitWindowSize(500,500);       // Set the size of the window here.
  glutInitWindowPosition(150,50);    // Upper left corner of window.

  glutCreateWindow("Game"); // Title displayed in window title bar.

  glutFullScreen();   

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  
  glutKeyboardFunc(keyboard); 
  glutSpecialFunc(special);   
  glutIdleFunc(idle);         
  
  init();
  glutMainLoop();
}
