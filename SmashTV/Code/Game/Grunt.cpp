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

	_isDead = true;

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
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Grunt.png");
	_imgDead = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Grunt_Death.png");

	_dst.w = 64;
	_dst.h = 128;
	_dst.x = 160;
	_dst.y = 80;

	_src.w = 32;
	_src.h = 57;
	_src.x = 0;
	_src.y = 0;

}

void Grunt::update()
{
	_contador++;
	
	//50 x 55
	if (_isDead)
	{
		_src.w = 50;
		_src.h = 100;
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
