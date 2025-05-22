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
	bool _endAnim;
	bool _isNotExploted;

	bool _isTouched;
	bool _cooldownCollision;

	SDL_Rect _src;
	SDL_Rect _dst;

	Uint32 _spriteMaxTime;
	Uint32 _nextSpriteCount;

public:
	Mine(int x, int y, int dir);
	~Mine();

	void init() override;
	void update() override;
	void render() override;

	bool checkCollision(SDL_Rect object);

	void setImg(int id) { _img = id; };
	
	void setMineX(int val) { _dst.x = val; };
	void setMineY(int val) { _dst.y = val; };

	bool getEndAnim() { return _endAnim; };

	bool getCooldownCollision() { return _cooldownCollision; };
	void setCooldownCollision(bool value) { _cooldownCollision = value; }

	int getMineX() { return _dst.x; };
	int getMineY() { return _dst.y; };

	void setIsTouched(bool val) { _isTouched = val; };

	bool getIsTouched() { return _isTouched; };
};

#endif

