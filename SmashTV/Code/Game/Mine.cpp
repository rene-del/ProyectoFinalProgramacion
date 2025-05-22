#include "Mine.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

#include <iostream>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;


Mine::Mine()
{
	_img = 0;
	_imgExplosion = 0;
	_currSprite = 0;
	_speed = 0;
	_contador = 0;

	_isTouched = true;

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

}

Mine::~Mine()
{
}

void Mine::init()
{

	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Mine.png");
	_imgExplosion = RESOURCE_MANAGER->loadAndGetGraphicID("Asset/Enemies/Explosion.png");
	_dst.w = 32;
	_dst.h = 32;
	_dst.x = 180;
	_dst.y = 90;

	_src.w = 14;
	_src.h = 12;
	_src.x = 0;
	_src.y = 0;
}

void Mine::update()
{//96 X 96
	if (_isTouched)
	{
		_src.w = _src.h = 96;
		bool endAnim = false;

		if (_contador > 100)
		{
			if (!endAnim)
			{
				if (_src.x < _src.w * 12)
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

void Mine::render()
{
	if (_isTouched)
	{
		VIDEO->renderGraphic(_img, _src, _dst);
	}
	else
	{
		VIDEO->renderGraphic(_imgExplosion, _src, _dst);
	}

}

void Mine::checkMapLimits()
{
}

bool Mine::checkPlayerCollision(SDL_Rect rectPlayer)
{

	if (
		_dst.x < rectPlayer.x + (rectPlayer.w - 20) &&
		rectPlayer.x < _dst.x + _dst.w &&
		_dst.y < rectPlayer.y + rectPlayer.h &&
		rectPlayer.y < _dst.y + _dst.h
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
