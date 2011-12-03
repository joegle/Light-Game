// Extra functions that are needed

struct color{
  double r;
  double g;
  double b;
  double a;
};

// radian to degree
float f(float a){
  return a*3.14/180;
}

// Some one should make this so that each rgb value is discrete
color randomColor(){
  color c;
  c.b=(float)rand()/(float)RAND_MAX;
  c.r=(float)rand()/(float)RAND_MAX;
  c.g=(float)rand()/(float)RAND_MAX;
  return c;
}

double distance(double x1,double y1,double x2,double y2)
{
  return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
