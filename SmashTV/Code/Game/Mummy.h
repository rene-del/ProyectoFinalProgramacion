#pragma once
#include "SDL.h"

enum STATES_MUMMY { ST_M_STILL, ST_M_MOVING, ST_M_DEAD, ST_M_ALIVE };


class Mummy
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

	STATES_MUMMY _actualMovementState;
public:
	Mummy();
	~Mummy();

	void init();
	void update();
	void render();

	void checkMapLimits();

	void setImg(int id) { _img = id; };
	void setCurrentSprite(int val) { _currSprite = val; };
	void setNextSpriteCount(Uint32 time) { _nextSpriteCount = time; };

	void setMummytX(int val) { _dst.x = val; };
	void setMummyY(int val) { _dst.y = val; };

	int getMummyX() { return _dst.x; };
	int getMummyY() { return _dst.y; };

	Uint32 getNextSpriteCoint() { return _nextSpriteCount; };
	Uint32 getSpriteMaxTime() { return _spriteMaxTime; };

	STATES_MUMMY getMovementState() { return _actualMovementState; };


};

