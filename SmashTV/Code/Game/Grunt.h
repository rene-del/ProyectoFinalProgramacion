#pragma once

#include "SDL.h"
enum STATES_GRUNT { ST_G_STILL, ST_G_MOVING, ST_G_DEAD, ST_G_ALIVE };

class Grunt
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

	STATES_GRUNT _actualMovementState;

public:

	Grunt();
	~Grunt();

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

	STATES_GRUNT getMovementState() { return _actualMovementState; };



};

