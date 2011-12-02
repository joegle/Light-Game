#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

int wHeight = 750, wWidth = 750; // window size

static GLdouble viewer[] = {0.0, 10.0}; // initial perspective
static GLdouble camera[] = {0.0, -1.0};
static GLfloat angle;

GLfloat floorMat[] = {0.10, 0.10, 0.10, 1.0}; // global floor material
GLfloat tableShine[] = {125};
GLfloat tableMatAmb[] = {0.65, 0.65, 0.65, 1.0}; // global light tables
GLfloat tableMatDiff[] = {0.50, 0.50, 0.50, 1.0};
GLfloat tableMatSpec[] = {0.70, 0.70, 0.70, 1.0};
GLfloat lampMat[] = {0.45, 0.45, 0.45, 1.0}; // base and neck of lamp
GLfloat lampRedLight[] = {1.0, 0.0, 0.0, 0.10}; // red fliter / lamp bulb
GLfloat lampGreenLight[] = {0.0, 1.0, 0.0, 0.10}; // green filter / lamp bulb
GLfloat lampBlueLight[] = {0.0, 0.0, 1.0, 0.10}; // blue filter / lamp bulb
GLfloat lightInt = 1.0;  // Light intensity toggle
GLfloat light0_pos[] = {0.0, 6.5, 0.0, 1.0}; // o1verhead light position
GLfloat light1_pos[] = {1,1.15,-4.25, 1.0}; // red lamp position
GLfloat light2_pos[] = {0.0,0.0,1.25, 1.0}; // green lamp position
GLfloat light3_pos[] = {0.0,0.0,1.25, 1.0}; // blue light position
GLfloat light4_pos[] = {1, 1.25, 4.25, 1.0}; // red filter position
GLfloat light5_pos[] = {0,.05,-1.31, 1.0}; // green filter position
GLfloat light6_pos[] = {0,.10,-1.3, 1.0}; // blue filter position

GLuint texture[2]; // Texture Array

struct Image
{
	unsigned int sizeX;
	unsigned int sizeY;
	GLubyte *data;
};

static unsigned int getint(FILE *fp)
{
	int c, c1, c2, c3;

	// get 4 bytes
	c = getc(fp);  
	c1 = getc(fp);  
	c2 = getc(fp);  
	c3 = getc(fp);

	return ((unsigned int) c) +   
		(((unsigned int) c1) << 8) + 
		(((unsigned int) c2) << 16) +
		(((unsigned int) c3) << 24);
}

static unsigned short getshort(FILE* fp)
{
	int c, c1;

	//get 2 bytes
	c = getc(fp);  
	c1 = getc(fp);

	return ((unsigned int) c) + (((unsigned int) c1) << 8);
}

int ImageLoad(char *filename, Image *image) 
{
	FILE *file;
	unsigned long size;                 // size of the image in bytes.
	//unsigned long i;					// standard counter.
	size_t i;					// standard counter.
	unsigned short int planes;          // number of planes in image (must be 1) 
	unsigned short int bpp;             // number of bits per pixel (must be 24)
	char temp;                          // temporary color storage for bgr-rgb conversion.

	// make sure the file is there.
	if ((file = fopen(filename, "rb"))==NULL) 
	{
		printf("File Not Found : %s\n",filename);
		return 0;
	}

	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// No 100% errorchecking anymore!!!

	// read the width
	image->sizeX = getint (file);
	printf("Width of %s: %lu\n", filename, image->sizeX);

	// read the height 
	image->sizeY = getint (file);
	printf("Height of %s: %lu\n", filename, image->sizeY);

	// calculate the size (assuming 24 bits or 3 bytes per pixel).
	size = image->sizeX * image->sizeY * 3;

	// read the planes
	planes = getshort(file);
	if (planes != 1) 
	{
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}

	// read the bpp
	bpp = getshort(file);
	if (bpp != 24) 
	{
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	// read the data. 
	image->data = new GLubyte[size];
	if (image->data == NULL) 
	{
		printf("Error allocating memory for color-corrected image data");
		return 0;	
	}

	if ((i = fread(image->data, size, 1, file)) != 1) 
	{
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	// reverse all of the colors. (bgr -> rgb)
	for (i=0;i<size;i+=3) 
	{ 
		temp = image->data[i];
		image->data[i] = image->data[i+2];
		image->data[i+2] = temp;
	}

	// we're done.
	return 1;
}

// Load Bitmaps And Convert To Textures
void LoadGLTextures() {	
	// Load Texture
	Image *image1;
	Image *image2;

	// allocate space for texture
	image1 = new Image();
	image2 = new Image();
	if (image1 == NULL || image2 == NULL) 
	{
		printf("Error allocating space for image");
		exit(0);
	}


	//load picture from file
	if (!ImageLoad("floor.bmp", image1)) 
	{
		exit(1);
	}

	//load picture from file
	if (!ImageLoad("floor.bmp", image2)) 
	{
		exit(1);
	} 


	// Create Texture Name and Bind it as current
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)

	//Set Texture Parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smaller than texture

	// Load texture into OpenGL RC!
	glTexImage2D(GL_TEXTURE_2D,		// 2D texture
		0,					// level of detail 0 (normal)
		3,					// 3 color components
		image1->sizeX,		// x size from image
		image1->sizeY,		// y size from image
		0,					// border 0 (normal)
		GL_RGB,			// rgb color data order
		GL_UNSIGNED_BYTE,  // color componente types
		image1->data		// image data itself
		);


	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->sizeX, image2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->data);

	delete []image1->data;
	delete image1;
	delete []image2->data;
	delete image2;
};

void init()
{
	LoadGLTextures();
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_DEPTH_TEST);
}



void drawLeg()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tableMatAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tableMatDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tableMatSpec);
	glScalef(0.05,1,0.05);
	glEnable(GL_TEXTURE_GEN_S); // generate texture coordinates
	glEnable(GL_TEXTURE_GEN_T); // generate texture coordinates
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glutSolidCube(2.0);
	glDisable(GL_TEXTURE_GEN_S); // disable texture coordinates
	glDisable(GL_TEXTURE_GEN_T); // disable texture coordinates
	glPopMatrix();	
}

void drawTableTop()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tableMatAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tableMatDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tableMatSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, tableShine);
	glScalef(1.2,0.05,2.0);
	glEnable(GL_TEXTURE_GEN_S); // generate texture coordinates
	glEnable(GL_TEXTURE_GEN_T); // generate texture coordinates
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glutSolidCube(2.0);
	glDisable(GL_TEXTURE_GEN_S); // disable texture coordinates
	glDisable(GL_TEXTURE_GEN_T); // disable texture coordinates
	glPopMatrix();
}

void drawFloor()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, floorMat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floorMat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, floorMat);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6,-1,-6);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(6,-1,-6);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(6,-1,6);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6,-1,6);

	glEnd();

	glTranslatef(3,0,-3);

	glPopMatrix();
}

void drawTable()
{
	glPushMatrix();
	drawLeg();
	glTranslatef(2,0,0);
	drawLeg();
	glTranslatef(0,0,2);
	drawLeg();
	glTranslatef(-2,0,0);
	drawLeg();
	glTranslatef(1,1,-1);
	drawTableTop();
	glPopMatrix();
}

void drawOverhead()
{
	glPushMatrix();
	glTranslatef(0,6.5,0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0,1.0,1.0);
	glutWireSphere(0.3,10,10);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void drawLamp(GLfloat col1, GLfloat col2, GLfloat col3)
{
	GLfloat lampBulbMat[] = {col1, col2, col3, 0.50};

	glDisable(GL_TEXTURE_2D);

	// lamp base
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lampMat);
	glScalef(2,0.15,2);
	glutSolidCube(0.5);
	glPopMatrix();

	// lamp neck
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lampMat);
	glTranslatef(0,0.55,0);
	glScalef(0.25, 2.5, 0.25);
	glutSolidCube(0.5);
	glPopMatrix();

	// Bulb 
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lampBulbMat);
	glTranslatef(0,1.25,0);
	glutWireSphere(0.25,25,25);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

void drawFilter(GLfloat col1, GLfloat col2, GLfloat col3)
{
	GLfloat filterMat[] = {col1, col2, col3,  0.30};
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, filterMat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, filterMat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, filterMat);
	glVertex3f(-0.5,0,-0.5);
	glVertex3f(0.5,0,-0.5);
	glVertex3f(0.5,0,0.5);
	glVertex3f(-0.5,0,0.5);
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

void display()
{
	GLfloat overheadLightAmb[] = {lightInt,lightInt,lightInt, 1.0};
	GLfloat overheadLightDif[] = {lightInt,lightInt,lightInt, 1.0};
	GLfloat overheadLightSpec[] = {1,1,1, 1.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(viewer[0], 4.75, viewer[1], viewer[0] + camera[0], 4.5, viewer[1] + camera[1], 0.0, 1.0, 0.0);

	// overhead light
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, overheadLightDif);
	glLightfv(GL_LIGHT0, GL_AMBIENT, overheadLightAmb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, overheadLightSpec);
	drawOverhead();
	glPopMatrix();

	// floor
	drawFloor();

	// tables
	glPushMatrix();
	glTranslatef(0,0,2);
	drawTable();
	glTranslatef(0,0,-6);
	drawTable();
	glPopMatrix();


	// three lamps
	glPushMatrix();
	// Red
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lampRedLight);
	glTranslatef(1,1.15,-4.25);
	drawLamp(1.0,0.0,0.0);

	// Green
	glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lampGreenLight);
	glTranslatef(0.0,0.0,1.25);
	drawLamp(0.0, 1.0, 0.0);

	// Blue
	glLightfv(GL_LIGHT3, GL_POSITION, light3_pos);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, lampBlueLight);
	glTranslatef(0.0,0.0,1.25);
	drawLamp(0.0,0.0,1.0);
	glPopMatrix();

	// three filters
	glPushMatrix();
	glTranslatef(1, 1.25, 4.25);
	drawFilter(1.0,0.0,0.0);
	glTranslatef(0,.05,-1.3);
	drawFilter(0.0, 1.0, 0.0);
	glTranslatef(0,.10,-1.3);
	drawFilter(0.0,0.0,1.0);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q' || key == 27) { exit(0); }
	switch (key)
	{
	case '0': lightInt = 0.0;
		display();
		break;
	case '1': lightInt = 0.1;
		display();
		break;
	case '2': lightInt = 0.2;
		display();
		break;
	case '3': lightInt = 0.3;
		display();
		break;
	case '4': lightInt = 0.4;
		display();
		break;
	case '5': lightInt = 0.5;
		display();
		break;
	case '6': lightInt = 0.6;
		display();
		break;
	case '7': lightInt = 0.7;
		display();
		break;
	case '8': lightInt = 0.8;
		display();
		break;
	case '9': lightInt = 0.9;
		display();
		break;
	}

}

void keyboard2(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) 
	{
		//viewer[0] -= 1.0;
		angle -= 0.05f;
		camera[0] = sin(angle);
		camera[1] = -cos(angle);
	}

	if (key == GLUT_KEY_RIGHT)
	{
		//viewer[0] -= 1.0;
		angle += 0.05f;
		camera[0] = sin(angle);
		camera[1] = -cos(angle);
	}

	if (key == GLUT_KEY_UP)
	{
		viewer[0] += camera[0] * 0.50;
		viewer[1] += camera[1] * 0.50;
	}

	if (key == GLUT_KEY_DOWN)
	{
		viewer[0] -= camera[0] * 0.50;
		viewer[1] -= camera[1] * 0.50;
	}

	display();
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* Uncomment for frustum
	if (w <= h)
	glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h/ (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, 2.0, 20.0);
	else
	glFrustum(-2.0, 2.0, -2.0 * (GLfloat)w/ (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, 2.0, 20.0);
	*/

	gluPerspective(45.0, 1, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(wWidth, wHeight);
	glutInitWindowPosition(150,50);
	glutCreateWindow("Ooooooh, Roomy"); 
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard2); 

	glutMainLoop();
}
