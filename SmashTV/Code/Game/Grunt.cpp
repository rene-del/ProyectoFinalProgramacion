#include "Grunt.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

#include <iostream>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;


Grunt::Grunt()
{
	_img = 0;
	_imgDead = 0;
	_currSprite = 0;
	_speed = 0;
	_contador = 0;

	_isDead = false;
	_endAnim = false;
	_resetAnim = false;

	_src.x = 0;
	_src.y = 0;
	_src.h = 0;
	_src.w = 0;

	_dst.x = 0;
	_dst.y = 0;
	_dst.h = 0;
	_dst.w = 0;

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

	_dst.w = 64;
	_dst.h = 64;
	_dst.x = 160;
	_dst.y = 160;

	_src.w = 34;
	_src.h = 34;
	_src.x = 0;
	_src.y = 0;

}

void Grunt::update()
{
	_contador++;
	if (!_isDead)
	{
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

	if (_isDead)
	{
		if (_src.x != 0 && !_resetAnim)
		{
			_src.x = 0;
			_resetAnim = true;
		}

		_src.w = _src.h = 96;
		_dst.w = _dst.h = 64;

		_endAnim = false;
		if (_contador > 10)
		{
			if (!_endAnim)
			{
				if (_src.x < _src.w * 13)
				{
					_src.x += _src.w;
				}
				else
				{
					_endAnim = true;
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
		VIDEO->renderGraphic(_img, _src, _dst);
	}
	if (_isDead)
	{
		VIDEO->renderGraphic(_imgDead, _src, _dst);
	}
}

void Grunt::checkMapLimits()
{
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

