#include "Grunt.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

#include <iostream>
#include <math.h>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;

Grunt::Grunt(int pos)
{
	_img = 0;
	_imgDead = 0;

	_currSprite = 0;
	_speed = 0.0f;
	_contador = 0;

	_audioDead = 0;

	_isDead = false;
	_animFinished = false;

	_resetAnim = false;

	_randomDirectionTimer = 0;
	_preferX = true;

	_dst.w = 64;
	_dst.h = 64;

	_dstSmooth.w = 64.0f;
	_dstSmooth.h = 64.0f;

	_src.w = 34;
	_src.h = 34;
	_src.x = 0;
	_src.y = 0;

	switch (pos)
	{
		// TOP
	case 0:
		_dstSmooth.x = static_cast<float>(SCREEN_WIDTH / 2.0f) - _dstSmooth.w / 2.0f;
		_dstSmooth.y = 40.0f + _dstSmooth.h;

		break;

		// BOTTOM
	case 1:
		_dstSmooth.x = static_cast<float>(SCREEN_WIDTH / 2.0f) - _dstSmooth.w / 2.0f;
		_dstSmooth.y = static_cast<float>(SCREEN_HEIGHT) - 40.0f - _dstSmooth.h;

		break;

		// LEFT
	case 2:
		_dstSmooth.x = 40.0f + _dstSmooth.w;
		_dstSmooth.y = static_cast<float>(SCREEN_HEIGHT / 2.0f) - _dstSmooth.h / 2.0f;

		break;

		// RIGHT
	case 3:
		_dstSmooth.x = static_cast<float>(SCREEN_WIDTH) - 40.0f - _dstSmooth.w;
		_dstSmooth.y = static_cast<float>(SCREEN_HEIGHT / 2.0f) - _dstSmooth.h / 2.0f;

		break;
	default:
		break;
	}

	_dst.x = static_cast<int>(_dstSmooth.x);
	_dst.y = static_cast<int>(_dstSmooth.y);

	_spriteMaxTime = 0;
	_nextSpriteCount = 0;

	_actualMovementState = ST_G_ALIVE;
}

Grunt::~Grunt()
{
}

void Grunt::init()
{
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/EnemyBlade.png");
	_imgDead = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Explosion.png");

	_audioDead = RESOURCE_MANAGER->loadAndGetAudioID("Assets/Audios/enemyExplosion.wav");

	_speed = 1.0f;
}

void Grunt::update(Player* player)
{
	_contador++;

	if (!_isDead)
	{
		// MOVEMENT TOWARDS THE PLAYER
		_randomDirectionTimer++;

		if (_randomDirectionTimer > 60)
		{
			_preferX = (rand() % 2 == 0);
			_randomDirectionTimer = 0;
		}

		float dx = static_cast<float>(player->getPlayerX()) - _dstSmooth.x;
		float dy = static_cast<float>(player->getPlayerY()) - _dstSmooth.y;

		const float epsilon = 1.0f;

		if (_preferX)
		{
			if (std::abs(dx) > epsilon)
			{
				float dirX = (dx > 0) ? 1.0f : -1.0f;
				_dstSmooth.x += dirX * _speed;
			}
			else if (std::abs(dy) > epsilon)
			{
				float dirY = (dy > 0) ? 1.0f : -1.0f;
				_dstSmooth.y += dirY * _speed;
			}
		}
		else
		{
			if (std::abs(dy) > epsilon)
			{
				float dirY = (dy > 0) ? 1.0f : -1.0f;
				_dstSmooth.y += dirY * _speed;
			}
			else if (std::abs(dx) > epsilon)
			{
				float dirX = (dx > 0) ? 1.0f : -1.0f;
				_dstSmooth.x += dirX * _speed;
			}
		}

		_dst.x = static_cast<int>(_dstSmooth.x);
		_dst.y = static_cast<int>(_dstSmooth.y);

		// SPRITES
		if (_contador > 2)
		{
			if (_src.x < _src.w * 7)
			{
				_src.x += _src.w;
			}
			else
			{
				_src.x = 0;
			}
			_contador = 0;
		}
	}

	//50 x 55

	else
	{
		if (_src.x != 0 && !_resetAnim)
		{
			_src.x = 0;
			_resetAnim = true;
		}

		_src.w = _src.h = 96;
		_dst.w = _dst.h = 64;

		if (_contador > 10)
		{
			if (!_animFinished)
			{
				if (_src.x < _src.w * 13)
				{
					_src.x += _src.w;
				}
				else
				{
					_animFinished = true;
				}
			}
			_contador = 0;
		}

	}
}

void Grunt::render()
{
	if (!_isDead)
	{
		VIDEO->renderGraphicSmooth(_img, _src, _dstSmooth);
	}
	else
	{
		VIDEO->renderGraphic(_imgDead, _src, _dst);
	}
}

bool Grunt::checkCollision(SDL_Rect object)
{
	if (_actualMovementState != ST_G_DEAD)
	{
		if ((_dst.x < object.x + object.w) &&
			(object.x < _dst.x + _dst.w) &&
			(_dst.y < object.y + object.h) &&
			(object.y < _dst.y + _dst.h))
		{
			_actualMovementState = ST_G_DEAD;
			return true;
		}
	}

	return false;
}

