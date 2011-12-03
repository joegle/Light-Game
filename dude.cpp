#include <iostream>
#include <vector>

using namespace std;

class dude
{
public:
  dude(world*);
  void foo();
  void wf();
  void look();
  void goForward();
  void goBackward();
  void doSomething();
  void drop();
  
  void turn(double x);
  void setPosition(double a,double b,double c);

  //position (specifically the eye coord)
  double x;
  double y;
  double z;
  
  double o; //overhead angle like compass direction
  double s; //side angle; tilt of head
  
private:
  vector<bin> _bins;
  double forward_step;
  double backward_step;
  world* w;
  bool carrying;
  box load;
};

dude::dude(world* ww)
{
  x = 0.5;
  y = 0.5;
  z = 1;
  forward_step = 1;
  backward_step = 1;
  w = ww;
  carrying = false;
}

void dude::setPosition(double a,double b,double c)
{
  x=a; 
  y=b; 
  z=c;
}

void dude::turn(double amt)
{
  o+=amt;
}



void dude::look()
{
  //  cout << x << " " << y << " " << z <<endl;
  gluLookAt(x,z,y,
	    x+sin(f(o))*cos(f(s)),
	    z+sin(f(s)),
	    y+cos(f(o))*cos(f(s)),
	    0,1,0);

  if(carrying)
    {
      double dis=2;
      double holdX = (x + dis*sin(f(o))*cos(f(s)))/20; //      double holdX = (x + dis*sin(f(o)))/20;
      double holdY = (y + dis*cos(f(o))*cos(f(s)))/20;

      load.x=holdX;
      load.y=holdY;
      load.z = 0.4 + sin(f(s));

      load.angle=o;
      load.drawHeld();
    }
  
}

// If dude is holding a cube, drop it down, releasing it from possession
void dude::drop()
{
  if(carrying)
    {
      carrying =false;
      load.dude=false;
      for(int i=0;i<w->_boxes.size();i++)
	{
	  if(w->_boxes[i].dude)
	    {
	      // Dude has member 'load' which is a dummy clone of the picked up cube
	      //   we transfer the clones data into the "real" one which will now appear in the level since its 'dude' parameter indicates that it is not being held. box::draw() will draw if 'dude' is false.
	      w->_boxes[i].x=load.x;
	      w->_boxes[i].y=load.y;
	      w->_boxes[i].angle=load.angle;

	      w->_boxes[i].dude=false;
	      w->checkBins();
	    }
	}
      w->checkWin();
    }
}

// This is the main interaction of the dude. 
// If the dude is in range of object this will do something with it:
//   + Toggle a switch
//   + Pick up a box if not already carrying
//   + Drop box if currently carrying one
void dude::doSomething(){
  cout<<"doSomething"<<endl;

  // Parameters for activation zone
  double radius=0.1;
  double dis=1;
  double rangeX = (x + dis*sin(f(o)))/20;
  double rangeY = (y + dis*cos(f(o)))/20;

  // Uncomment this to see where the center of the activation circle is
  //w->addBox(box(rangeX,rangeY));

  if(!carrying)
    {
      for(int i=0; !carrying && i<w->_boxes.size();i++)
	{
	  if( !(w->_boxes[i].placed) && 
	     distance(rangeX,rangeY,w->_boxes[i].x, w->_boxes[i].y) < radius)
	    {
	      //	      w->_boxes[i].c=randomColor();
	      w->_boxes[i].dude = true;
	      load = w->_boxes[i];
	      load.dude=true;

	      carrying = true;
	    }
	}
    }
  else // currently has load
    {
      drop();
      
    }
}

void dude::goForward(){

  int wall = w-> walls[(int)x/20][(int)y/20];

  signed int fx=x/20;
  signed int fy=y/20;

  int ox =x;
  int oy =y;

  y+= forward_step*cos(f(o));
  x+= forward_step*sin(f(o));

  signed int dx=fx-(int)x/20;
  signed int dy=fy-(int)y/20;


  if(wall & 8 && dx<0)
    {
      x=ox;
      y=oy;
    }

  if(wall & 4 && dy>0)
    {
      x=ox;
      y=oy;
    }

  if(wall & 2 && dy<0)
    {
      x=ox;
      y=oy;
    }

  if(wall & 1 && dx>0)
    {
      x=ox;
      y=oy;
    }

}

// Wall detection not implemented here yet
void dude::goBackward(){
  y += -1*backward_step*cos(f(o));
  x += -1*backward_step*sin(f(o));
}
