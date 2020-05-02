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
#include "SDL_Player.h"

BaseObject gBackground;


bool initSDL()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL Error " << SDL_GetError() << endl;
		success = false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gWindow = SDL_CreateWindow( "AquaDig Remake v1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (gWindow == NULL)
	{
		cout << "SDL Error " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Prevent overloading CPU & GPU. DS:04.29.20
		if (gScreen == NULL) //important!!! Lack of "=" symbol can make this code error. DS:04.15.20
		{
			cout << "SDL Error " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
			{
				success = false;
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

	MainPlayer player_;
	player_.LoadIMG("Image/Player/player_right.png", gScreen);
	player_.SetClips();

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

			player_.KeyboardAction(gEvent, gScreen);
		}
		SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
		SDL_RenderClear(gScreen);

		gBackground.Render(gScreen, NULL);
		game_map.DrawMap(gScreen);
		Map mapData = game_map.getMap();

		player_.MovePlayer(mapData);
//		player_.TouchMap(mapData);
		player_.Show(gScreen);

		SDL_RenderPresent(gScreen);
	}

	close();
	return 0;
}

