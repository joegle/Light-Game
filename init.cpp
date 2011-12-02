#include <fstream>

using namespace std;


// This temp for testing
void processfile(){

  ifstream level_file ("level.txt");
  if (level_file.is_open())
  {

    // read in the floor dimensions (30x30 max)
    level_file >> world_x;
    level_file >> world_y;

    // fill in the wall data
    for(int i=0;i<world_x;i++)
      for(int j=0;j<world_y;j++)
	  level_file >> walls[i][j];
      

    level_file.close();
  }
  else cout << "Unable to open level.txt which stores the level information";
}
