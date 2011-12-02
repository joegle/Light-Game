
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
     player.z+=10;
     glutPostRedisplay();
   }
   else if (key == 'z') {
     player.z-=10;
      glutPostRedisplay();
   }
   else if (key == 'q') {
     player.o+=10;
     glutPostRedisplay();
   }
   else if (key == 'w') {
     player.o-=10;
     glutPostRedisplay();
   }
   else if (key == 's') {
     player.s+=5;
     glutPostRedisplay();
   }
   else if (key == 'x') {
     player.s-=5;
     glutPostRedisplay();
   }
   else if (key == 'j') {
     world_y++;
     glutPostRedisplay();
   }
   else if (key == 'k') {
     world_y--;
     glutPostRedisplay();
   }

}	    


void special(int key, int x, int y) {
   if (key == GLUT_KEY_LEFT) {
     player.o+= 10;
     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_RIGHT) {
     player.o-= 10;
     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_UP) {
     player.y+= cos(f(player.o));
     player.x+= sin(f(player.o));
     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_DOWN) {
     player.y-= cos(f(player.o));
     player.x-= sin(f(player.o));

     glutPostRedisplay();
   }
   else if (key == GLUT_KEY_END) {
     player.s += 5;
     glutPostRedisplay();
   }
}
