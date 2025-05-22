#include "Blob.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

#include "Player.h"

#include <iostream>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;

extern Player PLAYER;

Blob::Blob(int x, int y, int dir)
{
	_bullets.resize(0);

	_img = 0;
	_currSprite = 0;
	_speed = 0;

	_src.x = 0;
	_src.y = 0;
	_src.w = 0;
	_src.h = 0;

	_dst.x = x;
	_dst.y = y;
	_dst.w = 0;
	_dst.h = 0;

	_spriteMaxTime = 0;
	_nextSpriteCount = 0;

	_actualMovementState = ST_B_ALIVE;

	_contador = 0;
	_reverse = false;
	_isDead = false;
}

Blob::~Blob()
{
	// DELETE BULLETS
	for (int i = 0; i < _bullets.size(); i++)
	{
		delete _bullets[i];
		_bullets.erase(_bullets.begin() + i);
		i--;
	}
}

void Blob::init()
{
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Blob.png");
	_speed = 1;
	
	_dst.w = 64;
	_dst.h = 128;

	_src.w = 52;
	_src.h = 75;
	_src.x = 0;
	_src.y = 0;

	_spriteMaxTime = 150;
	_nextSpriteCount = 0;

	_isDead = false;
}

void Blob::update()
{
	// CHECK BULLETS LIMIT
	if (_bullets.size() > 0)
	{
		for (int i = 0; i < _bullets.size(); i++)
		{
			_bullets[i]->update();

			if (_bullets[i]->getLimit() > 150)
			{
				delete _bullets[i];
				_bullets.erase(_bullets.begin() + i);
				i--;
			}
		}
	}

	//COOLDOWN
	_contador++;

	//JUMP (0-1-2-1-0)
	if (_actualMovementState == ST_B_ALIVE)
	{
		//MOVEMENT
		if (_contador > 20)
		{
			if (!_reverse)
			{
				if (_src.x == 52 * 2)
				{
					_reverse = true;

					BlobBullet* bullet = new BlobBullet();
					bullet->init(_dst.x, _dst.y, _dst.w, _dst.h);
					_bullets.push_back(bullet);
				}
				else
				{
					//+1 FRAME
					_src.x += 52;
				}
			}
			else
			{
				if (_src.x == 0)
				{
					_reverse = false;
				}
				else
				{
					//-1 FRAME
					_src.x -= 52;
				}
			}

			_nextSpriteCount++;
			_contador = 0;
		}

		//DIRECTIONS
		if (true)
		{
			//_dst.x --;
		}
	}

	//DEAD
	if (_actualMovementState == ST_B_DEAD)
	{
		bool endAnim = false;

		if (_contador > 50)
		{
			if (!endAnim)
			{
				//312
				if (_src.x < _src.w * 5)
				{
					_src.x += _src.w;
				}
				else
				{
					endAnim = true;
				}
			}

			_contador = 0;
		}
	}
}

void Blob::render()
{
	VIDEO->renderGraphic(_img, _src, _dst);

	if (_bullets.size() > 0)
	{
		for (auto& bullet : _bullets)
		{
			bullet->render();
		}
	}
}

bool Blob::checkCollision(SDL_Rect object)
{
	if (_actualMovementState != ST_B_DEAD)
	{
		if ((_dst.x < object.x + object.w) &&
			(object.x < _dst.x + _dst.w) &&
			(_dst.y < object.y + object.h) &&
			(object.y < _dst.y + _dst.h))
		{
			_actualMovementState = ST_B_DEAD;
			return true;
		}
	}

	return false;
}
