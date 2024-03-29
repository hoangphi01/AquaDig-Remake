//The software was written by me, with references from :

//Reference source 1 : LazyFoo's Tutorial (initSDL, Game-Loop, Texture load, Player with SpriteSheet load, Musics, Text)
//Reference source 2 : Phattrienphanmem123az's Tutorial (Map algorithm, Collision Detection) 
//Reference source 3 : Tran Thi Minh Chau's Tutorial (Way to organize, sort .h and .cpp files)  
//05 - 2020

#include "stdafx.h"
#include "SDL_Player.h"
#include "SDL_CommonFunc.h"
#include "SDL_BaseObj.h"


MainPlayer::MainPlayer()
{
	frameS = 0;
	xPos = 400;
	yPos = 80;
	xVal = 0;
	yVal = 0;
	widthFrame = 0;
	heightFrame = 0;
	statusS = -1;
	inputType.leftO = 0;
	inputType.rightO = 0;
	inputType.upO = 0;
	inputType.downO = 0;
	touchGround = false;
	oX = 0;
	oY = 0;

	goldCount = 0;
	silverCount = 0;
	copperCount = 0;
	
}

MainPlayer::~MainPlayer()
{

}

bool MainPlayer::LoadIMG(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadIMG(path, screen);

	if (ret == true)
	{
		widthFrame = rect_.w / 4;
		heightFrame = rect_.h;
	}
	return ret;
}

void MainPlayer::SetClips()
{
	if (widthFrame > 0 && heightFrame > 0)
	{
		frameClip[0].x = 0;
		frameClip[0].y = 0;
		frameClip[0].w = widthFrame;
		frameClip[0].h = heightFrame;

		frameClip[1].x = widthFrame;
		frameClip[1].y = 0;
		frameClip[1].w = widthFrame;
		frameClip[1].h = heightFrame;

		frameClip[2].x = 2*widthFrame;
		frameClip[2].y = 0;
		frameClip[2].w = widthFrame;
		frameClip[2].h = heightFrame;

		frameClip[3].x = 3*widthFrame;
		frameClip[3].y = 0;
		frameClip[3].w = widthFrame;
		frameClip[3].h = heightFrame;
	}
}

void MainPlayer::CountMoneyGold()
{
	goldCount++;
}

void MainPlayer::CountMoneySilver()
{
	silverCount++;
}

void MainPlayer::CountMoneyCopper()
{
	copperCount++;
}

void MainPlayer::Show(SDL_Renderer* des)
{
    if (statusS == SWIM_UP)
	{
		LoadIMG("Image/Player/player_up.png", des);
	}
	else if (statusS == SWIM_DOWN)
	{
		LoadIMG("Image/Player/player_down.png", des);
	}
	else if (statusS == SWIM_LEFT)
	{
		LoadIMG("Image/Player/player_left.png", des);
	}
	else if (statusS == SWIM_RIGHT)
	{
		LoadIMG("Image/Player/player_right.png", des);
	}

	if ((inputType.leftO == 1) || (inputType.rightO == 1) || (inputType.upO == 1) || (inputType.downO == 1))
	{
		frameS++;
	}
	else
	{
		frameS = 0;
	}

	if (frameS >= 4)
	{
		frameS = 0;
	}
	
	rect_.x = xPos - oX;
	rect_.y = yPos - oY;

	SDL_Rect* currentClip = &frameClip[frameS];

	SDL_Rect renderQuad = { rect_.x, rect_.y, widthFrame, heightFrame };

	SDL_RenderCopy(des, pObject, currentClip, &renderQuad);

}

void MainPlayer::KeyboardAction(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
			statusS = SWIM_RIGHT;
			inputType.rightO = 1;
			inputType.leftO = 0;
			break;
		case SDLK_LEFT:
			statusS = SWIM_LEFT;
			inputType.leftO = 1;
			inputType.rightO = 0;
			break;
		case SDLK_UP:
			statusS = SWIM_UP;
			inputType.upO = 1;
			inputType.downO = 0;
			break;
		case SDLK_DOWN:
			statusS = SWIM_DOWN;
			inputType.downO = 1;
			inputType.upO = 0;
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			statusS = SWIM_RIGHT;
			inputType.rightO = 0;
		}
			break;
		case SDLK_LEFT:
		{
			statusS = SWIM_LEFT;
			inputType.leftO = 0;
		}
			break;
		case SDLK_UP:
		{
			statusS = SWIM_UP;
			inputType.upO = 0;
		}
			break;
		case SDLK_DOWN:
		{
			statusS = SWIM_DOWN;
			inputType.downO = 0;
		}
			break;
		}
	}
	
}

void MainPlayer::MovePlayer(Map& mapData, Mix_Chunk* gSoundCoin, bool &quitSDL)
{
	xVal = 0;
	yVal = 1;
//	const int playerSpeed = 2;
	
	if (yVal >= MAX_FALLING_SPEED)
	{
		yVal = MAX_FALLING_SPEED;
		xVal = 0;
	}
	
	if (inputType.leftO == 1)
	{
		xVal = -PLAYER_SPEED;
	}
	else if (inputType.rightO == 1)
	{
		xVal = PLAYER_SPEED;
	}
	if (inputType.upO == 1)
	{
		yVal = -PLAYER_SPEED;
	}
	else if (inputType.downO == 1)
	{
		yPos += yVal;
	}
//	cout << xPos << " " << yPos << endl;

	TouchMap(mapData, gSoundCoin, quitSDL);
	CenterPlayer(mapData);
}

void MainPlayer::CenterPlayer(Map& mapData)
{
	mapData.startY = yPos - (SCREEN_HEIGHT / 2);
	if (mapData.startY < 0){
		mapData.startY = 0;
	}
	else if (mapData.startY + SCREEN_HEIGHT >= mapData.maxY){
		mapData.startY = mapData.maxY - SCREEN_HEIGHT;
	}

	mapData.startX = xPos - (SCREEN_WIDTH / 2);
	if (mapData.startX < 0){
		mapData.startX = 0;
	}
	else if (mapData.startX + SCREEN_WIDTH >= mapData.maxX){
		mapData.startX = mapData.maxX - SCREEN_WIDTH;
	}
}

void MainPlayer::TouchMap(Map& mapData, Mix_Chunk* gSoundCoin, bool &quitSDL)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//Check H
	int heightMin = heightFrame < TILE_SIZE ? heightFrame : TILE_SIZE;

	x1 = (xPos + xVal) / TILE_SIZE;
	x2 = (xPos + xVal + widthFrame - 1) / TILE_SIZE;

	y1 = (yPos) / TILE_SIZE;
	y2 = (yPos + heightMin - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		int y1x2Val = mapData.tile[y1][x2];
		int y2x2Val = mapData.tile[y2][x2];
		if (xVal > 0)
		{
			if (y1x2Val == MONEY_GOLD && y2x2Val == MONEY_GOLD)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				cout << y1x2Val << " " << y2x2Val << endl;
				CountMoneyGold();
				Mix_PlayChannel(-1, gSoundCoin, 0);
			}
			else if (y1x2Val == MONEY_SILVER && y2x2Val == MONEY_SILVER)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneySilver();
				Mix_PlayChannel(-1, gSoundCoin, 0);
			}
			else if (y1x2Val == MONEY_COPPER && y2x2Val == MONEY_COPPER)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneyCopper();
				Mix_PlayChannel(-1, gSoundCoin, 0);
			}
			else if (y1x2Val == MONEY_RED && y2x2Val == MONEY_RED)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneyCopper();
				Mix_PlayChannel(-1, gSoundCoin, 0);
				loadFinal(quitSDL);
			}
			else
			{
				if (mapData.tile[y1][x2] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE)
				{
					xPos = x2 * TILE_SIZE;
					xPos -= widthFrame + 1;
					xVal = 0;
				}
			}
		}
		else if (xVal < 0)
		{
			if (y1x2Val == MONEY_GOLD && y2x2Val == MONEY_GOLD)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneyGold();
				Mix_PlayChannel(-1, gSoundCoin, 0);
			}
			else if (y1x2Val == MONEY_SILVER && y2x2Val == MONEY_SILVER)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneySilver();
				Mix_PlayChannel(-1, gSoundCoin, 0);
			}
			else if (y1x2Val == MONEY_COPPER && y2x2Val == MONEY_COPPER)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneyCopper();
				Mix_PlayChannel(-1, gSoundCoin, 0);
			}
			else if (y1x2Val == MONEY_RED && y2x2Val == MONEY_RED)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneyCopper();
				Mix_PlayChannel(-1, gSoundCoin, 0);
				loadFinal(quitSDL);
			}
			else
			{
				if (mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y2][x1] != BLANK_TILE)
				{
					xPos = (x1 + 1) * TILE_SIZE;
					xVal = 0;
				}
			}
		} 
	}

	//Check V
	int widthMin = widthFrame < TILE_SIZE ? widthFrame : TILE_SIZE;
	x1 = (xPos) / TILE_SIZE;
	x2 = (xPos + widthMin) / TILE_SIZE;

	y1 = (yPos + yVal) / TILE_SIZE;
	y2 = (yPos + yVal + heightFrame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
	{
		int y2x1Val = mapData.tile[y2][x1];
		int y2x2Val = mapData.tile[y2][x2];
		if (yVal > 0)
		{
			if (y2x1Val == MONEY_GOLD && y2x2Val == MONEY_GOLD)
			{
				mapData.tile[y2][x1] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneyGold();
				Mix_PlayChannel(-1, gSoundCoin, 0);
			}
			else if (y2x1Val == MONEY_SILVER && y2x2Val == MONEY_SILVER)
			{
				mapData.tile[y2][x1] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneySilver();
				Mix_PlayChannel(-1, gSoundCoin, 0);
			}
			else if (y2x1Val == MONEY_COPPER && y2x2Val == MONEY_COPPER)
			{
				mapData.tile[y2][x1] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneyCopper();
				Mix_PlayChannel(-1, gSoundCoin, 0);
			}
			else if (y2x1Val == MONEY_RED && y2x2Val == MONEY_RED)
			{
				mapData.tile[y2][x1] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneyCopper();
				Mix_PlayChannel(-1, gSoundCoin, 0);
				loadFinal(quitSDL);
			}
			else
			{
				if (mapData.tile[y2][x1] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE)
				{
					yPos = y2 * TILE_SIZE;
					yPos -= (heightFrame + 1);
					yVal = 0;
					touchGround = true;
				}
			}
		}
		else if (yVal < 0)
		{
			if (y2x1Val == MONEY_GOLD && y2x2Val == MONEY_GOLD)
			{
				mapData.tile[y2][x1] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneyGold();
				Mix_PlayChannel(-1, gSoundCoin, 0);
			}
			else if (y2x1Val == MONEY_SILVER && y2x2Val == MONEY_SILVER)
			{
				mapData.tile[y2][x1] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneySilver();
				Mix_PlayChannel(-1, gSoundCoin, 0);
			}
			else if (y2x1Val == MONEY_COPPER && y2x2Val == MONEY_COPPER)
			{
				mapData.tile[y2][x1] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneyCopper();
				Mix_PlayChannel(-1, gSoundCoin, 0);
			}
			else if (y2x1Val == MONEY_RED && y2x2Val == MONEY_RED)
			{
				mapData.tile[y2][x1] = 0;
				mapData.tile[y2][x2] = 0;
				CountMoneyCopper();
				Mix_PlayChannel(-1, gSoundCoin, 0);
				loadFinal(quitSDL);
			}
			else
			{
				if (mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y1][x2] != BLANK_TILE)
				{
					yPos = (y1 + 1) * TILE_SIZE;
					yVal = 0;
				}
			}
		}
	}
	xPos += xVal;
	yPos += yVal;

	if (xPos < 0)
	{
		xPos = 0;
	}
	else if (xPos + widthFrame > mapData.maxX)
	{
		xPos = mapData.maxX - widthFrame - 1;
	}

}








