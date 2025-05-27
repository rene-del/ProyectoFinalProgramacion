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

	int getAudioDead() { return _audioDead; };

	bool getIsDead() { return _isDead; };
	bool getAnimFinished() { return _animFinished; };

	void setIsDead(bool val) { _isDead = val; };

protected:
	int _audioDead;

	bool _isDead;
	bool _animFinished;
};

#endif

