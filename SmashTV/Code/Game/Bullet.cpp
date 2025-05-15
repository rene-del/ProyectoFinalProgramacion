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
	_img.resize(0);

	_bulletTimeLimit = 0;

	_shot = false;
	_beginBullet = false;
	_direction = 0;
	_velocity = 0;

	_vSrc.resize(0);
	_vDst.resize(0);
}

Bullet::~Bullet()
{
}

void Bullet::init()
{
	_img.push_back(RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Bullets/Bullet_Right.png"));
	_img.push_back(RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Bullets/Bullet_Left.png"));
	_img.push_back(RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Bullets/Bullet_Down.png"));
	_img.push_back(RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Bullets/Bullet_Up.png"));

	SDL_Rect _src;
	SDL_Rect _dst;

	for (int i = 0; i < 2; i++)
	{
		_src.w = 5;
		_src.h = 2;
		_src.x = 0;
		_src.y = 0;

		_dst.w = 20;
		_dst.h = 4;

		_vSrc.push_back(_src);
		_vDst.push_back(_dst);
	}

	for (int i = 0; i < 2; i++)
	{
		_src.w = 2;
		_src.h = 5;
		_src.x = 0;
		_src.y = 0;

		_dst.w = 4;
		_dst.h = 20;

		_vSrc.push_back(_src);
		_vDst.push_back(_dst);
	}

	_velocity = 5;

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
				_vDst[3].y -= _velocity;
			}

			break;
		
		// DOWN
		case 3:
			if (_beginBullet)
			{
				_vDst[2].y += _velocity;
			}

			break;

		// LEFT
		case 2:
			if (_beginBullet)
			{
				_vDst[1].x -= _velocity;
			}

			break;

		// RIGHT
		case 1:
			if (_beginBullet)
			{
				_vDst[0].x += _velocity;
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
	VIDEO->renderGraphic(_img[_direction - 1], _vSrc[_direction - 1], _vDst[_direction - 1]);
}

void Bullet::isShoting(int Dir, int x, int y)
{
	_shot = true;
	
	if (!_beginBullet)
	{
		_direction = Dir;
		_beginBullet = true;

		switch (_direction)
		{
		// UP
		case 4:
			_vDst[3].x = x + 35;
			_vDst[3].y = y - 20;
			break;

		// DOWN
		case 3:
			_vDst[2].x = x + 42;
			_vDst[2].y = y + 50;
			break;

		// LEFT
		case 2:
			_vDst[1].x = x - 10;
			_vDst[1].y = y + 14;
			break;

		// RIGHT
		case 1:
			_vDst[0].x = x + 70;
			_vDst[0].y = y + 14;
			break;
		default:
			break;
		}
	}
}
