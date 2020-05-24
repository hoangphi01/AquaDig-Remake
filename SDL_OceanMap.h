//The software was written by me, with references from :

//Reference source 1 : LazyFoo's Tutorial (initSDL, Game-Loop, Texture load, Player with SpriteSheet load, Musics, Text)
//Reference source 2 : Phattrienphanmem123az's Tutorial (Map algorithm, Collision Detection) 
//Reference source 3 : Tran Thi Minh Chau's Tutorial (Way to organize, sort .h and .cpp files)  
//05 - 2020

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

	void LoadMap(char* name);
	void loadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen, Mix_Music* gSoundTheme);
	Map getMap() const { return gameMap; };
	void SetMap(Map& map_data) { gameMap = map_data; };

private:
	Map gameMap;
	tileMap tileMap[MAX_TILE];
};


#endif 