#ifndef BLOBBULLET_H
#define BLOBBULLET_H

#include "SDL.h"

class BlobBullet
{
public:
	BlobBullet();
	~BlobBullet();

	void init(int x, int y, int w, int h);
	void update();
	void render();

	int getLimit() { return _limit; };

	SDL_Rect getRect() { return _dst; };

private:
	int _img;
	int _limit;

	SDL_Rect _src;
	SDL_Rect _dst;
};

#endif;

