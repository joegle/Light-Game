LIBS = -lglut -lGLU

game: game.cpp globals.h controls.h objects.cpp init.cpp utils.cpp world.cpp dude.cpp boxes.cpp bins.cpp
	g++ -o game $(LIBS) game.cpp 
