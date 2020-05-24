//The software was written by me, with references from :

//Reference source 1 : LazyFoo's Tutorial (initSDL, Game-Loop, Texture load, Player with SpriteSheet load, Musics, Text)
//Reference source 2 : Phattrienphanmem123az's Tutorial (Map algorithm, Collision Detection) 
//Reference source 3 : Tran Thi Minh Chau's Tutorial (Way to organize, sort .h and .cpp files)  
//05 - 2020

#include "stdafx.h"
#include "SDL_BaseObj.h"
#include "SDL_DisplayText.h"

#include <iostream>
BaseObject::BaseObject()
{
	pObject = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

BaseObject::~BaseObject()
{
	Free();
}

bool BaseObject::LoadIMG(std::string path, SDL_Renderer* screen)
{
	Free(); //Remember this before debugging. Buffer overflow error. DS:04.28.20 
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
	if (loadSurface != NULL)
	{
		SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 255, 255, 255));
		newTexture = SDL_CreateTextureFromSurface( screen, loadSurface);
		if (newTexture != NULL)
		{
			rect_.w = loadSurface->w;
			rect_.h = loadSurface->h;
		}
		SDL_FreeSurface(loadSurface);
	}

	pObject = newTexture;

	return pObject != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	
	SDL_Rect renderScreen = { rect_.x, rect_.y, rect_.w, rect_.h };

	SDL_RenderCopy(des, pObject, clip, &renderScreen);
}

void BaseObject::Free()
{
	if (pObject != NULL)
	{
		SDL_DestroyTexture(pObject);
		pObject = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}
