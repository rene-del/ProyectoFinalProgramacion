#pragma once

#include "SDL.h"

class Bullet
{
private:
	int _img;
	int _x;
	int _y;

	SDL_Rect _src;
	SDL_Rect _dst;


public:
	Bullet();
	~Bullet();

	void init();
	void update();
	void render();

	void setImg(int id) { _img = id; };

};

