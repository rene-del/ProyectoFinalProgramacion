#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"

enum STATES { ST_STILL, ST_MOVING, ST_NOT_ATTACKING, ST_ATTACK };

enum DIRECTION { DIR_RIGHT, DIR_LEFT, DIR_DOWN, DIR_UP };

class Player
{
private:
	int _img;

	SDL_Rect _src;
	SDL_Rect _dst;

	Uint32 _spriteMaxTime;
	Uint32 _nextSpriteCount;

	STATES _actualState;
	DIRECTION _actualDir;

public:
	Player();
	~Player();

	void init();
	void update();
	void render();

	void setImg(int id) { _img = id; };
	void setNextSpriteCount(Uint32 time) { _nextSpriteCount = time; };

	STATES getState() { return _actualState; };
};

#endif

