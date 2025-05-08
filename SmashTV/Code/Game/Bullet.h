#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"

class Bullet
{
private:
	int _img;
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

	void isShoting(int Dir, int x, int y);
	
	void setBulletTimeLimit(Uint32 time) { _bulletTimeLimit = time; };
	
	Uint32 getBulletTimeLimit() { return _bulletTimeLimit; };

	void setImg(int id) { _img = id; };
};

#endif

