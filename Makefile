LIBS = -lglut -lGLU


game: game.cpp globals.h controls.cpp objects.cpp init.cpp utils.cpp
	g++ -o game $(LIBS) game.cpp 

test:
	g++ -o test $(LIBS) test.cpp

