#include <fstream>

using namespace std;


// This temp for testing
void processfile(){

  ifstream level_file ("level.txt");
  if (level_file.is_open())
  {

    // read in the floor dimensions (30x30 max)
    level_file >> world.x;
    level_file >> world.y;

    // fill in the wall data
    for(int i=0;i<world.x;i++)
      for(int j=0;j<world.y;j++)
	  level_file >> world.walls[i][j];



    level_file.close();
  }
  else cout << "Unable to open level.txt which stores the level information";
}
