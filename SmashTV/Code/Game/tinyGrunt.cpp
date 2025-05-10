#include "tinyGrunt.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

#include <iostream>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;


tinyGrunt::tinyGrunt()
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

	_actualMovementState = ST_TG_ALIVE;
}

tinyGrunt::~tinyGrunt()
{
	
}

void tinyGrunt::init()
{
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/TinyGrunt.png");
	_imgDead = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/TinyGrunt_Death.png");

	_dst.w = 32;
	_dst.h = 32;
	_dst.x = 160;
	_dst.y = 120;

	_src.w = 20;
	_src.h = 23;
	_src.x = 0;
	_src.y = 0;
}

void tinyGrunt::update()
{
	_contador++;
	//35 x 40

	if (_isDead)
	{
		_src.w = 35;
		_src.h = 40;
		//1st frame is the same as iddle frame
		
		bool endAnim = false;
		if (_contador > 100)
		{
			if (!endAnim)
			{
				if (_src.x < _src.w * 9)
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

void tinyGrunt::render()
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

void tinyGrunt::checkMapLimits()
{
}
