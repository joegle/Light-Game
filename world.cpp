#include <iostream>
#include <vector>

using namespace std;

class lights
{
public:
	void draw();
};

class walls
{
public:
	void draw();
};

class switches
{
public:
	void draw();
};

class boxes
{
public:
	void draw();
};

class bins
{
public:
	void draw();
};


class world
{
public:
	void drawWorld();
	void drawLights();
	void drawWalls();
	void drawSwitches();
	void drawBoxes();
	void drawBins();
	void drawFloorCeiling();

	void addLight(lights light);
	void addWall(walls wall);
	void addSwitch(switches newSwitch);
	void addBox(boxes box);
	void addBin(bins bin);

private:
	vector<lights> _lights;
	vector<walls> _walls;
	vector<switches> _switches;
	vector<boxes> _boxes;
	vector<bins> _bins;
	int x;
	int y;
};

void world::drawWorld()
{
	drawFloorCeiling();
	drawLights();
	drawWalls();
	drawSwitches();
	drawBoxes();
	drawBins();
}

void world::drawFloorCeiling()
{
	//draw an appropriate floor here
}

void world::drawLights()
{
	for(int i = 0; i < _lights.size(); i++)
	{
		_lights[i].draw();
	}
}

void world::drawWalls()
{
	for(int i = 0; i < _lights.size(); i++)
	{
		_walls[i].draw();
	}
}

void world::drawSwitches()
{
	for(int i = 0; i < _lights.size(); i++)
	{
		_switches[i].draw();
	}
}

void world::drawBoxes()
{
	for(int i = 0; i < _lights.size(); i++)
	{
		_boxes[i].draw();
	}
}

void world::drawBins()
{
	for(int i = 0; i < _lights.size(); i++)
	{
		_bins[i].draw();
	}
}

void world::addLight(lights light)
{
	_lights.push_back(light);
}

void world::addWall(walls wall)
{
	_walls.push_back(wall);
}

void world::addSwitch(switches newSwitch)
{
	_switches.push_back(newSwitch);
}

void world::addBox(boxes box)
{
	_boxes.push_back(box);
}

void world::addBin(bins bin)
{
	_bins.push_back(bin);
}

