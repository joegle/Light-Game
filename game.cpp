//   g++ -o test -lglut -lGLU lab4_start.cpp

#include <stdlib.h>         /* For _MAX_PATH definition */
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <GL/glut.h>
#include "controls.h"
#include "objects.h"


using namespace std;

double world_time=0;
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

struct Object {
  double x;
  double y;
  double z;
  double o; // Overhead direction (North,East)
  double s;  // Tilt of head
};
// http://fly.cc.fer.hr/~unreal/theredbook/chapter03.html

Object player ={20,20,20,0,0};

int width;   // Current width of window; value is maintained by reshape().
int height;  // Current height of window; value is maintained by reshape().


void init() {
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST); //enable the depth testing
  glEnable(GL_LIGHTING); //enable the lighting
  glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
  //glEnable(GL_LIGHT1); //enable LIGHT1, our Ambient Light

  glShadeModel(GL_SMOOTH); //set the shader to smooth shader

}

float f(float a){
  return a*3.14/180;
}


void initTransformation() {
  glMatrixMode (GL_PROJECTION); //set the matrix to projection
  glLoadIdentity ();
  gluPerspective (60, (GLfloat)width / (GLfloat)height, 1.0, 1000.0); 
  
  glMatrixMode( GL_MODELVIEW);
  glLoadIdentity();

}

void light()
{
  light_position[1]=sin(f(world_time*100));
  light_position[0]=cos(f(world_time*100));
  light_position[2]=cos(f(world_time*100)+75);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}



void drawObjects() {

  gluLookAt(player.x,player.y,player.z,
	    player.x+sin(f(player.s))*cos(f(player.o)),
	     player.y+sin(f(player.s))*sin(f(player.o)),
	     player.z+cos(f(player.s)),
	    0,1,0);
  light();
  floor();
  teapot(10,10);
  table(-20,20);

  table(10,10);
}

void display() {
  glClearColor(0,0,0,1); 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
  initTransformation();              // Setup projection and view.

  drawObjects();

  glFlush();
  glutSwapBuffers();  // Makes the drawing appear on the screen.
}


void reshape(int new_width, int new_height) {
   glViewport(0,0,new_width,new_height);
   height = new_height;
   width = new_width;
}


void idle() {
  world_time += 0.001;
  glutPostRedisplay();
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
