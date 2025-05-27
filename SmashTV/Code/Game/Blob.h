#ifndef BLOB_H
#define BLOB_H

#include "SDL.h"
#include "Enemy.h"
#include "BlobBullet.h"

#include <vector>

//constant movement
enum STATES_BLOB {ST_B_STILL, ST_B_MOVING, ST_B_DEAD, ST_B_ALIVE};

class Blob : public Enemy
{
private:
	std::vector<BlobBullet*> _bullets;

	int _img;
	int _currSprite;
	int _speed;
	int _contador;
	
	bool _reverse;

	int _randomDirectionTimer;
	bool _preferX;

	float _dirX;
	float _dirY;

	SDL_Rect _src;
	SDL_Rect _dst;
	
	SDL_FRect _dstSmooth;

	Uint32 _spriteMaxTime;
	Uint32 _nextSpriteCount;

	STATES_BLOB _actualMovementState;
	

public:
	Blob(int x, int y);
	~Blob();

	void init() override;
	void update(Player* player) override;
	void render() override;

	bool checkCollision(SDL_Rect object) override;

	void setImg(int id) { _img = id; };
	void setCurrentSprite(int val) { _currSprite = val; };
	void setNextSpriteCount(Uint32 time) { _nextSpriteCount = time; };

	void setBlobX(int val) { _dst.x = val; };
	void setBlobY(int val) { _dst.y = val; };

	void setIsDead(bool val) { _isDead = val; };

	bool getIsDead() { return _isDead; };

	int getBlobX() { return _dst.x; };
	int getBlobY() { return _dst.y; };

	Uint32 getNextSpriteCoint() { return _nextSpriteCount; };
	Uint32 getSpriteMaxTime() { return _spriteMaxTime; };

	STATES_BLOB getMovementState() { return _actualMovementState; };

	std::vector<BlobBullet*> getBullets() { return _bullets; };

	void setBulletsVector(std::vector<BlobBullet*> val) { _bullets = val; };
};

#endif

