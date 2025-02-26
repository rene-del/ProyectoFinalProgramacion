#include "Player.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"
#include "../Engine/TimeManager.h"

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;
extern TimeManager* TIME_MANAGER;

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

	_actualState = ST_STILL;
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

	_spriteMaxTime = 150;
	_nextSpriteCount = 0;

	_actualState = ST_STILL;
	_actualDir = DIR_DOWN;
}

void Player::update()
{
	
}

void Player::render()
{
	VIDEO->renderGraphic(_img, _src, _dst);
}
