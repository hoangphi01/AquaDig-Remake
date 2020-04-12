#ifndef SDL_COMMON_FUNC_H_
#define SDL_COMMON_FUNC_H_

#include "stdafx.h"

#include <Windows.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;

//screen
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


#endif // SDL_COMMON_FUNC_H_
