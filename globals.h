
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

double world_time=0;

int world_y=1;
int world_x=1;

struct Object {
  double x;
  double y;
  double z;
  double o; // Overhead direction (North,East)
  double s;  // Tilt of head
};

Object player;
