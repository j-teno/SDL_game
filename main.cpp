/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL error: %s\n", path, IMG_GetError());
	} else {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s!", path.c_str());
		}
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

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
			int imgFlags = IMG_INIT_PNG;

			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                isInitOk = false;
			}
			else
			{
				gScreenSurface = SDL_GetWindowSurface( window );
			}
		}
	}

	return isInitOk;
}

bool close()
{
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
	{
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}

	SDL_DestroyWindow( window );
	window = NULL;
	SDL_Quit();
}

bool load_media()
{
	bool success = true;

	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("background.png");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		printf("Failed to load DEFAULT image!\n");
		success = false;
	}

	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.png");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
		printf("Failed to load DOWN image!\n");
		success = false;
	}

	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.png");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
		printf("Failed to load LEFT image!\n");
		success = false;
	}

	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.png");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		printf("Failed to load RIGHT image!\n");
		success = false;
	}

	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.png");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
		printf("Failed to load UP image!\n");
		success = false;
	}
	return success;
}

void main_loop()
{
	bool quitReq = false;
	SDL_Event e;
	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

	while(!quitReq)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quitReq = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_q:
						quitReq = true;
						break;
					case SDLK_DOWN:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
						break;
					case SDLK_LEFT:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
						break;
					case SDLK_RIGHT:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
						break;
					case SDLK_UP:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
						break;
					default:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
						break;
						
				}
			}
			// SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
			SDL_Rect stretchRect {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
			SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
			SDL_UpdateWindowSurface(window);
		}
	}
}

int main( int argc, char* args[] )
{
	if (!init()) {
		printf("Failed to init!");
	} else {
		if (!load_media()) {
			printf("failed to load media!");
		} else {
			main_loop();
		}
	}

	close();

	return 0;
}