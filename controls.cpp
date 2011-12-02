
using namespace std;
void foo()
{
  player.x++;
  cout<<"foo";
}



void keyboard(unsigned char key, int x, int y) {
   if (key == 27)
      exit(0);
   else if (key == 'a') {
     player.y+=10;
     glutPostRedisplay();
   }
   else if (key == 'z') {
     player.y-=10;
      glutPostRedisplay();
   }
   else if (key == 'q') {
     player.s+=10;
     glutPostRedisplay();
   }
   else if (key == 'w') {
     player.s-=10;
     glutPostRedisplay();
   }

}	    


void special(int key, int x, int y) {
   if (key == GLUT_KEY_LEFT) {
     player.x+= 10;
     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_RIGHT) {
     player.x-= 10;
     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_UP) {
     player.z+= 10;
     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_DOWN) {
     player.z-= 10;
     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_HOME) {
     glutPostRedisplay();
   }
}
