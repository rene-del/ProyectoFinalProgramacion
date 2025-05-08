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
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Bullets/Bullet.png");
	_dst.w = 10;
	_dst.h = 10;
	_dst.x = (SCREEN_WIDTH / 2) - (_dst.w / 2);
	_dst.y = (SCREEN_HEIGHT / 2) - (_dst.h / 2);

	_src.w = 88;
	_src.h = 48;
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
				_dst.y -= _velocity;
			break;
		
		// DOWN
		case 3:
			if (_beginBullet)
				_dst.y += _velocity;
			break;

		// LEFT
		case 2:
			if (_beginBullet)
				_dst.x -= _velocity;
			break;

		// RIGHT
		case 1:
			if (_beginBullet)
				_dst.x += _velocity;
			break;
		default:
			break;
		}

		_bulletTimeLimit++;
	}
}

void Bullet::render()
{
	VIDEO->renderGraphic(_img, _src, _dst);
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
