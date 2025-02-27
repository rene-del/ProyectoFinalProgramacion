#include "Player.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;

Player::Player()
{
	_img = 0;

	_src.x = 0;
	_src.y = 0;
	_src.w = 0;
	_src.h = 0;

	_dst.w = 0;
	_dst.y = 0;
	_dst.x = 0;
	_dst.y = 0;

	_spriteMaxTime = 0;
	_nextSpriteCount = 0;

	_actualMovementState = ST_STILL;
	_actualAttackingState = ST_NOT_ATTACKING;
	_actualDir = DIR_DOWN;
}

Player::~Player()
{
}

void Player::init()
{
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/PlayerTileset.png");

	_dst.w = 60;
	_dst.h = 60;
	_dst.x = (SCREEN_WIDTH / 2) - (_dst.w / 2);
	_dst.y = (SCREEN_HEIGHT / 2) - (_dst.h / 2);

	_src.w = 26;
	_src.h = 26;
	_src.x = 0;
	_src.y = _src.h;

	_spriteMaxTime = 200;
	_nextSpriteCount = 0;
}

void Player::update()
{
	// CONTROL KEYS


	// CONTROL SPRITES
	if (_actualDir == DIR_DOWN)
	{
		if (_actualMovementState == ST_STILL)
		{
			if (_actualAttackingState == ST_NOT_ATTACKING)
			{
				_src.x = 0;
				_src.y = _src.h;
			}
			else if (_actualAttackingState == ST_ATTACKING)
			{
				_src.x = _src.w;
				_src.y = _src.h;
			}
		}
	}
	else if (_actualDir == DIR_UP)
	{

	}
	else if (_actualDir == DIR_RIGHT)
	{

	}
	else if (_actualDir == DIR_LEFT)
	{

	}
}

void Player::render()
{
	VIDEO->renderGraphic(_img, _src, _dst);
}
