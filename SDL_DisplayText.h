//The software was written by me, with references ideas from :

//Reference source 1 : LazyFoo's Tutorial (initSDL, Game-Loop, Texture load, Player with SpriteSheet load, Musics, Text)
//Reference source 2 : Phattrienphanmem123az's Tutorial (Map algorithm, Collision Detection) 
//Reference source 3 : Tran Thi Minh Chau's Tutorial (Way to organize, sort .h and .cpp files)  
//05 - 2020

#ifndef TEXT_SHOW_H_
#define TEXT_SHOW_H_

#include"SDL_CommonFunc.h"
#include"SDL_BaseObj.h"

class TextShow
{
public:
	TextShow();
	~TextShow();

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		YELLOW_TEXT = 2,
	};

	bool LoadText(TTF_Font* font, SDL_Renderer* screen);
	void Free();

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);

	void RenderText(SDL_Renderer* screen, int xTPos, int yTPos, SDL_Rect* clip = NULL, double angle = 0.0,
					SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int GetTextWidth() const { return tWidth; }
	int GetTextHeight() const { return tHeight; }

	void SetText(const std::string& text) { strVal = text; }
	string GetText() const { return strVal; }

private:
	string strVal;
	SDL_Color textColor;
	SDL_Texture* textTexture;
	int tWidth;
	int tHeight;
};

#endif