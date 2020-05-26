//The software was written by me, with references ideas from :

//Reference source 1 : LazyFoo's Tutorial (initSDL, Game-Loop, Texture load, Player with SpriteSheet load, Musics, Text)
//Reference source 2 : Phattrienphanmem123az's Tutorial (Map algorithm, Collision Detection) 
//Reference source 3 : Tran Thi Minh Chau's Tutorial (Way to organize, sort .h and .cpp files)  
//05 - 2020

#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "stdafx.h"

#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "SDL_CommonFunc.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void setRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }
	SDL_Rect getRect() const { return rect_; }
	SDL_Texture* getObject() const { return pObject; }

	bool LoadIMG(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();


protected:
	SDL_Texture* pObject;
	SDL_Rect rect_;
};
#endif // BASE_OBJECT_H_