LIBS = -lglut -lGLU

game: game.cpp globals.h controls.h objects.cpp init.h init.cpp utils.cpp world.cpp dude.cpp boxes.cpp boxes.h bins.cpp toggles.h toggles.cpp
	g++ -o game $(LIBS) game.cpp
