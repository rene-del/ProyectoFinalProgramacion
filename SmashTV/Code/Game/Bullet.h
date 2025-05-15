#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"

#include <vector>

class Bullet
{
private:
	std::vector<int> _img;

	int _velocity;
	int _direction;

	bool _shot;
	bool _beginBullet;

	int _bulletTimeLimit;

	std::vector<SDL_Rect> _vSrc;
	std::vector<SDL_Rect> _vDst;

public:
	Bullet();
	~Bullet();

	void init();
	void update();
	void render();

	void isShoting(int Dir, int x, int y);
	
	void setBulletTimeLimit(Uint32 time) { _bulletTimeLimit = time; };
	
	Uint32 getBulletTimeLimit() { return _bulletTimeLimit; };

	void setImg(int id) { _img[_direction - 1] = id; };
};

#endif

