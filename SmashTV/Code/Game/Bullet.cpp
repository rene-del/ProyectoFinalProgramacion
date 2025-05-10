#include "Bullet.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

#include <iostream>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;

Bullet::Bullet()
{
	_img = 0;

	_bulletTimeLimit = 0;

	_rotation = 0.0f;

	_shot = false;
	_beginBullet = false;
	_direction = 0;
	_velocity = 0;

	_src.x = 0;
	_src.y = 0;
	_src.h = 0;
	_src.w = 0;

	_dst.x = 0;
	_dst.y = 0;
	_dst.h = 0;
	_dst.w = 0;
}

Bullet::~Bullet()
{
}

void Bullet::init()
{
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Bullets/bullet_down.png");

	_rotation = 0.0f;

	_dst.w = 4;
	_dst.h = 20;
	_dst.x = (SCREEN_WIDTH / 2) - (_dst.w / 2);
	_dst.y = (SCREEN_HEIGHT / 2) - (_dst.h / 2);

	_src.w = 1;
	_src.h = 5;
	_src.x = 0;
	_src.y = 0;

	_velocity = 10;

	_beginBullet = false;
	_shot = false;
}

void Bullet::update()
{	
	if (_shot)
	{
		switch (_direction)
		{		
		// UP
		case 4:
			if (_beginBullet)
			{
				_rotation = 180.0f;
				_dst.y -= _velocity;
			}

			break;
		
		// DOWN
		case 3:
			if (_beginBullet)
			{
				_dst.y += _velocity;
				_rotation = 0.0f;
			}

			break;

		// LEFT
		case 2:
			if (_beginBullet)
			{
				_dst.x -= _velocity;
				_rotation = 90.0f;
			}

			break;

		// RIGHT
		case 1:
			if (_beginBullet)
			{
				_dst.x += _velocity;
				_rotation = -90.0f;
			}

			break;
		default:
			break;
		}

		_bulletTimeLimit++;
	}
}

void Bullet::render()
{
	VIDEO->renderGraphicRotated(_img, _src, _dst, _rotation);
}

void Bullet::isShoting(int Dir, int x, int y)
{
	_shot = true;
	
	if (!_beginBullet)
	{
		_direction = Dir;
		_beginBullet = true;
		_dst.x = x + 32;
		_dst.y = y + 32;
	}
}
