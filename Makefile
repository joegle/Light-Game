LIBS = -lglut -lGLU

game: bins.cpp bins.h boxes.cpp boxes.h controls.h dude.cpp dude.h game.cpp init.h init.cpp level.txt lights.cpp lights.h objects.h objects.cpp toggles.cpp toggles.h utils.cpp utils.h world.h world.cpp
	g++ -o game $(LIBS) game.cpp
