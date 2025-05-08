#pragma once

#include "SDL.h"

//constant movement
enum STATES_ENEMIES {ST_E_STILL, ST_E_MOVING, ST_E_DEAD, ST_E_ALIVE};

class Blob
{
private:

	int _img;
	int _bulltetImg;
	int _currSprite;
	int _speed;
	int _numberBullets;
	int _contador;
	
	bool _reverse;
	bool isDead;



	SDL_Rect _src;
	SDL_Rect _dst;

	Uint32 _spriteMaxTime;
	Uint32 _nextSpriteCount;

	STATES_ENEMIES _actualMovementState;
	

public:
	Blob();
	~Blob();

	void init();
	void update();
	void render();

	void checkMapLimits();

	void setImg(int id) { _img = id; };
	void setCurrentSprite(int val) { _currSprite = val; };
	void setNextSpriteCount(Uint32 time) { _nextSpriteCount = time; };

	void setBlobX(int val) { _dst.x = val; };
	void setBlobY(int val) { _dst.y = val; };

	int getBlobX() { return _dst.x; };
	int getBlobY() { return _dst.y; };

	Uint32 getNextSpriteCoint() { return _nextSpriteCount; };
	Uint32 getSpriteMaxTime() { return _spriteMaxTime; };

	STATES_ENEMIES getMovementState() { return _actualMovementState; };
	


};

