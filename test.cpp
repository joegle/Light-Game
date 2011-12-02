//   g++ -o test -lglut -lGLU lab4_start.cpp


#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <GL/glut.h>
using namespace std;

const int milliseconds_per_frame = 100;  // Time you would LIKE per frame
                                        // The actual time can be longer.
                                        
int width;   // Current width of window; value is maintained by reshape().
int height;  // Current height of window; value is maintained by reshape().

float x_rotate = 0.0;   // Amount of rotation of the entire scene about
                        //    the x-axis.
float y_rotate = 0.0;   // Amount of rotation of the entire scene about
                        //    the y-axis.  This is applied BEFORE the x-rotation.

float t ;
bool ortho = false;     // True if an orthographic projection is used,
                        //   false for a perspective projection.

bool animating = false;  // The value is toggled when user hits the "A" key.


void init() {
  glEnable(GL_COLOR_MATERIAL);
  glEnable (GL_DEPTH_TEST); //enable the depth testing
  glEnable (GL_LIGHTING); //enable the lighting
  glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
  glEnable (GL_LIGHT1); //enable LIGHT1, our Ambient Light
  glShadeModel (GL_SMOOTH); //set the shader to smooth shader
}


void timer(int id) {
   t+=10;
   glutPostRedisplay();
}

float f(float A,float f,float p){
  return A*sin(t*f*3.14/180+p*3.14/180);
}

void initTransformation() {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   double aspect = ((double)height)/((double)width);
   if (ortho) {
      if (aspect >= 1)
         glOrtho(-16,16,-16*aspect,16*aspect,30,70);
      else
         glOrtho(-16/aspect,16/aspect,-16,16,30,70);
   }
   else {
      if (aspect >= 1)
         glFrustum(-10,10,-10*aspect,10*aspect,30,70);
      else
         glFrustum(-10/aspect,10/aspect,-10,10,30,70);
   }
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0,0,50,0,0,0,0,1,0);
   glRotatef(x_rotate,1,0,0);  // Rotation of whole scene
   glRotatef(y_rotate,0,1,0);
}

void drawObjects() {

   GLfloat DiffuseLight[] = {1, 1, 1}; //set DiffuseLight
   GLfloat AmbientLight[] = {1, 1, 1}; //set AmbientLight
   glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
   glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
   GLfloat LightPosition[] = {0,0,1,0};

   glColor3f(.97,.93,0.72);
   glScalef(3,3,3); 
   glRotatef(90,1,0,0);
   GLUquadricObj *b = gluNewQuadric();
   GLUquadricObj *base = gluNewQuadric();
   GLUquadricObj *m = gluNewQuadric();
   GLUquadricObj *t = gluNewQuadric();

   float th = 0.5;
   float tr = 0.6;
   float tbr = 0.5;
   float mh = 0.1;
   float bh = 0.8;
   glRotatef( f(360,0.3,20), f(1,.9,2), f(1,0.51,13), f(1,.01,77));     

   // Top cone part
   gluCylinder(t, tr, tbr, th, 20, 10);
   glTranslatef(0,0,th);

   // Middle (bend) cone part
   glColor3f(.97,.93,.63);
   gluCylinder(m, tbr, tbr*.9, mh, 20, 10);
   glColor3f(.97,.93,.73);
   glTranslatef(0,0,mh);

   // Bottom (longest) cone part
   gluCylinder(b, tbr*.9,tbr*.7, bh, 20, 10);
   glTranslatef(0,0,bh);
   
   // The bottom base of cone
   gluDisk(base,0,tbr*.7,20,30);
   glTranslatef(0,0,-1*(th+mh+bh));

   // Make the ice cream
   //   Made of 3 stacked torus and a tetrahedron tip
   glColor3f(1,0.3,0.5);
   glScalef(0.5,0.5,0.5);
   glutSolidTorus( .5, 1.0, 20, 20);
   glTranslatef(0,0,-0.8);
   glutSolidTorus( .3, 1.0, 20, 20);
   glTranslatef(0,0,-0.58);
   glutSolidTorus( .3, 0.6, 40, 40);
   glRotatef(90,0,1,0);
   glutSolidTetrahedron();
   glPushMatrix();



   // Make ring of rings   
   glLoadIdentity();
   glColor3f(1,1,0);
   // Rotate the whole ring's normal
   glRotatef(f(360,.3,0),f(1,.25,2),f(1,0.17,100),f(1,1,77));     

   for(int i=0;i<=16;i++){
     glPushMatrix();

     // This moves the normal vector of the large ring
     glRotatef(f(360,.3,0),f(1,.25,2),f(1,0.17,100),f(1,1,20));     

     // This rotates on the large ring axis so that we have a circle of rings
     glRotatef(i*22.5,1,0,0); 

     // This tilts single rings
     glRotatef(f(360,.3,0),f(1,.25,2),f(1,0.11,13),f(1,.01,227)); 

     // Sets large radius
     glTranslatef(0, f(8,1,2), 0); 

     // Draw the ring
     glutSolidTorus(f(.1,.8,0), f(4,.1,1), 20, 20);

     // Go back to old matrix so we can plot the next ring
     glPopMatrix();
   }


}


/**
 *  Called whenever the windows needs to be redrawn.  It should
 *  completely redraw the image that is to be displayed in the window.
 *  To force it to be called, call the subroutine  glutPostRedisplay().
 */
void display() {
   if (!animating) {
         // Cause display to be called again after milliseconds_per_frame.
      glutTimerFunc(milliseconds_per_frame,timer,1);  
   }
   glClearColor(0,0,0,1); 
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
   initTransformation();           // Setup projection and view.
   drawObjects();
   glFlush();
   glutSwapBuffers();  // Makes the drawing appear on the screen.
}


/**
 *  Called when the user changes the size of the window.
 *  It should not be necessary to modify this.
 */
void reshape(int new_width, int new_height) {
   glViewport(0,0,new_width,new_height);
   height = new_height;
   width = new_width;
}


/**
 *  If you uncomment the glutMouseFunc() call in the the main program,
 *  then this will be called whenever the user presses or releases 
 *  any of the buttons on the mouse.
 */
void mouse(int button, int state, int x, int y) {
}


/**
 *  If you uncomment the glutMotionFunc() call in the the main program,
 *  then this will be called whenever the user moves the mouse.
 */
void motion(int x, int y) {
}


/**
 *  If you uncomment the glutKeyboardFunc() call in the the main program,
 *  then this will be called whenever the user types a character on
 *  the keyboard.
 */
void keyboard(unsigned char key, int x, int y) {
   if (key == 27)
      exit(0);
   else if (key == 'a' || key == 'A') {
     animating = !animating;
      glutPostRedisplay();
   }
   else if (key == 'p' || key == 'P') {
      ortho = !ortho;
      if (!animating)
         glutPostRedisplay();
   }
}


/**
 *  If you uncomment the glutSpecialFunc() call in the the main program,
 *  then this will be called when the user presses certain special
 *  keys on the keyboard, such  as the arrow keys and function keys.
 */
void special(int key, int x, int y) {
   if (animating)
      return;

   t+=10;
   if (key == GLUT_KEY_LEFT) {
      y_rotate -= 15;
      glutPostRedisplay();
   }
   else if (key == GLUT_KEY_RIGHT) {
      y_rotate += 15;
      glutPostRedisplay();
   }
   else if (key == GLUT_KEY_UP) {
      x_rotate += 15;
      glutPostRedisplay();
   }
   else if (key == GLUT_KEY_DOWN) {
      x_rotate -= 15;
      glutPostRedisplay();
   }
   else if (key == GLUT_KEY_HOME) {
      x_rotate = y_rotate = 0;
      glutPostRedisplay();
   }
}


/**
 *  If you uncomment the glutIdleFunc() call in the the main program,
 *  then this will be called whenever the program does not have any
 *  other events to process.  It is can be called repeatedly
 *  while the program is idle.
 */
void idle() {
}


int main(int argc, char **argv) {
  cout<<"Press 'a' to animate\n";

   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(500,500);       // Set the size of the window here.
   glutInitWindowPosition(150,50);    // Upper left corner of window.
   glutCreateWindow("OpenGL Window"); // Title displayed in window title bar.
   
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);

   //glutMouseFunc(mouse);       // Uncomment to enable mouse handling.
   //glutMotionFunc(motion);     // Uncomment to enable mouse motion handling. 
   glutKeyboardFunc(keyboard); // Uncomment to enable ASCII key handling.
   glutSpecialFunc(special);   // Uncomment to enable special key handling.
   glutIdleFunc(idle);         // Uncomment to enable the idle function.
   
   init();
   glutMainLoop();
}
