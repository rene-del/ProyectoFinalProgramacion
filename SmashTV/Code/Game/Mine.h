#ifndef MINE_H
#define MINE_H

#include "SDL.h"
#include "Enemy.h"

class Mine : public Enemy
{
private:
	int _img;
	int _imgExplosion;
	int _currSprite;
	int _speed;
	int _contador;
	bool _isNotExploted;
	bool _cooldownCollision;
	
	int _randomDirectionTimer;
	bool _preferX;

	SDL_Rect _src;
	SDL_Rect _dst;

	SDL_FRect _dstSmooth;

	Uint32 _spriteMaxTime;
	Uint32 _nextSpriteCount;

public:
	Mine(int pos);
	~Mine();

	void init() override;
	void update(Player* player) override;
	void render() override;

	bool checkCollision(SDL_Rect object) override;

	void setImg(int id) { _img = id; };
	
	void setMineX(int val) { _dst.x = val; };
	void setMineY(int val) { _dst.y = val; };

	bool getCooldownCollision() { return _cooldownCollision; };
	void setCooldownCollision(bool value) { _cooldownCollision = value; }

	int getMineX() { return _dst.x; };
	int getMineY() { return _dst.y; };
};

#endif

