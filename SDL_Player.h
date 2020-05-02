#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_

#include "SDL_CommonFunc.h"
#include "SDL_BaseObj.h"

#define FALLING_SPEED 0.7
#define MAX_FALLING_SPEED 10
#define PLAYER_SPEED 0.1
#define MAX_SURFACE 40

class MainPlayer : public BaseObject
{
public:
	MainPlayer();
	~MainPlayer();

	enum SwimType
	{
		SWIM_UP = 0,
		SWIM_DOWN = 1,
		SWIM_RIGHT = 2,
		SWIM_LEFT = 3
	};

	virtual bool LoadIMG(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void KeyboardAction(SDL_Event events, SDL_Renderer* screen);
	void SetClips();

	void MovePlayer(Map& mapData);
	void TouchMap(Map& mapData);

private:
	float xVal;
	float yVal;

	float xPos;
	float yPos;

	int widthFrame;
	int heightFrame;

	SDL_Rect frameClip[4];
	Input inputType;
	int frameS;
	int statusS;

	bool touchGround;

};



#endif
