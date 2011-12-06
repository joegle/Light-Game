LIBS = -lglut -lGLU

game: game.cpp globals.h controls.h objects.cpp init.h utils.h world.cpp dude.cpp boxes.cpp bins.cpp toggles.h toggles.cpp lights.h lights.cpp spikeTrap.h spikeTrap.cpp level.txt
	g++ -o game $(LIBS) game.cpp -w
