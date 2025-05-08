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
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Bullet.png");
	_dst.w = 10;
	_dst.h = 10;
	_dst.x = (SCREEN_WIDTH / 2) - (_dst.w / 2);
	_dst.y = (SCREEN_HEIGHT / 2) - (_dst.h / 2);

	_src.w = 8;
	_src.h = 7;
	_src.x = 0;
	_src.y = _src.h;

	_velocity = 20;

	_beginBullet = false;
	_shot = false;


}

void Bullet::update()
{
	//std::cout << "X: " << _dst.x << "Y: " << _dst.y << "\n";
	
	if (_shot)
	{
		switch (_direction)
		{
			//up
		case 4:
			if (_beginBullet)
			_dst.y -= _velocity;
			break;
			//down
		case 3:
			if (_beginBullet)
			_dst.y += _velocity;
			break;
			//left
		case 2:
			if (_beginBullet)
			_dst.x -= _velocity;
			break;
			//right
		case 1:
			if (_beginBullet)
			_dst.x += _velocity;
			break;
		default:
			break;
		}
		_bulletTimeLimit++;
		if (_bulletTimeLimit > 50)
		{
			_beginBullet = false;
			_bulletTimeLimit = 0;

			std::cout << "true" << "\n";
			//reset - despawn
			_dst.x = 99999;
			_dst.y = 99999;
		}


	}

	if (_beginBullet)
	{
		std::cout << "bala comenzada" << "\n";
	}
	if (!_beginBullet)
	{
		std::cout << "bala acabada" << "\n";

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
