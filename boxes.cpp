class box
{
public:
  box(double,double);
  void draw();
  
  double x;
  double y;

  color c;
};

box::box(double xx,double yy)
{
  x=xx;
  y=yy;
  c=randomColor();
}

void box::draw()
{

  glPushMatrix();


  glTranslated(x*20,0,y*20);
  glScaled(0.25,0.25,0.25);
  glTranslated(0,1,0);
  glColor3f(c.r,c.g,c.b);
  glutSolidTeapot(1);

  glPopMatrix();

  
}
