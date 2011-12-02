#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <string>
using namespace std;
class Lights
{
  public:
    Lights(int n, GLfloat pos[], GLfloat diff[], GLfloat amb[], GLfloat spec[]);

    void draw();
    GLenum getLightEnum(int n);
  
  private:
    int lightNum;
    GLfloat position[4];
    GLfloat diffuse[4];
    GLfloat ambient[4];
    GLfloat specular[4];
};

Lights::Lights(int n, GLfloat pos[], GLfloat diff[], GLfloat amb[], GLfloat spec[])
{
/*  for (int i=0; i<4; i++)
  {
    position[i] = pos[i];
    diffuse[i] = diff[i];
    ambient[i] = amb[i];
    specular[i] = spec[i];
  }*/

  lightNum = n;
}

void Lights::draw() 
{
   GLfloat position[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat spec[] = { 1.0, 1.0, 1.0, 1.0 }; 

  glPushMatrix();
   glLightfv(getLightEnum(lightNum), GL_POSITION, position);
   glLightfv(getLightEnum(lightNum), GL_DIFFUSE, diffuse);
   glLightfv(getLightEnum(lightNum), GL_AMBIENT, ambient);
   glLightfv(getLightEnum(lightNum), GL_SPECULAR, specular);
  glPopMatrix();

}

GLenum Lights::getLightEnum(int n)
{
  switch (n)
  {
    case 0:
		return GL_LIGHT0;
		break;
    case 1:
		return GL_LIGHT1;
		break;
	case 2:
		return GL_LIGHT2;
		break;
	 case 3:
		return GL_LIGHT3;
		break;
	case 4:
		return GL_LIGHT4;
		break;
	case 5:
		return GL_LIGHT5;
		break;
	case 6:
		return GL_LIGHT6;
		break;
	case 7:
		return GL_LIGHT7;
		break;
	default:
		return GL_LIGHT0;
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE);
  glutInitWindowSize(500,500);
  glutCreateWindow("");

  GLfloat pos[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat amb[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat diff[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat spec[] = { 1.0, 1.0, 1.0, 1.0 };

  Lights l = Lights(0, pos, diff, amb, spec);
  l.draw();
  
  return 0;
}
