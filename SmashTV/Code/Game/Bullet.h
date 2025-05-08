#pragma once

#include "SDL.h"

class Bullet
{
private:
	int _img;
	int _x;
	int _y;
	int _velocity;

	int _direction;
	bool _shot;
	bool _beginBullet;

	int _bulletTimeLimit;


	SDL_Rect _src;
	SDL_Rect _dst;


public:
	Bullet();
	~Bullet();

	void init();
	void update();
	void render();

	void isShoting(int Dir);
	void resetBulletTimeLimit(Uint32 time) { _bulletTimeLimit = time; };

	void setImg(int id) { _img = id; };

	

};

