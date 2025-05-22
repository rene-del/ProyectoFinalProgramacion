#include "Mummy.h"


#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

#include <iostream>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;


Mummy::Mummy()
{
	_img = 0;
	_imgDead = 0;
	_currSprite = 0;
	_speed = 0;
	_contador = 0;

	_isDead = true;

	_src.x = 0;
	_src.y = 0;
	_src.w = 0;
	_src.h = 0;

	_dst.x = 0;
	_dst.y = 0;
	_dst.w = 0;
	_dst.h = 0;

	_spriteMaxTime = 0;
	_nextSpriteCount = 0;

	_actualMovementState = ST_M_STILL;


}

Mummy::~Mummy()
{
}

void Mummy::init()
{
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Mummy.png");
	_imgDead = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Mummy_Death.png");
	
	_dst.w = 64;
	_dst.h = 128;
	_dst.x = 120;
	_dst.y = 80;

	_src.w = 33;
	_src.h = 50;
	_src.x = 0;
	_src.y = 0;

}

void Mummy::update()
{
	_contador++;

	//33 x 47
	if (_isDead)
	{
		_src.w = 33;
		_src.h = 47;
		bool endAnim = false;
		if (_contador > 10)
		{
			if (!endAnim)
			{
				if (_src.x < _src.w * 11)
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

void Mummy::render()
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

void Mummy::checkMapLimits()
{
}

void Mummy::checkPlayerCollision(SDL_Rect rectPlayer)
{
	if (
		_dst.x < rectPlayer.x + (rectPlayer.w - 20) &&
		rectPlayer.x < _dst.x + _dst.w &&
		_dst.y < rectPlayer.y + rectPlayer.h &&
		rectPlayer.y < _dst.y + _dst.h
		)
	{
		std::cout << "colision con jugador" << "\n";
	}
}
