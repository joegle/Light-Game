#ifndef WORLD
#define WORLD

#include <iostream>
#include <vector>
#include "boxes.h"
#include "bins.h"
#include "toggles.h"
#include "lights.h"

using namespace std;

class world
{
public:
  void drawWorld();
  void setDimensions(int xx,int yy);
  //void drawLights();
  void drawWalls();
  void drawToggles();
  void drawBoxes();
  void drawBins();
  void drawFloor();
  void tick();
  void syncBinsBoxes();
  void checkBins();
  void checkWin();
  
  //void addLight(Lights light);
  //  void addWall();
  void addToggle(toggle t);
  void addBox(box box);
  void addBin(bin b);

  int x;
  int y;
  int walls[30][30];  // [row][col]
  double time;

  //vector<Lights> _lights;
  vector<toggle> _toggles;
  vector<box> _boxes;
  vector<bin> _bins;
 
private:

};

#include "world.cpp"
#endif
