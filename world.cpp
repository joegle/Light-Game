#include "world.h"

void world::drawWorld()
{
  drawFloor();
  drawWalls();
  drawBoxes();
  drawToggles();
  drawBins();

  
  //drawLights();

  
}

void world::setDimensions(int xx,int yy)
{
  x = xx;
  y = yy;
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
/*
void world::drawLights()
{
	for(int i = 0; i < _lights.size(); i++)
	{
	  _lights[i].draw();
	}
}
*/
// draw wall from (x1,y2) to (x2,y2)
void drawWall(double x1,double y1, double x2, double y2)
{
  glPushMatrix();
  
  // This is how it is. It work  x1*=20;
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

void world::drawToggles()
{

	for(int i = 0; i < _toggles.size(); i++)
	{

	  _toggles[i].draw();
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
	for(int i = 0; i < _bins.size(); i++)
	{
		_bins[i].draw();
	}
}
/*
void world::addLight(Lights light)
{
	_lights.push_back(light);
}*/



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
