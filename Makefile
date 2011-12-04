LIBS = -lglut -lGLU

game: game.cpp globals.h controls.h objects.cpp init.cpp utils.cpp world.cpp dude.cpp boxes.cpp bins.cpp toggles.h toggles.cpp level.txt
	g++ -o game $(LIBS) game.cpp 

test:
	g++ -o test $(LIBS) test.cpp
