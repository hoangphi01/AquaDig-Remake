#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_

#include "SDL_CommonFunc.h"
#include "SDL_BaseObj.h"


#define FALLING_SPEED 0.7
#define MAX_FALLING_SPEED 10
#define PLAYER_SPEED 2
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
		//SPACE_PUSH = 4
	};

	virtual bool LoadIMG(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void KeyboardAction(SDL_Event events, SDL_Renderer* screen);
	void SetClips();

	void MovePlayer(Map& mapData, Mix_Chunk* gSoundCoin, bool &quitSDL);
	void TouchMap(Map& mapData, Mix_Chunk* gSoundCoin, bool &quitSDL);
	void SetMapView(const int oceanX, const int oceanY) { oX = oceanX; oY = oceanY; };
	void CenterPlayer(Map& mapData);
	void CountMoneyGold();
	void CountMoneySilver();
	void CountMoneyCopper();
	int GetCoinValue() const { return (goldCount*10 + silverCount*7 + copperCount*3); };
private:
	int goldCount = 0;
	int silverCount = 0;
	int copperCount = 0;

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

	int oX;
	int oY; //luu vi tri moi de view map

};



#endif
