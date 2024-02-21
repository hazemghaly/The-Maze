#include "headers/main.h"

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface  = NULL;
SDL_Surface* gHelloWorld  = NULL;
SDL_Event e;

int main( int argc, char* args[] )
{
	bool quit = false;

	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );

			SDL_UpdateWindowSurface( gWindow );

            while ( quit == false )
			{
				while ( SDL_PollEvent( &e ) )
				{
					if ( e.type == SDL_QUIT )
						quit = true;
				}
			}
		}
	}

	close();
	return 0;
}