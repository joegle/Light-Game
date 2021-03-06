#ifndef WORLD
#define WORLD

#include <iostream>
#include <vector>
#include <utility>
#include "boxes.h"
#include "bins.h"
#include "lights.h"
#include "toggles.h" 
#include "spikeTrap.h"

using namespace std;

class world
{
public:
  world();
  void drawWorld();
  void setDimensions(int xx,int yy);
  unsigned int getint(FILE *fp);
  unsigned short getshort(FILE* fp);
  int ImageLoad(char *filename, Image *image);
  void LoadGLTextures();
  void drawLights();
  void drawWalls();
  void drawToggles();
  void drawBoxes();
  void drawBins();
  void drawFloor();
  void drawCeiling();
  void drawSpikeTraps();
  void tick();
  void syncBinsBoxes();
  void checkBins();
  void checkWin();
  
  void addLight(light l);
  void addToggle(toggle t);
  void addBox(box box);
  void addBin(bin b);
  void addSpikeTrap(spikeTrap st);
  void drawWall(double x1,double y1, double x2, double y2);

  int x;
  int y;
  int walls[30][30];  // [row][col]
  double time;
  GLuint texture[3];
  bool won;
  bool loss;
  double timeProgressed;

  vector<light> _lights;
  vector<toggle> _toggles;
  vector<box> _boxes;
  vector<bin> _bins;
  vector<spikeTrap> _spikeTraps;
private:

};

#include "world.cpp"
#endif
