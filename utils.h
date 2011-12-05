#ifndef UTILS
#define UTILS

// Extra functions that are needed
#include <iostream>
using namespace std;

class color{
public:
  double r;
  double g;
  double b;
  double a;
};

// radian to degree
float f(float a){
  return a*3.14/180;
}


//http://stackoverflow.com/a/686376/164617
float r(float a, float b)
{
return ((b-a)*((float)rand()/RAND_MAX))+a;
}

// Some one should make this so that each rgb value is discrete
color randomColor(){
  color c;

  c.r=(float)rand()/(float)RAND_MAX;
  c.b=(float)rand()/(float)RAND_MAX;
  c.g= (float)rand()/(float)RAND_MAX;


  return c;
}

double distance(double x1,double y1,double x2,double y2)
{
  
  double dx,dy;
  dx=abs(x2-x1);
  dy=abs(y2-y1);
  
  //  cout<<dx<<" "<<dy<<endl;
  
  return sqrt(dx*dx + dy*dy);
}

struct Image 
{
	unsigned long sizeX;
	unsigned long sizeY;
	GLubyte *data;
};

#endif
