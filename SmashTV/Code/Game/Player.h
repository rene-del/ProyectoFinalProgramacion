#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"

enum STATES { ST_STILL, ST_MOVING, ST_NOT_ATTACKING, ST_ATTACKING, ST_DEAD };

class Player
{
private:
	int _img;
	int _currSprite;
	int _speed;

	SDL_Rect _src;
	SDL_Rect _dst;

	Uint32 _spriteMaxTime;
	Uint32 _nextSpriteCount;

	STATES _actualMovementState;
	STATES _actualAttackingState;

public:
	Player();
	~Player();

	void init();
	void update();
	void render();

	void checkMapLimits();

	void setImg(int id) { _img = id; };
	void setCurrSprite(int val) { _currSprite = val; };
	void setNextSpriteCount(Uint32 time) { _nextSpriteCount = time; };

	Uint32 getNextSpriteCount() { return _nextSpriteCount; };
	Uint32 getSpriteMaxTime() { return _spriteMaxTime; };

	STATES getMovementState() { return _actualMovementState; };
	STATES getAttackingState() { return _actualAttackingState; };
};

#endif

