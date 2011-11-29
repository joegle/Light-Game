/*******************************************************************************
Author: Joseph Wright
Course: CMPSC 457 - 2011

Credits:    

Assignment:     Lab 2
Compiler:       gcc -lglut  (and runs on windows visual studio)

 I certify that, this program code is my work.  Others may have assisted me
 with planning and concepts, but the code was written, solely, by me.

 I understand that submitting code which is totally or partially the product
 of other individuals is a violation of the Academic Integrity Policy and not
 acceptable ethical conduct. Violations of academic integrity policies will
 be handled as noted in the instructor?s syllabus.
 Falsification of execution results is an inappropriate and unacceptable
 activity. Such violations may result in zero credit for the assignment,
 reduced credit for the assignment, or course failure.
*******************************************************************************/

#include <stdlib.h>
//#include <GLUT/glut.h>
#include <GL/glut.h>
#include <math.h>

GLfloat x=0.5; // x,y of kriby position
GLfloat y=0.5;
GLfloat dx=0.0002; // vector for speed
GLfloat dy=0.0003;
float w=0.1; //Kirby radius
float r=1; // Kirby colors
float g= 0.796078431;
float b=0.811764706;
float wh=400; // window h and w
float ww=400;
float pw,ph; //rescalling factors for h and w
int doubleb;


void myReshape(int w, int h)
{
  pw=ww/glutGet(GLUT_WINDOW_WIDTH);
  ph=wh/glutGet(GLUT_WINDOW_HEIGHT);
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,1/pw, 0, 1/ph, -1.0, 1.0);
}


void bounce(void)
{
  x+=dx; 
  y+=dy;
  if(x+0.2 > 1/pw || x< 0.2)
    {
      dx *= -1.00;
      //Get random RGB values for face
      r=(float)rand()/(float)RAND_MAX;
      g=(float)rand()/(float)RAND_MAX;
      b=(float)rand()/(float)RAND_MAX;

    }
  if(y+0.2 > 1/ph || y < 0.2)
    {
      r=(float)rand()/(float)RAND_MAX;
      g=(float)rand()/(float)RAND_MAX;
      b=(float)rand()/(float)RAND_MAX;
      dy *= -1.00; 
    }
  glutSetWindow(doubleb);
  glutPostRedisplay();
}

void kirby()
{
  // Start with main face area
  float fx=0;
  float fy=0;
  float fr=.2;
  int i;

  glColor3f(r, g,b);
  glBegin(GL_TRIANGLE_FAN);
  for(i=0; i<=200; i+=6)
      glVertex2f(x+fr*cos(i),y+fr*sin(i));
  glEnd();

  float ex=fy-0.05;
  float ey=fx+0.06;
  float er=.07;
  float ee=.4;

  //draw eyes
  glColor3f(0.415686275,0.11372549,0.164705882);
  glBegin(GL_TRIANGLE_FAN);
  for(i=0; i<=200; i+=6)
      glVertex2f(x+ex+er*cos(i)*ee,y+ey+er*sin(i));
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  for(i=0; i<=200; i+=6)
      glVertex2f(x-ex+er*cos(i)*ee,y+ey+er*sin(i));
  glEnd();

  // Gleam in the eyes
  ey*=1.5;
  er*=0.5;
  glColor3f(1,1,1);
  glBegin(GL_TRIANGLE_FAN);
  for(i=0; i<=200; i+=6)
      glVertex2f(x+ex+er*cos(i)*ee,y+ey+er*sin(i));
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  for(i=0; i<=200; i+=6)
      glVertex2f(x-ex+er*cos(i)*ee,y+ey+er*sin(i));
  glEnd();


  //Smile is arc of a circle
  float sw=.1;
  float sy=.1;
   glLineWidth(2);
  glColor3f(0.415686275,0.11372549,0.164705882);
  glBegin(GL_LINE_STRIP);
  for(i=-30; i>-150; i-=5)
      glVertex2f(x+er*cos(i*3.14/180),y+er*sin(i*3.14/180));
  glEnd();


  //Cheeks are ovals
  float cy=0.0189;
  float cx=.09;

  glColor3f(1,0.439215686,0.454901961);
  glBegin(GL_TRIANGLE_FAN);
  for(i=0; i<=200; i+=6)
    glVertex2f(x-cx-er*cos(i),y-cy+er*sin(i)*ee);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  for(i=0; i<=200; i+=6)
    glVertex2f(x+cx-er*cos(i),y-cy+er*sin(i)*ee);
  glEnd();
  

}

void displayd(){
  glClear (GL_COLOR_BUFFER_BIT);
  kirby();
  glutSwapBuffers();
}

void key(unsigned char k, int x, int y)
{

  // Exit on 'q' press and ignore else
  switch (k) {
  case 'q':  /* Escape */
    exit(0);
    break;
  default:
    return;
  }
  glutPostRedisplay();
}

void myinit ()
{
  glClearColor (0.0, 0.0, 0.0, 1.0);
  glColor3f(1, 0.796078431,0.811764706);
  glShadeModel (GL_FLAT);
}

void mouse(int btn, int state, int x, int y)
{
  // Exit on right click
  if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)  
    exit(0);
}


int main(int argc, char** argv)
{
  // Init
  glutInit(&argc,argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(500,200);
  glutInitWindowSize(wh,ww); 
  doubleb=glutCreateWindow("Kirby");
  myinit ();

  // Set callbacks
  glutDisplayFunc(displayd);
  glutReshapeFunc(myReshape);
  glutIdleFunc(bounce);
  glutMouseFunc(mouse);
  glutKeyboardFunc(key);
  glutMainLoop();

}
