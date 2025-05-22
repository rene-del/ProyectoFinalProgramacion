#pragma once

#include "Blob.h"



class Mine
{
private:
	int _img;
	int _imgExplosion;
	int _currSprite;
	int _speed;
	int _contador;

	bool _isTouched;

	SDL_Rect _src;
	SDL_Rect _dst;

	Uint32 _spriteMaxTime;
	Uint32 _nextSpriteCount;

public:
	Mine();
	~Mine();

	void init();
	void update();
	void render();

	void checkMapLimits();
	bool checkPlayerCollision(SDL_Rect rectPlayer);


	void setImg(int id) { _img = id; };
	void setCurrentSprite(int val) { _currSprite = val; };
	void setNextSpriteCount(Uint32 time) { _nextSpriteCount = time; };
	
	void setMineX(int val) { _dst.x = val; };
	void setMineY(int val) { _dst.y = val; };

	int getMineX() { return _dst.x; };
	int getMineY() { return _dst.y; };

	Uint32 getNextSpriteCoint() { return _nextSpriteCount; };
	Uint32 getSpriteMaxTime() { return _spriteMaxTime; };

};

