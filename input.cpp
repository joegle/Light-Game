#include <iostream>

using namespace std;

void createWorld();
void readGrid();
void readWalls();
void readCubes();
void readBins();
void readLights();
void readSwitches();
void createGrid(double x, double y);
void createWall(double x, double y, double bin);
void createCube(double x, double y, double z, double r, double g, double b);
void createBin(double x, double y, double z, double r, double g, double b, double linkage);
void createLight(double x, double y, double z, double r, double g, double b);
void createSwitch(double x, double y, double z, double r, double g, double b, double linkage);

int main()
{
	createWorld();
}

void createWorld()
{
	//make the grid
	readGrid();

	//make the walls
	readWalls();

	//make the cubes
	readCubes();

	//make the bins
	readBins();
	
	//make the lights
	readLights();

	//make the switches
	readSwitches();
}

void readGrid()
{
	double x,y;
	cin >> x >> y;
	createGrid(x,y);
}

void readWalls()
{
	double n, x, y, bin;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> x >> y >> bin;
		createWall(x,y,bin);
	}
}

void readCubes()
{
	double n,x,y,z,r,g,b;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> x >> y >> z >> r >> g >> b;
		createCube(x,y,z,r,g,b);
	}
}

void readBins()
{
	double n,x,y,z,r,g,b,linkage;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> x >> y >> z >> r >> g >> b >> linkage;
		createBin(x,y,z,r,g,b,linkage);
	}
}

void readLights()
{
	double n,x,y,z,r,g,b;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> x >> y >> z >> r >> g >> b;
		createLight(x,y,z,r,g,b);
	}
}

void readSwitches()
{
	double n,x,y,z,r,g,b,linkage;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> x >> y >> z >> r >> g >> b >> linkage;
		createSwitch(x,y,z,r,g,b,linkage);
	}
}


void createGrid(double x, double y)
{
	cout << "Stub for create grid." << endl;
	cout << "Inputs were the following: " << endl;
	cout << "x: " << x << "\ny: " << y << endl;
	cout << endl;
}

void createWall(double x, double y, double bin)
{
	cout << "Stub for create wall." << endl;
	cout << "Inputs were the following: " << endl;
	cout << "x: " << x << "\ny: " << y << "\nbin: " << bin << endl;
	cout << "    The value represented by bin creates the following walls:" << endl;
	if(bin - 8 >= 0)
	{
		bin-=8;
		cout << "    Top wall created." << endl;
	}
	if(bin - 4 >= 0)
	{
		bin-=4;
		cout << "    Right wall created." << endl;
	}
	if(bin - 2 >= 0)
	{
		bin-=2;
		cout << "    Bottom wall created." << endl;
	}
	if(bin - 1 >= 0)
	{
		bin-=1;
		cout << "    Left wall created." << endl;
	}
	cout << endl;
}

void createCube(double x, double y, double z, double r, double g, double b)
{
	cout << "Stub for create cube." << endl;
	cout << "Inputs were the following: " << endl;
	cout << "x: " << x << "\ny: " << y << "\nr: " << r << "\ng: " << g << "\nb: " << b << endl;
	cout << endl;
}

void createBin(double x, double y, double z, double r, double g, double b, double linkage)
{
	cout << "Stub for create bin." << endl;
	cout << "Inputs were the following: " << endl;
	cout << "x: " << x << "\ny: " << y << "\nr: " << r << "\ng: " << g << "\nb: " << b << "\nlinkage: " << linkage << endl;
	cout << endl;
}

void createLight(double x, double y, double z, double r, double g, double b)
{
	cout << "Stub for create light." << endl;
	cout << "Inputs were the following: " << endl;
	cout << "x: " << x << "\ny: " << y << "\nr: " << r << "\ng: " << g << "\nb: " << b << endl;
	cout << endl;
}

void createSwitch(double x, double y, double z, double r, double g, double b, double linkage)
{
	cout << "Stub for create switch." << endl;
	cout << "Inputs were the following: " << endl;
	cout << "x: " << x << "\ny: " << y << "\nr: " << r << "\ng: " << g << "\nb: " << b << "\nlinkage: " << linkage << endl;
	cout << endl;
}

/*
input file should be as follows
2 2							grid size: x y
4							num walls: n
0 0 0						wall details: x y binaryRepresentationOfWalls	
0 1 0						// top right bottom left
0 2 0						// rockin it css style
0 3 0
1							num cubes: n
0 0 0 1 0 0					cube details: x y z r g b
1							num bins: n	
0 0 0 1 0 0 0				bin details: x y z r g b linkedToCubeId
1							num lights: n
0 0 1 1 1 1					light details: x y z r g b
1							num switches: n
1 1 0 1 1 1 0				switch details: x y z r g b linkedToBinId

*/
