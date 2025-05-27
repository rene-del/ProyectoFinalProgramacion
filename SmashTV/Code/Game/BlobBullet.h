#ifndef BLOBBULLET_H
#define BLOBBULLET_H

#include "SDL.h"

#include "Player.h"

class BlobBullet
{
public:
	BlobBullet();
	~BlobBullet();

	void init(int x, int y, int w, int h, int dirX, int dirY);
	void update(Player* player);
	void render();

	bool checkCollision(SDL_Rect object);

	int getLimit() { return _limit; };

	SDL_Rect getRect() { return _dst; };

private:
	int _img;
	int _limit;

	int _dirX;
	int _dirY;

	int _speed;

	SDL_Rect _src;
	SDL_Rect _dst;
};

#endif;

