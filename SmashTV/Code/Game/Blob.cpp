#include "Blob.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"

#include <iostream>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;

Blob::Blob(int pos)
{
	_bullets.resize(0);

	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Blob.png");
	_audioDead = RESOURCE_MANAGER->loadAndGetAudioID("Assets/Audios/blobDeath.wav");

	_currSprite = 0;
	_speed = 0;

	_randomDirectionTimer = 0;
	_preferX = false;

	_dirX = 0.0f;
	_dirY = 0.0f;

	_dst.w = 64;
	_dst.h = 128;

	_dstSmooth.w = 64.0f;
	_dstSmooth.h = 128.0f;

	_src.w = 52;
	_src.h = 75;
	_src.x = 0;
	_src.y = 0;

	switch (pos)
	{
		// TOP
	case 0:
		_dstSmooth.x = static_cast<float>(SCREEN_WIDTH / 2.0f) - _dstSmooth.w / 2.0f;
		_dstSmooth.y = _dstSmooth.h - 40.0f;

		break;

		// BOTTOM
	case 1:
		_dstSmooth.x = static_cast<float>(SCREEN_WIDTH / 2.0f) - _dstSmooth.w / 2.0f;
		_dstSmooth.y = static_cast<float>(SCREEN_HEIGHT) - 40.0f - _dstSmooth.h;

		break;

		// LEFT
	case 2:
		_dstSmooth.x = _dstSmooth.w;
		_dstSmooth.y = static_cast<float>(SCREEN_HEIGHT / 2.0f) - _dstSmooth.h / 2.0f;

		break;

		// RIGHT
	case 3:
		_dstSmooth.x = static_cast<float>(SCREEN_WIDTH) - 40.0f - _dstSmooth.w;
		_dstSmooth.y = static_cast<float>(SCREEN_HEIGHT / 2.0f) - _dstSmooth.h / 2.0f;

		break;
	default:
		break;
	}

	_dst.x = static_cast<int>(_dstSmooth.x);
	_dst.y = static_cast<int>(_dstSmooth.y);

	_spriteMaxTime = 0;
	_nextSpriteCount = 0;

	_actualMovementState = ST_B_ALIVE;

	_contador = 0;

	_reverse = false;
	_isDead = false;
	_animFinished = false;
}

Blob::~Blob()
{
	// DELETE BULLETS
	for (int i = 0; i < _bullets.size(); i++)
	{
		delete _bullets[i];
		_bullets.erase(_bullets.begin() + i);
		i--;
	}
}

void Blob::init()
{
	_speed = 1;

	_spriteMaxTime = 150;
	_nextSpriteCount = 0;

	_isDead = false;
}

void Blob::update(Player* player)
{
	// CHECK BULLETS LIMIT
	if (_bullets.size() > 0)
	{
		for (int i = 0; i < _bullets.size(); i++)
		{
			_bullets[i]->update(player);

			if (_bullets[i]->getLimit() > 150)
			{
				delete _bullets[i];
				_bullets.erase(_bullets.begin() + i);
				i--;
			}
		}
	}

	//COOLDOWN
	_contador++;

	//JUMP (0-1-2-1-0)
	if (_actualMovementState == ST_B_ALIVE)
	{
		// MOVEMENT TOWARDS THE PLAYER
		_randomDirectionTimer++;

		if (_randomDirectionTimer > 60)
		{
			_preferX = (rand() % 2 == 0);
			_randomDirectionTimer = 0;
		}

		float dx = static_cast<float>(player->getPlayerX()) - _dstSmooth.x;
		float dy = static_cast<float>(player->getPlayerY()) - _dstSmooth.y;

		const float epsilon = 1.0f;

		if (_preferX)
		{
			if (std::abs(dx) > epsilon)
			{
				_dirX = (dx > 0) ? 1.0f : -1.0f;
				_dirY = 0.0f;
				_dstSmooth.x += _dirX * _speed;
			}
			else if (std::abs(dy) > epsilon)
			{
				_dirY = (dy > 0) ? 1.0f : -1.0f;
				_dirX = 0.0f;
				_dstSmooth.y += _dirY * _speed;
			}
		}
		else
		{
			if (std::abs(dy) > epsilon)
			{
				_dirY = (dy > 0) ? 1.0f : -1.0f;
				_dirX = 0.0f;
				_dstSmooth.y += _dirY * _speed;
			}
			else if (std::abs(dx) > epsilon)
			{
				_dirX = (dx > 0) ? 1.0f : -1.0f;
				_dirY = 0.0f;
				_dstSmooth.x += _dirX * _speed;
			}
		}

		_dst.x = static_cast<int>(_dstSmooth.x);
		_dst.y = static_cast<int>(_dstSmooth.y);

		// SPRITES
		if (_contador > 20)
		{
			if (!_reverse)
			{
				if (_src.x == 52 * 2)
				{
					_reverse = true;

					BlobBullet* bullet = new BlobBullet();

					int dirX = static_cast<int>(_dirX);
					int dirY = static_cast<int>(_dirY);

					bullet->init(_dst.x, _dst.y, _dst.w, _dst.h, dirX, dirY);
					_bullets.push_back(bullet);
				}
				else
				{
					//+1 FRAME
					_src.x += 52;
				}
			}
			else
			{
				if (_src.x == 0)
				{
					_reverse = false;
				}
				else
				{
					//-1 FRAME
					_src.x -= 52;
				}
			}

			_nextSpriteCount++;
			_contador = 0;
		}
	}

	//DEAD
	else if (_actualMovementState == ST_B_DEAD)
	{
		if (_contador > 50)
		{
			if (!_animFinished)
			{
				//312
				if (_src.x < _src.w * 5)
				{
					_src.x += _src.w;
				}
				else
				{
					_animFinished = true;
				}
			}

			_contador = 0;
		}
	}
}

void Blob::render()
{
	if (!_isDead)
	{
		VIDEO->renderGraphic(_img, _src, _dst);
	}
	else
	{
		VIDEO->renderGraphicSmooth(_img, _src, _dstSmooth);
	}

	if (_bullets.size() > 0)
	{
		for (auto& bullet : _bullets)
		{
			bullet->render();
		}
	}
}

bool Blob::checkCollision(SDL_Rect object)
{
	if (_actualMovementState != ST_B_DEAD)
	{
		if ((_dst.x < object.x + object.w) &&
			(object.x < _dst.x + _dst.w) &&
			(_dst.y < object.y + object.h) &&
			(object.y < _dst.y + _dst.h))
		{
			_actualMovementState = ST_B_DEAD;
			return true;
		}
	}

	return false;
}
