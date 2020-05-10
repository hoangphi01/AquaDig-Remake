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