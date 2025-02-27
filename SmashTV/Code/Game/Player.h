#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"

enum STATES { ST_STILL, ST_MOVING, ST_NOT_ATTACKING, ST_ATTACKING };

enum DIRECTION { DIR_RIGHT, DIR_LEFT, DIR_DOWN, DIR_UP };

class Player
{
private:
	int _img;

	SDL_Rect _src;
	SDL_Rect _dst;

	Uint32 _spriteMaxTime;
	Uint32 _nextSpriteCount;

	STATES _actualMovementState;
	STATES _actualAttackingState;
	DIRECTION _actualDir;

public:
	Player();
	~Player();

	void init();
	void update();
	void render();

	void setImg(int id) { _img = id; };
	void setNextSpriteCount(Uint32 time) { _nextSpriteCount = time; };

	Uint32 getNextSpriteCount() { return _nextSpriteCount; };

	STATES getMovementState() { return _actualMovementState; };
	STATES getAttackingState() { return _actualAttackingState; };
};

#endif

