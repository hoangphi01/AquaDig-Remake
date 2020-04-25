// AquaDig Remake 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

#include "SDL_CommonFunc.h"
#include "SDL_BaseObj.h"
#include "SDL_OceanMap.h"

BaseObject gBackground;

bool initSDL()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL Error " << SDL_GetError() << endl;
		success = false;
		return false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gWindow = SDL_CreateWindow( "AquaDig Remake v1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (gWindow == NULL)
	{
		cout << "SDL Error " << SDL_GetError() << endl;
		success = false;
		return false;
	}
	else
	{
		gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gScreen == NULL) //important!!! Lack of "=" symbol can make this code error.

		{
			cout << "SDL Error " << SDL_GetError() << endl;
			success = false;
			return false;
		}
		else
		{
			SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
			{
				success = false;
				return false;
			}
			
		}
	}
	return success;

}

bool loadBackground()
{
	bool test = gBackground.LoadIMG("Image/Background.png", gScreen);
	if (test == false)
	{
		cout << "SDL Error " << SDL_GetError() << endl;
		return false;
	}
	return true;
}

void close()
{
	gBackground.Free();

	SDL_DestroyRenderer(gScreen);
	gScreen = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (initSDL() == false)
	{
		cout << "SDL Error " << SDL_GetError() << endl;
		return -1;
	}
	if (loadBackground() == false)
	{
		cout << "SDL Error " << SDL_GetError() << endl;
		return -1;
	}

	OceanMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.loadTiles(gScreen);



	bool quitSDL = false;
	SDL_Event gEvent;
	while (!quitSDL)
	{
		while (SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_QUIT)
			{
				quitSDL = true;
			}
		}
		SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
		SDL_RenderClear(gScreen);

		gBackground.Render(gScreen, NULL);
		game_map.DrawMap(gScreen);

		SDL_RenderPresent(gScreen);
	}

	close();
	return 0;
}

