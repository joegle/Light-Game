#include "dude.h"

dude::dude(world* ww)
{
  x = 2.5;
  y = 2.5;
  z = 2;
  forward_step = 1;
  backward_step = 1;
  w = ww;
  carrying = false;
  mouseWarp = false;

  // Dude's lamp init
  lampOil = 100.00;
  lamp = GL_LIGHT7;
  lampState = false;
  lampAmb[0] = 1.0;
  lampAmb[1] = 1.0;
  lampAmb[2] = 1.0;
  lampAmb[3] = 1.0;
  lampDif[0] = 1.0;
  lampDif[1] = 1.0;
  lampDif[2] = 1.0;
  lampDif[3] = 1.0;
  lampSpec[0] = 1.0;
  lampSpec[1] = 1.0;
  lampSpec[2] = 1.0;
  lampSpec[3] = 1.0;
  lampPos[3] = 1.0; // Set the dude's light as positional
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
  // Dude no longer does the gluLookAt() himself. This has been pushed out to game.cpp for lighting stuff
  if(carrying)
    {
      double dis=2;
      double holdX = (x + dis*sin(f(o))*cos(f(s)))/20; //      double holdX = (x + dis*sin(f(o)))/20;
      double holdY = (y + dis*cos(f(o))*cos(f(s)))/20;

      load.x=holdX;
      load.y=holdY;
      load.z = 1 + sin(f(s));

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
  // Parameters for activation zone
  double radius=0.1;
  double dis=1;
  double rangeX = (x + dis*sin(f(o)))/20;
  double rangeY = (y + dis*cos(f(o)))/20;

  // Uncomment this to see where the center of the activation circle is
  //w->addBox(box(rangeX,rangeY));

  if(!carrying)
    {

      // look for boxes to carry
      for(int i=0; !carrying && i<w->_boxes.size();i++)
	{
	  if( !(w->_boxes[i].placed) && 
	     distance(rangeX,rangeY,w->_boxes[i].x, w->_boxes[i].y) < radius)
	    {
	      // w->_boxes[i].c=randomColor();
	      w->_boxes[i].dude = true;
	      load = w->_boxes[i];
	      load.dude=true;

	      carrying = true;
	    }
	}

      // look for toggles to flick
      for(int i=0; !carrying && i<w->_toggles.size();i++)
	{
	  if( distance(rangeX,rangeY,w->_toggles[i].x, w->_toggles[i].y) < radius )
	    {
        for (int j=0; j < w->_toggles.size(); j++)
          w->_toggles[j].state = 0;
          
          w->_toggles[i].flick();

	    }
	}

    }
  else // currently has load
    {
      drop();
    }
}

void dude::strafeLeft() {
  this->o += 90;
  goForward();
  this->o -= 90;
}

void dude::strafeRight() {
  this->o -= 90;
  goForward();
  this->o += 90;
}

void dude::goForward(){
  
  int wall = w-> walls[(int)x/20][(int)y/20];
  
  int fx=x/20;
  int fy=y/20;

  double ox = x;
  double oy = y;

  lampPos[0] = x;
  lampPos[1] = z;
  lampPos[2] = y;
  y+= forward_step*cos(f(o));
  x+= forward_step*sin(f(o));

  if(wall & 4 && (x>(((fx+1)*20)-2)))
    {
      x=ox;
      y=oy;
    }

  if(wall & 2 && (y<((fy*20))+2))
    {
      x=ox;
      y=oy;
    }

  if(wall & 8 && (y>(((fy+1)*20)-2)))
    {
      x=ox;
      y=oy;
    }

  if(wall & 1 && (x<((fx*20))+2))
    {
      x=ox;
      y=oy;
    }
}

// Wall detection not implemented here yet
void dude::goBackward(){
  this->o -= 180;
  goForward();
  this->o += 180;
}

// The dude's lamp will ALWAYS be GL_LIGHT7 (the last one available)
void dude::setLamp() {
  //cout << lampOil << endl;
  glLightfv(lamp, GL_AMBIENT, lampAmb);
  glLightfv(lamp, GL_DIFFUSE, lampDif);
  glLightfv(lamp, GL_SPECULAR, lampSpec);
  //GLfloat attenuation = 1.5 - (lampOil / 100);
  GLfloat attenuation = .2;
  #if defined (_MSC_VER) 
	attenuation /= 10;
  #endif 
  glLightf(lamp, GL_LINEAR_ATTENUATION,attenuation);

 if (lampOil <= 0)
  lampState = false;

 if (lampState)
 {
  glLightfv(lamp, GL_POSITION, lampPos);
  glEnable(lamp);
 }
 else
  glDisable(lamp);

}
