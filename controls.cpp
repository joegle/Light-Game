#ifndef CONTROLS
#define CONTROLS

#include <GL/glut.h>
#include "globals.h"

using namespace std;
void foo()
{
  cout<<"foo";
}



void keyboard(unsigned char key, int x, int y) {
   if (key == 27)
      exit(0);
   else if (key == 'a') {
     dude.z+=10;
     glutPostRedisplay();
   }
   else if (key == 'z') {
     dude.z-=10;
      glutPostRedisplay();
   }
   else if (key == 'q') {
     dude.o+=10;
     glutPostRedisplay();
   }
   else if (key == 'w') {
     dude.o-=10;
     glutPostRedisplay();
   }
   else if (key == 's') {
     dude.s+=5;
     glutPostRedisplay();
   }
   else if (key == 'x') {
     dude.s-=5;
     glutPostRedisplay();
   }
   else if (key == 'j') {
     glutPostRedisplay();
   }
   else if (key == 'k') {
     glutPostRedisplay();
   }

   else if (key == ' ') {
     cout<<"space";
     dude.doSomething();
     glutPostRedisplay();
     
   }

}	    


void special(int key, int x, int y) {
   if (key == GLUT_KEY_LEFT) {
     dude.turn(10);
     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_RIGHT) {
     dude.turn(-10);
     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_UP) {
     dude.goForward();
     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_DOWN) {
     dude.goBackward();
     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_END) {
     dude.s += 5;
     glutPostRedisplay();
   }
}

#endif