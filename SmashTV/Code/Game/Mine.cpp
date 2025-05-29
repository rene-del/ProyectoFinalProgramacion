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

	_audioDead = 0;

	_src.w = 14;
	_src.h = 12;
	_src.x = 0;
	_src.y = 0;

	_dst.h = 28;
	_dst.w = 24;

	_spriteMaxTime = 0;
	_nextSpriteCount = 0;

	switch (pos)
	{
		// TOP
	case 0:
		_dst.x = SCREEN_WIDTH / 2 - _dst.w / 2;
		_dst.y = 40 + _dst.h;

		break;

		// BOTTOM
	case 1:
		_dst.x = SCREEN_WIDTH / 2 - _dst.w / 2;
		_dst.y = SCREEN_HEIGHT - 40 - _dst.h;

		break;

		// LEFT
	case 2:
		_dst.x = 40 + _dst.w;
		_dst.y = SCREEN_HEIGHT / 2 - _dst.h / 2;

		break;

		// RIGHT
	case 3:
		_dst.x = SCREEN_WIDTH - 40 - _dst.w;
		_dst.y = SCREEN_HEIGHT / 2 - _dst.h / 2;

		break;
	default:
		break;
	}
}

Mine::~Mine()
{
}

void Mine::init()
{
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Mine.png");
	_imgExplosion = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Explosion.png");

	_audioDead = RESOURCE_MANAGER->loadAndGetAudioID("Assets/Audios/enemyExplosion.wav");
}

void Mine::update(Player* player)
{//96 X 96

	_contador++;

	
	if (_isDead)
	{
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
					_isNotExploted = false;
				}
			}

			_contador = 0;
		}

	}
}

void Mine::render()
{
	if (_isNotExploted)
	{
		if (!_isDead)
		{
			VIDEO->renderGraphic(_img, _src, _dst);
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
