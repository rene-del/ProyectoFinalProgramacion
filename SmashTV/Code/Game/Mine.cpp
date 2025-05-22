#include "Mine.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

#include <iostream>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;


Mine::Mine(int x, int y, int dir)
{
	_img = 0;
	_imgExplosion = 0;
	_currSprite = 0;
	_speed = 0;
	_contador = 0;

	_isTouched = false;
	_endAnim = false;
	_cooldownCollision = false;
	_isNotExploted = true;


	_src.x = 0;
	_src.y = 0;
	_src.h = 0;
	_src.w = 0;

	_dst.x = x;
	_dst.y = y;
	_dst.h = 0;
	_dst.w = 0;

	_spriteMaxTime = 0;
	_nextSpriteCount = 0;

}

Mine::~Mine()
{
}

void Mine::init()
{

	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Mine.png");
	_imgExplosion = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Explosion.png");
	_dst.w = 32;
	_dst.h = 32;

	_src.w = 14;
	_src.h = 12;
	_src.x = 0;
	_src.y = 0;
}

void Mine::update()
{//96 X 96

	_contador++;

	
	if (_isTouched)
	{
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
		if (!_isTouched)
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
		_isTouched = true;
		return _isTouched;
	}

	return _isTouched;
}
