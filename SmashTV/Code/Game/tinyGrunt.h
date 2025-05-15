#pragma once

#include "SDL.h"

enum STATES_TINYGRUNT { ST_TG_STILL, ST_TG_MOVING, ST_TG_DEAD, ST_TG_ALIVE };

class tinyGrunt
{
private:
	int _img;
	int _imgDead;
	int _currSprite;
	int _speed;
	int _contador;

	bool _isDead;

	SDL_Rect _src;
	SDL_Rect _dst;

	Uint32 _spriteMaxTime;
	Uint32 _nextSpriteCount;

	STATES_TINYGRUNT _actualMovementState;

public:

	tinyGrunt();
	~tinyGrunt();

	void init();
	void update();
	void render();

	void checkMapLimits();

	void setImg(int id) { _img = id; };
	void setCurrentSprite(int val) { _currSprite = val; };
	void setNextSpriteCount(Uint32 time) { _nextSpriteCount = time; };

	void setGruntX(int val) { _dst.x = val; };
	void setGruntY(int val) { _dst.y = val; };

	int getGruntX() { return _dst.x; };
	int getGruntY() { return _dst.y; };

	Uint32 getNextSpriteCoint() { return _nextSpriteCount; };
	Uint32 getSpriteMaxTime() { return _spriteMaxTime; };

	STATES_TINYGRUNT getMovementState() { return _actualMovementState; };


};

