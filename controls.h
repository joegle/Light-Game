#ifndef CONTROLS
#define CONTROLS

#include <GL/glut.h>
#include "globals.h"

void keyboard(unsigned char key, int x, int y) {
   if (key == 27)
      exit(0);
   else if (key == 'a') {
     //dude.z+=10;
     dude.strafeLeft();
     glutPostRedisplay();
   }
   else if (key == 'd') {
    dude.strafeRight();
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
     //dude.o-=10;
     dude.goForward();
     glutPostRedisplay();
   }
   else if (key == 's') {
     //dude.s+=5;
     dude.goBackward();
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
     dude.doSomething();
     glutPostRedisplay();
     
   }

}	    

void special(int key, int x, int y) {
   if (key == GLUT_KEY_LEFT) {
     dude.strafeLeft();
     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_RIGHT) {
     dude.strafeRight();
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

void mouseMove(int x, int y)
{
    //dude.o = -x * .3;
    // dude.s = y * .3;
    
	if(!dude.mouseWarp)
		{
			int centerX = width / 2;
			int centerY = height / 2;

			int deltaX = -1 * (x - centerX);
			int deltaY = -1 * (y - centerY);
		
			dude.o += deltaX;
			if(dude.s + deltaY > -90 && dude.s + deltaY < 90)
      	dude.s += deltaY;
			dude.mouseWarp = true;
			glutWarpPointer(centerX, centerY);
		}
		else
		{
		    dude.mouseWarp = false;
		}
	glutPostRedisplay();
}

#endif
