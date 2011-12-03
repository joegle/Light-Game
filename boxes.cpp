
class box
{
public:
  box(double,double);
  void draw();
  
  bool dude; //does the dude have it
  double x;
  double y;
  double angle;

  color c;
};

box::box(double xx,double yy)
{
  dude=false;
  x=xx;
  y=yy;
  angle=0;
  c=randomColor();
}

void box::draw()
{

  glPushMatrix();
  if(!dude)
    {
      glTranslated(x*20,0,y*20);
      glRotated(angle, 0, 1, 0);
      glScaled(0.25,0.25,0.25);
      glTranslated(0,1,0);
      glColor3f(c.r,c.g,c.b);
      glutSolidTeapot(1);
  }
  else
    {

      glTranslated(x*20,0,y*20);
      glRotated(angle, 0, 1, 0);
      glScaled(0.25,0.25,0.25);
      glTranslated(0,1,0);
      glColor3f(c.r,c.g,c.b);
      glutSolidTeapot(1);
    }

  glPopMatrix();
  
}
