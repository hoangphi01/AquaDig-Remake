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
#include "SDL_DisplayText.h"

BaseObject gBackground;
TTF_Font* countdownTime = NULL;

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

			if (TTF_Init() == -1)
			{
				success = false;
			}

			countdownTime = TTF_OpenFont("font/PixelFont.ttf", 13);
			if (countdownTime == NULL)
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

	//time countdown 
	TextShow game_time;
	game_time.SetColor(TextShow::WHITE_TEXT);

	TextShow game_point;
	game_point.SetColor(TextShow::YELLOW_TEXT);

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
//		game_map.DrawMap(gScreen);
		Map mapData = game_map.getMap();


		player_.SetMapView(mapData.startX, mapData.startY);
		player_.MovePlayer(mapData);
		player_.Show(gScreen);

		game_map.SetMap(mapData);
		game_map.DrawMap(gScreen);

		//time
		string timeStr = "TIME LEFT: ";
		Uint32 timeVal = SDL_GetTicks() / 1000;
		Uint32 valTime = 60 - timeVal;
		if (valTime <= 0)
		{
			quitSDL = true;
			break;
		}
		else
		{
			std::string strVal = std::to_string(valTime);
			timeStr += strVal;

			game_time.SetText(timeStr);
			game_time.LoadText(countdownTime, gScreen);
			game_time.RenderText(gScreen, SCREEN_WIDTH - 170, 50);
			if (valTime <= 15)
			{
				game_time.SetColor(TextShow::RED_TEXT);
			}
		}

		//point
		string pointStr = "MONEY: ";
		int moneyCount = player_.GetCoinValue();
		std::string moneyStr = std::to_string(moneyCount);
		pointStr += moneyStr;
		game_point.SetText(pointStr);
		game_point.LoadText(countdownTime, gScreen);
		game_point.RenderText(gScreen, SCREEN_WIDTH - 170, 15);

		SDL_RenderPresent(gScreen);
	}

	close();
	return 0;
}

