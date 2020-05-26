//The software was written by me, with references ideas from :

//Reference source 1 : LazyFoo's Tutorial (initSDL, Game-Loop, Texture load, Player with SpriteSheet load, Musics, Text)
//Reference source 2 : Phattrienphanmem123az's Tutorial (Map algorithm, Collision Detection) 
//Reference source 3 : Tran Thi Minh Chau's Tutorial (Way to organize, sort .h and .cpp files)  
//05 - 2020

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

//Load Icon
SDL_Surface* icon = IMG_Load("icon/AquaDigRe.png");

//Create Background
BaseObject gBackground;

//Fonts
TTF_Font* countdownTime = NULL;

//Free Musics
void FreeMusic()
{
	if (gSoundCoin != NULL)
	{
		Mix_FreeChunk(gSoundCoin);
		gSoundCoin = NULL;
	}
}

//Free Theme Musics
void FreeTheme()
{
	if (gSoundTheme != NULL)
	{
		Mix_FreeMusic(gSoundTheme);
		gSoundTheme = NULL;
	}
}

//Init SDL
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

			//sound
			if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
			{
				success = false;
			}
			
			FreeTheme();
			gSoundTheme = Mix_LoadMUS("Music/ThemeSound.wav");
			FreeMusic();
			gSoundCoin = Mix_LoadWAV("Music/CollectMoney.wav");

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

void loadAndRenderMenu(){
	BaseObject Menu;

	bool test = Menu.LoadIMG("Image/Menu.png", gScreen);
	if (test == false)
	{
		cout << "SDL Error " << SDL_GetError() << endl;
	}
	Menu.Render(gScreen, NULL);
	SDL_RenderPresent(gScreen);
	SDL_Delay(5000);
}

void loadGameOver(){
	BaseObject GameOver;

	bool test = GameOver.LoadIMG("Image/GameOver.png", gScreen);
	if (test == false)
	{
		cout << "SDL Error " << SDL_GetError() << endl;
	}
	GameOver.Render(gScreen, NULL);
	SDL_RenderPresent(gScreen);
	SDL_Delay(2000);
}

void loadFinal(bool &quitSDL){
	BaseObject Final;

	bool test = Final.LoadIMG("Image/Final.png", gScreen);
	if (test == false)
	{
		cout << "SDL Error " << SDL_GetError() << endl;
	}
	Final.Render(gScreen, NULL);
	SDL_RenderPresent(gScreen);
	SDL_Delay(5000);
	quitSDL = true;
}

void loadIcon()
{
	SDL_SetWindowIcon(gWindow, icon);
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

Uint32 playGame(bool &playAgain, Uint32 totalTime)
{
	
	bool quitSDL = false;

	loadIcon();
	loadAndRenderMenu();
	loadBackground();

	//play theme
	Mix_PlayMusic(gSoundTheme, -1);

	//load map
	OceanMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.loadTiles(gScreen);

	//load player
	MainPlayer player_;
	player_.LoadIMG("Image/Player/player_right.png", gScreen);
	player_.SetClips();

	//show text
	TextShow game_point;
	game_point.SetColor(TextShow::YELLOW_TEXT);

	//time countdown 
	TextShow game_time;
	game_time.SetColor(TextShow::WHITE_TEXT);

	Uint32 prevMoney = 0;
	Uint32 startTime = 185;
	Uint32 timeVal;

	
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
		player_.MovePlayer(mapData, gSoundCoin, quitSDL);
		player_.Show(gScreen);

		game_map.SetMap(mapData);
		game_map.DrawMap(gScreen, gSoundTheme);


		//point
		string pointStr = "MONEY: ";
		int moneyCount = player_.GetCoinValue();
		std::string moneyStr = std::to_string(moneyCount);
		pointStr += moneyStr;
		game_point.SetText(pointStr);
		game_point.LoadText(countdownTime, gScreen);
		game_point.RenderText(gScreen, SCREEN_WIDTH - 170, 15);

		//time
		string timeStr = "TIME LEFT: ";
		timeVal = SDL_GetTicks() / 1000 - totalTime;
		Uint32 valTime = startTime - timeVal;

		if (moneyCount - prevMoney >= 50)
		{
			prevMoney += moneyCount - prevMoney;
			startTime += 10;
		}
		else
		{
			if (valTime <= 15)
			{
				game_time.SetColor(TextShow::RED_TEXT);
			}
			if (valTime <= 0)
			{
				loadGameOver();
				playAgain = true;
				quitSDL = true;
//				break;
			}

			std::string strVal = std::to_string(valTime);
			timeStr += strVal;


			game_time.SetText(timeStr);
			game_time.LoadText(countdownTime, gScreen);
			game_time.RenderText(gScreen, SCREEN_WIDTH - 170, 50);


		}

		SDL_RenderPresent(gScreen);
	}
	cout << timeVal << endl;
	return timeVal;
}

int main(int argc, char* argv[])
{
	if (initSDL() == false)
	{
		cout << "SDL Error " << SDL_GetError() << endl;
		return -1;
	}

	//Game Loop
	Uint32 totalTime = 0;
	bool playAgain = true;
	while (playAgain) {
		playAgain = false;
		totalTime += playGame(playAgain, totalTime);
		cout << totalTime << endl;
	}


	close();

	return 0;
}



