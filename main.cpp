/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* gSplashScreen = NULL;

bool init()
{
	bool isInitOk = true;

	if(SDL_Init( SDL_INIT_VIDEO ) < 0)
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		isInitOk = false;
	}
	else
	{
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			isInitOk = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface( window );
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 76, 0, 153 ) );

		}
	}

	return isInitOk;
}

bool close()
{
	SDL_FreeSurface(gSplashScreen);
	gSplashScreen = NULL;

	SDL_DestroyWindow( window );
	SDL_Quit();
}

bool load_media()
{
	bool success = true;

	gSplashScreen = SDL_LoadBMP("splashscreen.bmp");
	if (gSplashScreen == NULL) {
		printf("Unable to load image!");
		success = false;
	}

	return success;
}

int main( int argc, char* args[] )
{
	if (!init()) {
		printf("Failed to init!");
	} else {
		if (!load_media()) {
			printf("failed to load media!");
		} else {
			SDL_BlitSurface(gSplashScreen, NULL, screenSurface, NULL);
			SDL_UpdateWindowSurface( window );
			SDL_Delay( 2000 );
		}
	}

	close();

	return 0;
}