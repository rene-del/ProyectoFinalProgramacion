#include "Mine.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

#include <iostream>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;

Mine::Mine(int pos)
{
	_img = 0;
	_imgExplosion = 0;

	_currSprite = 0;
	_speed = 0;
	_contador = 0;

	_isDead = false;
	_animFinished = false;
	_cooldownCollision = false;
	_isNotExploted = true;

	_randomDirectionTimer = 0;
	_preferX = true;

	_audioDead = 0;

	_src.w = 14;
	_src.h = 12;
	_src.x = 0;
	_src.y = 0;

	_dst.h = 42;
	_dst.w = 38;

	_dstSmooth.h = 28.0f;
	_dstSmooth.w = 24.0f;

	_spriteMaxTime = 0;
	_nextSpriteCount = 0;

	switch (pos)
	{
		// TOP
	case 0:
		_dstSmooth.x = static_cast<float>(SCREEN_WIDTH / 2.0f) - _dstSmooth.w / 2.0f;
		_dstSmooth.y = _dstSmooth.h;

		break;

		// BOTTOM
	case 1:
		_dstSmooth.x = static_cast<float>(SCREEN_WIDTH / 2.0f) - _dstSmooth.w / 2.0f;
		_dstSmooth.y = static_cast<float>(SCREEN_HEIGHT) - 40.0f - _dstSmooth.h;

		break;

		// LEFT
	case 2:
		_dstSmooth.x = _dstSmooth.w;
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
}

Mine::~Mine()
{
}

void Mine::init()
{
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Mine.png");
	_imgExplosion = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Explosion.png");

	_audioDead = RESOURCE_MANAGER->loadAndGetAudioID("Assets/Audios/enemyExplosion.wav");

	_speed = 1.0f;
}

void Mine::update(Player* player)
{//96 X 96

	_contador++;
	
	if (_isDead)
	{
		_src.w = _src.h = 96;

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
					_isNotExploted = false;
				}
			}

			_contador = 0;
		}
	}
	else
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
	}
}

void Mine::render()
{
	if (_isNotExploted)
	{
		if (!_isDead)
		{
			VIDEO->renderGraphicSmooth(_img, _src, _dstSmooth);
		}
		else
		{
			VIDEO->renderGraphic(_imgExplosion, _src, _dst);
		}
	}

}

bool Mine::checkCollision(SDL_Rect object)
{
	if ((_dst.x < object.x + object.w) &&
		(object.x < _dst.x + _dst.w) &&
		(_dst.y < object.y + object.h) &&
		(object.y < _dst.y + _dst.h))
	{
		return true;
	}

	return false;
}
