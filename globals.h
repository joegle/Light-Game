// Globals will be here


GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

double world_time=0;

// This is the size of the whole level
// Try running and pressing j/k/u/i keys
int world_x=1;
int world_y=1;


struct Object {
  double x;
  double y;
  double z;
  double o; // Overhead direction (North,East)
  double s;  // Tilt of head
};

Object player;
