#include "shared.h"

//global variable declaration
	int zoom = 10;
	int worldshiftx = 0;
	int worldshifty = 0;
	bool drag = false;

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;
	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	int grid [ worldsize ][ worldsize ] = {0};

	bool showgrid = false;

void draw()
{
	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00  );
	SDL_RenderClear( gRenderer );

	//go through the grid

	for ( int y = 0; y <  worldsize; y++)
	{
		
		for ( int x = 0; x < worldsize; x++)
		{
			//draw indavidual cells
			SDL_Rect fillRect = { (x+worldshiftx)*zoom, (y+worldshifty)*zoom, zoom, zoom };
			switch (grid[x][y])
			{
				case 0:
					SDL_SetRenderDrawColor( gRenderer, 0x99, 0x33, 0xFF, 0xFF );		
					SDL_RenderFillRect( gRenderer, &fillRect );
					break;
				case 1:
					SDL_SetRenderDrawColor( gRenderer, 255 , 215, 0, 0xFF );		
					SDL_RenderFillRect( gRenderer, &fillRect );
					break;
				case 2:
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xB2, 0x66, 0xFF );		
					SDL_RenderFillRect( gRenderer, &fillRect );
					break;
				case 3:
					SDL_SetRenderDrawColor( gRenderer, 0x00, 0x99, 0x4C, 0xFF );		
					SDL_RenderFillRect( gRenderer, &fillRect );
					break;
				case 4:
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );		
					SDL_RenderFillRect( gRenderer, &fillRect );
					break;
				default: break;
			}
			//grid
			if(showgrid)
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
				SDL_RenderDrawPoint( gRenderer, (x+worldshiftx)*zoom, (y+worldshifty)*zoom );
			}
		}
		
	}
		
	////Render red filled quad
	//SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );		
	//SDL_RenderFillRect( gRenderer, &fillRect );

	////Render green outlined quad
	//SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	//SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );		
	//SDL_RenderDrawRect( gRenderer, &outlineRect );
	//			
	////Draw blue horizontal line
	//SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );		
	//SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

	//Update screen
	SDL_RenderPresent( gRenderer );
}

void click(int x, int y, char c)
{
	switch(c)
	{
		case SDL_BUTTON_LEFT:
			switch ( grid[ x/zoom-worldshiftx ][ y/zoom-worldshifty  ] )
			{
				case 0: 
					grid[ x/zoom-worldshiftx ][ y/zoom-worldshifty  ] = 1;
					break;
				case 3: 	
					grid[ x/zoom-worldshiftx ][ y/zoom-worldshifty  ] = 1;
					break;
				case 4: break;
				default: 
					grid[ x/zoom-worldshiftx ][ y/zoom-worldshifty  ] = 0;
					break;
			}
		case SDL_BUTTON_RIGHT: 
			drag = true;
			printf("on\n");
			break;
		
	}
}

void wheelcontrol(int dir)
{
	//printf("%d", dir);
	//worldshiftx += dir;
	zoom += dir;
}

void logic()
{
	bool destroy = false;

	for ( int y = 0; y < worldsize; y++)
	{
		for ( int x = 0; x < worldsize; x++)
		{
			//search for world limit
			if (grid[x][y] == 1)
			{
				destroy = false;
				if (grid[x+1][y] == 4) destroy = true; 
				if (grid[x+1][y+1] == 4) destroy = true;
				if (grid[x][y+1] == 4) destroy = true; 
				if (grid[x-1][y+1] == 4) destroy = true;
				if (grid[x-1][y] == 4) destroy = true;
				if (grid[x-1][y-1] == 4) destroy = true;
				if (grid[x][y-1] == 4) destroy = true;
				if (grid[x+1][y-1] == 4) destroy = true;
			}
			//search for neibors
			int neibors = 0;
			if (grid[x+1][y] == 1 || grid[x+1][y] == 2) neibors++; 
			if (grid[x+1][y+1] == 1 || grid[x+1][y+1] == 2) neibors++;
			if (grid[x][y+1] == 1 || grid[x][y+1] == 2) neibors++; 
			if (grid[x-1][y+1] == 1 || grid[x-1][y+1] == 2) neibors++;
			if (grid[x-1][y] == 1 || grid[x-1][y] == 2) neibors++;
			if (grid[x-1][y-1] == 1 || grid[x-1][y-1] == 2) neibors++;
			if (grid[x][y-1] == 1 || grid[x][y-1] == 2) neibors++;
			if (grid[x+1][y-1] == 1 || grid[x+1][y-1] == 2) neibors++;
			
			/*
				0: empty
				1: occupied
				2: marked for death
				3: marked for birth
				4: world end
			*/

			switch (grid[x][y])
			{
				case 0:
					if (neibors == 3) grid[x][y] = 3;
					break;
				case 1:
					if (neibors > 3) grid[x][y] = 2; 
					else if (neibors < 2) grid[x][y] = 2;
					else if (destroy == true) grid[x][y] = 2;
					break;
				default: break;
			}
		}
		
	}
}

void updatestate()
{
	for ( int y = 0; y < worldsize; y++)
	{
		for ( int x = 0; x < worldsize; x++)
		{
			switch (grid[x][y])
			{
				case 2:
					grid[x][y] = 0;
					break;
				case 3:
					grid[x][y] = 1;
					break;
				default: break;
			}
		}
		
	}
}

void setupmap()
{
	for ( int y = 0; y < worldsize; y++)
	{
		for ( int x = 0; x < worldsize; x++)
		{
			if ( y == 0) grid[x][y] = 4;
			else if ( y == worldsize-1) grid[x][y] = 4;
			else if ( x == 0) grid[x][y] = 4;
			else if ( x == worldsize-1) grid[x][y] = 4;
			else grid[x][y] = 0;
		}
	}
}

void loadmap()
{
	FILE *infile = NULL;
	infile = fopen("glider.map","r");
	
	for ( int y = 0; y < 80; y++)
	{
		for ( int x = 0; x < 80; x++)
		{
			fscanf(infile, "%d", &grid[x][y]);
		}
	}
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	SDL_Init( SDL_INIT_VIDEO );
	//Create window
	gWindow = SDL_CreateWindow( "Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	//Create renderer for window
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );	
	//Initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	return success;
}


void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}
