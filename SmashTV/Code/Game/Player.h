#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"

#include "Bullet.h"
#include <vector>

class Player
{
private:
	enum STATES { ST_STILL, ST_MOVING, ST_NOT_ATTACKING, ST_ATTACKING, ST_DEAD };
	enum DIRECTION { DIR_NONE, DIR_RIGHT, DIR_LEFT, DIR_DOWN, DIR_UP };

	int _img;
	int _currSprite;
	int _speed;
	int _shootingCooldown;
	int _lifes;

	int _audioGun;
	int _audioHurt;

	bool _endAnim;

	SDL_Rect _src;
	SDL_Rect _dst;

	Uint32 _spriteMaxTime;
	Uint32 _nextSpriteCount;

	STATES _actualMovementState;
	STATES _actualAttackingState;

	std::vector<Bullet*> _bullets;

	std::vector<DIRECTION> _directionStack;
	DIRECTION _lastDir;

	DIRECTION getLastDir();
	void updateDirectionStack();

public:
	Player();
	~Player();

	void init();
	void update();
	void render();

	void checkMapLimits();

	void setImg(int id) { _img = id; };
	void setCurrSprite(int val) { _currSprite = val; };
	void setLifes(int val) { _lifes = val; };
	void setNextSpriteCount(Uint32 time) { _nextSpriteCount = time; };

	void setBulletsVector(std::vector<Bullet*> val) { _bullets = val; };

	void setPlayerX(int val) { _dst.x = val; };
	void setPlayerY(int val) { _dst.y = val; };

	int getPlayerX() { return _dst.x; };
	int getPlayerY() { return _dst.y; };
	int getLifes() { return _lifes; };
	int getAudioHurt() { return _audioHurt; };

	bool getEndAnim() { return _endAnim; };

	SDL_Rect getPlayerRect() { return _dst; };

	Uint32 getNextSpriteCount() { return _nextSpriteCount; };
	Uint32 getSpriteMaxTime() { return _spriteMaxTime; };

	STATES getMovementState() { return _actualMovementState; };
	STATES getAttackingState() { return _actualAttackingState; };

	std::vector<Bullet*> getBullets() { return _bullets; };

	DIRECTION getCurrentDirection();
	DIRECTION getPrevDirection();

	DIRECTION getLastDir() const { return _lastDir; }
	void resetLastDir() { _lastDir = DIR_DOWN; }
};

#endif

