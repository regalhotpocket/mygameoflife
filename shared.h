//libraries used everywhere
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <cmath>
#include <sstream>
#include <SDL2/SDL_image.h>


//function prototypes
	//initiate SDL
	bool init();
	//prepare to close the program
	void close();
	//prep and draw the screen
	void draw();
	//prep and draw the screen
	void click(int x, int y, char c );
	//check, destroy, and birth
	void logic();
	//update state
	void updatestate();
	//clear items
	void setupmap();
	//load a premade map
	void loadmap();
	//zoom controls
	void wheelcontrol(int dir);

//global constants
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;
	const int worldsize = 80;

//grabbing global variables difined in shared.cpp
	extern int zoom;
	extern int worldshiftx;
	extern int worldshifty;
	extern bool drag;

	//The window we'll be rendering to
	extern SDL_Window* gWindow;
	//The window renderer
	extern SDL_Renderer* gRenderer;

	extern int grid [ worldsize ][ worldsize ];

	extern bool showgrid;
