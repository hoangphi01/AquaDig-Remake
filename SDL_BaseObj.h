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