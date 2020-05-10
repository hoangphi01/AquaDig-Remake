#include "stdafx.h"
#include "SDL_DisplayText.h"
#include "SDL_BaseObj.h"


TextShow::TextShow()
{
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	textTexture = NULL;
}

TextShow::~TextShow()
{
	Free();
}
 
bool TextShow::LoadText(TTF_Font* font, SDL_Renderer* screen)
{
	Free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, strVal.c_str(), textColor);
	if (textSurface)
	{
		textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
		tWidth = textSurface->w;
		tHeight = textSurface->h;
	}
	return textTexture != NULL;
}

void TextShow::Free()
{
	if(textTexture != NULL)
	{
		SDL_DestroyTexture(textTexture);
		textTexture = NULL;
	}
}

void TextShow::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	textColor.r = red;
	textColor.g = green;
	textColor.b = blue;
}

void TextShow::SetColor(int type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255, 0, 0 };
		textColor = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255, 255, 255 };
		textColor = color;
	}
	else if (type == YELLOW_TEXT)
	{
		SDL_Color color = { 255, 255, 0 };
		textColor = color;
	}
}

void TextShow::RenderText(SDL_Renderer* screen, int xTPos, int yTPos, SDL_Rect* clip, double angle,
	SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { xTPos, yTPos, tWidth, tHeight };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(screen, textTexture, clip, &renderQuad, angle, center, flip); 
}






