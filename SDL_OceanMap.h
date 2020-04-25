#ifndef OCEAN_MAP_H
#define OCEAN_MAP_H

#include "SDL_CommonFunc.h"
#include "SDL_BaseObj.h"

#define MAX_TILE 100

class tileMap : public BaseObject
{
public:
	tileMap() { ; }
	~tileMap() { ; }
};

class OceanMap
{
public:
	OceanMap() { ; }
	~OceanMap() { ; }

	void LoadMap(char* name );
	void loadTiles( SDL_Renderer* screen );
	void DrawMap(SDL_Renderer* screen);

private:
	Map gameMap;
	tileMap tileMap[MAX_TILE];
};


#endif 