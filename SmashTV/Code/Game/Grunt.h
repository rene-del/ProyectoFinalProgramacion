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
	int _contador;

	float _speed;

	bool _resetAnim;

	int _randomDirectionTimer;
	bool _preferX;

	SDL_Rect _src;
	SDL_Rect _dst;

	SDL_FRect _dstSmooth;

	Uint32 _spriteMaxTime;
	Uint32 _nextSpriteCount;

	STATES_GRUNT _actualMovementState;

public:

	Grunt(int pos);
	~Grunt();

	void init() override;
	void update(Player* player) override;
	void render() override;

	bool checkCollision(SDL_Rect object) override;

	void setImg(int id) { _img = id; };
	void setCurrentSprite(int val) { _currSprite = val; };
	void setNextSpriteCount(Uint32 time) { _nextSpriteCount = time; };

	void setGruntX(int val) { _dst.x = val; };
	void setGruntY(int val) { _dst.y = val; };

	SDL_Rect getRectGrunt() { return _dst; };

	Uint32 getNextSpriteCoint() { return _nextSpriteCount; };
	Uint32 getSpriteMaxTime() { return _spriteMaxTime; };

	STATES_GRUNT getMovementState() { return _actualMovementState; };
};

#endif

