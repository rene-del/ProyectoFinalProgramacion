#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"

#include "Player.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	virtual void init();
	virtual void update(Player* player);
	virtual void render();

	virtual bool checkCollision(SDL_Rect);

	bool getIsDead() { return _isDead; };

	void setIsDead(bool val) { _isDead = val; };

protected:
	bool _isDead;
};

#endif

