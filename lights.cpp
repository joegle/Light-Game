#include "lights.h"

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