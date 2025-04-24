#include "Bullet.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;

Bullet::Bullet()
{
	_img = 0;

	_travel = false;
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
	_dst.w = 84;
	_dst.h = 48;
	_dst.x = (SCREEN_WIDTH / 2) - (_dst.w / 2);
	_dst.y = (SCREEN_HEIGHT / 2) - (_dst.h / 2);

	_src.w = 200;
	_src.h = 26;
	_src.x = 0;
	_src.y = _src.h;

	_velocity = 20;

}

void Bullet::update()
{
	bool space = INPUT_MANAGER->getKeyState(SDL_SCANCODE_SPACE);

	bool up = INPUT_MANAGER->getKeyState(SDL_SCANCODE_UP);
	bool down = INPUT_MANAGER->getKeyState(SDL_SCANCODE_DOWN);
	bool left = INPUT_MANAGER->getKeyState(SDL_SCANCODE_LEFT);
	bool right = INPUT_MANAGER->getKeyState(SDL_SCANCODE_RIGHT);



	if (space)
	{
		_travel = true;
	}


	if (_travel)
	{
		if (up)
		{
			_direction = 0;
		}
		if (down)
		{
			_direction = 1;
		}
		if (left)
		{
			_direction = 2;
		}
		if (right)
		{
			_direction = 3;
		}
		
		switch (_direction)
		{
			//up
		case 0:
			_dst.y -= _velocity;
			break;
			//down
		case 1:
			_dst.y += _velocity;
			break;
			//left
		case 2:
			_dst.x -= _velocity;
			break;
			//right
		case 3:
			_dst.x += _velocity;
			break;
		default:
			break;
		}

	}

}

void Bullet::render()
{
	VIDEO->renderGraphic(_img, _src, _dst);
}
