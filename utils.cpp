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


color randomColor(){
  color c;
  c.b=(float)rand()/(float)RAND_MAX;
  c.r=(float)rand()/(float)RAND_MAX;
  c.g=(float)rand()/(float)RAND_MAX;
  return c;
}
