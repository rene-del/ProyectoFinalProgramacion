#include "BlobBullet.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/Audio.h"

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern Audio* AUDIO;

BlobBullet::BlobBullet()
{
	_img = 0;
	_limit = 0;

	_src.x = 0;
	_src.y = 0;
	_src.w = 0;
	_src.h = 0;

	_dst.x = 0;
	_dst.y = 0;
	_dst.w = 0;
	_dst.h = 0;

	_dirX = 0;
	_dirY = 0;
	_speed = 0;
}

BlobBullet::~BlobBullet()
{
}

void BlobBullet::init(int x, int y, int w, int h, int dirX, int dirY)
{
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Blob_Shot.png");

	_src.x = 0;
	_src.y = 0;
	_src.w = 16;
	_src.h = 11;

	_dirX = dirX;
	_dirY = dirY;

	_dst.w = 16;
	_dst.h = 11;

	switch (_dirX)
	{
	case -1:
		_dst.x = x - 10 + (w / 2 - _dst.w / 2);
		_dst.y = y + (h / 2 - _dst.h / 2);

		break;
	case 1:
		_dst.x = x + 10 + (w / 2 + _dst.w / 2);
		_dst.y = y + (h / 2 - _dst.h / 2);

		break;
	default:
		break;
	}

	switch (_dirY)
	{
	case -1:
		_dst.x = x + w / 2;
		_dst.y = y - 10;

		break;
	case 1:
		_dst.x = x + (w / 2 + _dst.w / 2);
		_dst.y = y + h;
		break;
	default:
		break;
	}

	_speed = 2;
}

void BlobBullet::update(Player* player)
{
	// BULLET MOVEMENT
	_dst.x += _dirX * _speed;
	_dst.y += _dirY * _speed;

	// BULLET LIMIT INCREASE
	_limit++;

	// COLLISION WITH PLAYER
	bool collide = checkCollision(player->getPlayerRect());

	if (collide)
	{
		_limit = 151;
		AUDIO->playAudio(-1, player->getAudioHurt(), 0);
		player->setLifes(player->getLifes() - 1);
	}
}

void BlobBullet::render()
{
	VIDEO->renderGraphic(_img, _src, _dst);
}

bool BlobBullet::checkCollision(SDL_Rect object)
{
	if ((_dst.x < object.x + object.w) &&
		(object.x < _dst.x + _dst.w) &&
		(_dst.y < object.y + object.h) &&
		(object.y < _dst.y + _dst.h))
	{
		return true;
	}

	return false;
}
