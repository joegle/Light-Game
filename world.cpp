#include "world.h"

world::world()
{
  for(int i=0;i<30;i++)
  {
      circuit[0][i]=((int)r(0,20))%2;
  }
}

void world::drawWorld()
{
  drawFloor();
  drawCeiling();
  drawWalls();
  drawBoxes();
  drawToggles();
  drawBins();
  drawLights();
}

void world::setDimensions(int xx,int yy)
{
  x = xx;
  y = yy;
}

void world::drawFloor()
{
  glEnable(GL_TEXTURE_2D);
	GLfloat floorAmbient[] = {.3,.3,.3,1};
	GLfloat floorSpec[] = { .3,.3,.3,1};
	GLfloat floorDiff[] = { .3,.3,.3,1};
  glPushMatrix();
    glTranslatef(x * 10, 0 ,y * 10);
    glScalef(x * 10, 0 , y * 10);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,floorAmbient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,floorSpec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,floorDiff);  
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
      glTexCoord2f(-1.0, 1.0);   glVertex3f(-1.0f,0, 1.0f);     
      glTexCoord2f( 1.0, 1.0);   glVertex3f( 1.0f,0, 1.0f);     
      glTexCoord2f( 1.0,-1.0);   glVertex3f( 1.0f,0,-1.0f);     
      glTexCoord2f(-1.0,-1.0);   glVertex3f(-1.0f,0,-1.0f);  
   glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void world::drawCeiling()
{
  glPushMatrix();
    glTranslatef(0, 4, 0);
    drawFloor();
  glPopMatrix();
}

// Checks if each bin has its bin and sets the bin and box with its filled or placed value
void world::checkBins()
{
  // distance margin of error
  double radius=0.05;
  for(int i = 0; i <_bins.size(); i++)
    {

      // This line will put all boxes in their bins
      // _boxes[i].x=_bins[i].x;      _boxes[i].y=_bins[i].y;


   if(distance(_boxes[i].x,
	    _boxes[i].y, 
		  _bins[i].x,
		  _bins[i].y) < radius)
	{
	  _bins[i].filled = true;
	  _boxes[i].placed = true;
	}
      else
	{
	  _bins[i].filled = false;
	  _boxes[i].placed = false;

	}
    }

}

void world::updateCircuit()
{
  // (p + q + r + q r) mod 2
  for(int i=0;i<30;i++)
    circuit[0][i]= _toggles[i].state;

  bool p,q,r;
  for(int i=1;i<29;i++)
    {
      for(int j=0;j<30;j++)
	{
	  p = circuit[i-1][(j-1)%30];
	  q = circuit[i-1][(j)];
	  r = circuit[i-1][(j+1)%30];
	  circuit[i][j] = (p + q + r + q*r) %2;
	}
    }

  for(int i=0;i<30;i++)
    {
    for(int j=0;j<30;j++)
      {
	cout<<circuit[i][j]<< " ";
      }
    cout<<endl;
    }
}

void world::checkWin()
{
  
  for(int i = 0; i <_bins.size(); i++)
    {
      if(!_boxes[i].placed)
	cout<<0;
      else
	cout<<1;
    }
  cout<<endl;  

}

// makes bins and boxes match colors
//  _bins[X] goes with _boxes[X]
void world::syncBinsBoxes()
{
  for(int i = 0; i <_boxes.size(); i++)
    {
      _boxes[i].c=_bins[i].c;
    }
}

// draw wall from (x1,y2) to (x2,y2)
void world::drawWall(double x1,double y1, double x2, double y2)
{
  glEnable(GL_TEXTURE_2D);
  GLfloat floorAmbient[] = {.3,.3,.3,1};
  GLfloat floorSpec[] = { .3,.3,.3,1};
  GLfloat floorDiff[] = { .3,.3,.3,1};
  
  glPushMatrix();
  
  // This is how it is. It works
  x1*=20;
  x2*=20;
  y1*=20;
  y2*=20;
  
  int h=4; // height of wall
  
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,floorAmbient);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,floorSpec);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,floorDiff);
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glBegin(GL_QUADS);
    glTexCoord2f(0, 0 ); glVertex3f(x1,h,y1); 
	  glTexCoord2f( 1, 0); glVertex3f(x1,0,y1);
	  glTexCoord2f( 1,1); glVertex3f(x2,0,y2);
	  glTexCoord2f(0,1);  glVertex3f(x2,h,y2);
  glEnd();   
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void world::drawWalls()
{
  int part;
  for(int i=0;i<x;i++)
    for(int j=0;j<y;j++)
      {
	part=walls[i][j];

	if(part & 1 )
	  drawWall(i,j,i,j+1);

	if(part & 2 )
	  drawWall(i,j,i+1,j);

	if(part & 4 )
	  drawWall(i+1,j+1,i+1,j);

	if(part & 8 )
	  drawWall(i+1,j+1,i,j+1);

      }

  // Draw Outer Walls
  drawWall(0,0,0,y);
  drawWall(0,0,x,0);
  drawWall(0,y,x,y);
  drawWall(x,0,x,y);
}

void world::drawBoxes()
{
	for(int i = 0; i <_boxes.size(); i++)
	{
	  _boxes[i].draw();
	}
}

void world::drawLights()
{
  for(int i = 0; i < _lights.size(); i++)
  {
    if(_toggles[i].state)
	   {
	      _lights[i].draw();
	   }
     _lights[i].toggleLight(i, _toggles[i].state);
  }

  cout<<endl;
}


void world::drawBins()
{
	for(int i = 0; i < _bins.size(); i++)
	{
		_bins[i].draw();
	}
}

void world::drawToggles()
{

  for(int i = 0; i < _toggles.size(); i++)
    {
      _toggles[i].draw();
    }
  
}


void world::addLight(light l)
{

	_lights.push_back(l);
}


void world::addToggle(toggle t)
{
	_toggles.push_back(t);
}

void world::addBox(box b)
{
	_boxes.push_back(b);
	//	cout<<" "<<b.x<<" "<<b.y<<endl;
		
}

void world::addBin(bin b)
{
	_bins.push_back(b);
}


// Make time proceed
void world::tick()
{
  time += 0.001;
}


/*
* getint and getshort are help functions to load the bitmap byte by byte on 
* SPARC platform.
* Aquired from xv bitmap load routine because the original bmp loader didn't
* work on 
* I've tried to change as little code as possible.
*/

unsigned int world::getint(FILE *fp)
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

unsigned short world::getshort(FILE* fp)
{
	int c, c1;

	//get 2 bytes
	c = getc(fp);  
	c1 = getc(fp);

	return ((unsigned int) c) + (((unsigned int) c1) << 8);
}

// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.

int world::ImageLoad(char *filename, Image *image) 
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
void world::LoadGLTextures() {	
	// Load Texture
	Image *image1;

	// allocate space for texture
	image1 = new Image();
	if (image1 == NULL) 
	{
		printf("Error allocating space for image");
		exit(0);
	}

	//load picture from file
	if (!ImageLoad("img/floor.bmp", image1)) 
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

	//copied from above
	Image *image2;

	// allocate space for texture
	image2 = new Image();
	if (image2 == NULL) 
	{
		printf("Error allocating space for image");
		exit(0);
	}

	//load picture from file
	if (!ImageLoad("img/wood.bmp", image2)) 
	{
		exit(1);
	}        

	// Create Texture Name and Bind it as current
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);   // 2d texture (x and y size)

	//Set Texture Parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smaller than texture

	// Load texture into OpenGL RC!
	glTexImage2D(GL_TEXTURE_2D,		// 2D texture
				 0,					// level of detail 0 (normal)
				 3,					// 3 color components
				 image2->sizeX,		// x size from image
				 image2->sizeY,		// y size from image
				 0,					// border 0 (normal)
				 GL_RGB,			// rgb color data order
				 GL_UNSIGNED_BYTE,  // color componente types
				 image2->data		// image data itself
				 );
	//copied from above
	Image *image3;

	// allocate space for texture
	image3 = new Image();
	if (image3 == NULL) 
	{
		printf("Error allocating space for image");
		exit(0);
	}

	//load picture from file
	if (!ImageLoad("img/stone.bmp", image3)) 
	{
		exit(1);
	}        

	// Create Texture Name and Bind it as current
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);   // 2d texture (x and y size)

	//Set Texture Parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smaller than texture

	// Load texture into OpenGL RC!
	glTexImage2D(GL_TEXTURE_2D,		// 2D texture
				 0,					// level of detail 0 (normal)
				 3,					// 3 color components
				 image3->sizeX,		// x size from image
				 image3->sizeY,		// y size from image
				 0,					// border 0 (normal)
				 GL_RGB,			// rgb color data order
				 GL_UNSIGNED_BYTE,  // color componente types
				 image3->data		// image data itself
				 );
};
