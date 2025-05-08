#include "Blob.h"


#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

#include <iostream>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;

Blob::Blob()
{
	_img = 0;
	_bulltetImg = 0;
	_currSprite = 0;
	_speed = 0;
	_numberBullets = 0;

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

	_actualMovementState = ST_E_DEAD;


	_contador = 0;
	_reverse = false;

}

Blob::~Blob()
{
	

}

void Blob::init()
{
	//55 WIDTH ATTACK ANIMATION
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Blob.png");
	_speed = 1;

	
	_dst.w = 64;
	_dst.h = 128;
	_dst.x = (SCREEN_WIDTH / 4) +   (SCREEN_WIDTH / 2);
	_dst.y = 80;

	_src.w = 52;
	_src.h = 75;
	_src.x = 0;
	_src.y = 0;

	_spriteMaxTime = 150;
	_nextSpriteCount = 0;
}

void Blob::update()
{
	//COOLDOWN
	_contador++;
	//JUMP (0-1-2-1-0)
	if (_actualMovementState == ST_E_ALIVE)
	{
		//MOVEMENT
		if (_contador > 20)
		{
			if (!_reverse)
			{
				if (_src.x == 52 * 2)
				{
					_reverse = true;
				}
				if (_src.x != 52 * 2)
				{
					//+1 FRAME
					_src.x += 52;
				}
			}
			if (_reverse)
			{
				if (_src.x == 0)
				{
					_reverse = false;
				}
				if (_src.x != 0)
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
			_dst.x--;
		}
	}

	//DEAD
	if (_actualMovementState == ST_E_DEAD)
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
}

void Blob::checkMapLimits()
{
}
