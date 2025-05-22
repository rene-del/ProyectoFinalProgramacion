#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
public:
	Enemy();
	~Enemy();

	virtual void init();
	virtual void update();
	virtual void render();
};

#endif

