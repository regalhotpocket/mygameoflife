#include "shared.h"


int main()
{
	init();
	setupmap();
	bool quit = false; 
	bool paused = true;
	SDL_Event userinput;

	while( !quit ) 
	{
		 while( SDL_PollEvent( &userinput ) != 0 ) 
		{ 
			switch( userinput.type )
			{
				case SDL_QUIT: 
					quit = true; 
					break;
				case SDL_MOUSEBUTTONDOWN:
					click(userinput.button.x, userinput.button.y, userinput.button.button);
					break;
				case SDL_MOUSEBUTTONUP:
					if (userinput.button.button == SDL_BUTTON_RIGHT )
					{
						drag = false;
					}
					break;
					
				case SDL_MOUSEMOTION:
					if (drag) 
					{
						worldshiftx += userinput.motion.xrel;
		  				worldshifty += userinput.motion.yrel;
					}
					break;
				
				case SDL_MOUSEWHEEL:
					wheelcontrol(userinput.button.x);
					break;
					
				case SDL_KEYDOWN:
					switch(userinput.key.keysym.sym)
					{
						case SDLK_SPACE:
							paused = !paused;
						break;
						case SDLK_l:
							loadmap();
						break;
					}
					break;
				
			}

		}
		if(!paused)
		{
			logic();
			updatestate();
		}
			
		draw();
		SDL_Delay(500);
	}
	
	close();

}
