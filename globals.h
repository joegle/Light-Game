#ifndef GLOBALS
#define GLOBALS

#include "world.h"
#include "dude.h"
#include "utils.h"

// Globals will be here
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };


world world;
dude dude(&world);



int width;   // Current width of window; value is maintained by reshape().
int height;  // Current height of window; value is maintained by reshape().
bool oilGodMode = false;


//From example
/* storage for two texture  */

#endif
