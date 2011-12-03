#include <iostream>
#include <vector>
#include "boxes.cpp"

using namespace std;



class lights
{
public:
  void draw(){cout<<"draw light";};
};


class switches
{
public:
  void draw(){cout<<"draw switch";};
};


class bins
{
public:
  void draw(){cout<<"draw switch";};
};


class world
{
public:
  void drawWorld();
  void setDimensions(int xx,int yy);
  void drawLights();
  void drawWalls();
  void drawSwitches();
  void drawBoxes();
  void drawBins();
  void drawFloor();
  void tick();
  
  void addLight(lights light);
  //  void addWall();
  void addSwitch(switches newSwitch);
  void addBox(box box);
  void addBin(bins bin);

  int x;
  int y;
  int walls[30][30];  // [row][col]
  double time;

  vector<lights> _lights;
  vector<switches> _switches;
  vector<box> _boxes;
  vector<bins> _bins;
 
private:

};


void world::drawWorld()
{
  drawFloor();
  drawWalls();
  drawBoxes();

  /*
  drawLights();
  drawSwitches();
  drawBins();
  */
}

void world::setDimensions(int xx,int yy)
{
  x=xx;
  y=yy;
}

void world::drawFloor()
{
  glPushMatrix();

  glTranslatef(x * 10, 0 ,y * 10);
  glScalef(x * 10, 0 , y * 10);
  
  glColor3f(1,0,1);

  glBegin(GL_QUADS);
  glTexCoord2f(-1.0, 1.0);   glVertex3f(-1.0f,0, 1.0f);     
  glTexCoord2f( 1.0, 1.0);   glVertex3f( 1.0f,0, 1.0f);     
  glTexCoord2f( 1.0,-1.0);   glVertex3f( 1.0f,0,-1.0f);     
  glTexCoord2f(-1.0,-1.0);   glVertex3f(-1.0f,0,-1.0f);     
  glEnd();   

  glPopMatrix();



	//draw an appropriate floor here
}

void world::drawLights()
{
	for(int i = 0; i < _lights.size(); i++)
	{
	  _lights[i].draw();
	}
}

// draw wall from (x1,y2) to (x2,y2)
void drawWall(double x1,double y1, double x2, double y2)
{
  glPushMatrix();
  
  // This is how it is. It works
  x1*=20;
  x2*=20;
  y1*=20;
  y2*=20;
  
  glColor3f(0,0,1);

  int h=4; // height of wall

  glBegin(GL_QUADS);
    glVertex3f(x1,h,y1);     
    glVertex3f(x1,0,y1);     
    glVertex3f(x2,0,y2);     
    glVertex3f(x2,h,y2);     
  glEnd();   

  glPopMatrix();
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



}

void world::drawSwitches()
{
	for(int i = 0; i < _lights.size(); i++)
	{
		_switches[i].draw();
	}
}

void world::drawBoxes()
{
	for(int i = 0; i <_boxes.size(); i++)
	{
		_boxes[i].draw();
	}
}

void world::drawBins()
{
	for(int i = 0; i < _lights.size(); i++)
	{
		_bins[i].draw();
	}
}

void world::addLight(lights light)
{
	_lights.push_back(light);
}



void world::addSwitch(switches newSwitch)
{
	_switches.push_back(newSwitch);
}

void world::addBox(box b)
{
	_boxes.push_back(b);
	//	cout<<" "<<b.x<<" "<<b.y<<endl;
		
}

void world::addBin(bins bin)
{
	_bins.push_back(bin);
}


void world::tick()
{
  time += 0.001;
}
