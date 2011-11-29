LIBS = -lglut -lGLU

game: 
	g++ -o game $(LIBS) game.cpp controls.h objects.h
