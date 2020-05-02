#include "stdafx.h"
#include "SDL_OceanMap.h"
#include "SDL_BaseObj.h"
#include "SDL_CommonFunc.h"

void OceanMap::LoadMap( char* name )
{
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL)
	{
		return;
	}

	gameMap.maxX = 0;
	gameMap.maxY = 0;

	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp, "%d", &gameMap.tile[i][j]);
			int value = gameMap.tile[i][j];
			if (value > 0)
			{
				if (j > gameMap.maxX)
				{
					gameMap.maxX = j;
				}
				if (i > gameMap.maxY)
				{
					gameMap.maxY = i;
				}
			}
		}
	}


	gameMap.maxX = (gameMap.maxX + 1) * TILE_SIZE;
	gameMap.maxY = (gameMap.maxY + 1) * TILE_SIZE;

	gameMap.startX = 0;
	gameMap.startY = 0;

	gameMap.fileName = name;
	fclose(fp);

}

void OceanMap::loadTiles(SDL_Renderer* screen)
{
	char fileIMG[50];
	FILE* fp = NULL;

	for (int i = 0; i < MAX_TILE; i++)
	{
		sprintf_s(fileIMG, "map/%d.png", i);

		fopen_s(&fp, fileIMG, "rb");
		if (fp == NULL)
		{
			continue;
		}

		fclose(fp);

		tileMap[i].LoadIMG(fileIMG, screen);
	}
}

void OceanMap::DrawMap(SDL_Renderer* screen)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	int mapX = 0;
	int mapY = 0;
	
	mapY = gameMap.startY / TILE_SIZE;
	y1 = (gameMap.startY%TILE_SIZE)* -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	mapX = gameMap.startX / TILE_SIZE;
	x1 = (gameMap.startX%TILE_SIZE)* -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	
	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		mapX = gameMap.startX / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int value = gameMap.tile[mapY][mapX];
			if (value > 0)
			{
				tileMap[value].setRect(j, i);
				tileMap[value].Render(screen);
			}
			mapX++;
		} 
		mapY++; 
	}
}