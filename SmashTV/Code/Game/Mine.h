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
	bool _endAnim;
	bool _isNotExploted;

	bool _isTouched;
	bool _cooldownCollision;

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

	bool checkCollision(SDL_Rect object);

	void setImg(int id) { _img = id; };
	
	void setMineX(int val) { _dst.x = val; };
	void setMineY(int val) { _dst.y = val; };

	bool getEndAnim() { return _endAnim; };

	bool getCooldownCollision() { return _cooldownCollision; };
	void setCooldownCollision(bool value) { _cooldownCollision = value; }

	int getMineX() { return _dst.x; };
	int getMineY() { return _dst.y; };

};

