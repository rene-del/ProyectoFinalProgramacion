#ifndef GRUNT_H
#define GRUNT_H

#include "SDL.h"
#include "Enemy.h"

enum STATES_GRUNT { ST_G_STILL, ST_G_MOVING, ST_G_DEAD, ST_G_ALIVE };

class Grunt : public Enemy
{
private:
	int _img;
	int _imgDead;
	int _currSprite;
	int _speed;
	int _contador;

	bool _isDead;
	bool _endAnim;
	bool _resetAnim;

	SDL_Rect _src;
	SDL_Rect _dst;

	Uint32 _spriteMaxTime;
	Uint32 _nextSpriteCount;

	STATES_GRUNT _actualMovementState;

	


public:

	Grunt(int x, int y, int dir);
	~Grunt();

	void init() override;
	void update() override;
	void render() override;

	void checkMapLimits();
	bool checkCollision(SDL_Rect object);

	void setImg(int id) { _img = id; };
	void setCurrentSprite(int val) { _currSprite = val; };
	void setNextSpriteCount(Uint32 time) { _nextSpriteCount = time; };

	void setGruntX(int val) { _dst.x = val; };
	void setGruntY(int val) { _dst.y = val; };

	SDL_Rect getRectGrunt() { return _dst; };

	Uint32 getNextSpriteCoint() { return _nextSpriteCount; };
	Uint32 getSpriteMaxTime() { return _spriteMaxTime; };

	STATES_GRUNT getMovementState() { return _actualMovementState; };

	void setIsDead(bool val) { _isDead = val; };

	bool getIsDead() { return _isDead; };
};

#endif

