#include "Player.h"
#include "Bullet.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/Audio.h"
#include "../Engine/InputManager.h"

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern Audio* AUDIO;
extern InputManager* INPUT_MANAGER;

Player::Player()
{
	_img = 0;
	_audioGun = 0;
	_audioHurt = 0;

	_currSprite = 0;
	_speed = 0;
	_shootingCooldown = 0;
	_lifes = 0;

	_endAnim = false;

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

	_actualMovementState = ST_STILL;
	_actualAttackingState = ST_NOT_ATTACKING;

	_bullets.clear();

	_lastDir = DIR_DOWN;
}

Player::~Player()
{
	// DELETE BULLETS
	for (int i = 0; i < _bullets.size(); i++)
	{
		delete _bullets[i];
		_bullets.erase(_bullets.begin() + i);
		i--;
	}
}

void Player::init()
{
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Player/PlayerTileset.png");
	_audioGun = RESOURCE_MANAGER->loadAndGetAudioID("Assets/Audios/gunShot.wav");
	_audioHurt = RESOURCE_MANAGER->loadAndGetAudioID("Assets/Audios/playerHurt.wav");

	_currSprite = 0;
	_speed = 2;
	_shootingCooldown = 0;
	_lifes = 3;

	_endAnim = false;

	_dst.w = 80;
	_dst.h = 80;
	_dst.x = (SCREEN_WIDTH / 2) - (_dst.w / 2);
	_dst.y = (SCREEN_HEIGHT / 2) - (_dst.h / 2);

	_src.w = 26;
	_src.h = 26;
	_src.x = 0;
	_src.y = _src.h;

	_spriteMaxTime = 150;
	_nextSpriteCount = 0;

	_actualMovementState = ST_STILL;
	_actualAttackingState = ST_NOT_ATTACKING;

	resetLastDir();
}

void Player::update()
{
	// CURRENT DIRECTION
	updateDirectionStack();
	DIRECTION actualDir = getCurrentDirection();

	// CONTROL KEYS
	bool space = INPUT_MANAGER->getKeyState(SDL_SCANCODE_SPACE);

	if (_bullets.size() > 0)
	{
		for (int i = 0; i < _bullets.size(); i++)
		{
			_bullets[i]->update();

			if (_bullets[i]->getBulletTimeLimit() > 100)
			{
				delete _bullets[i];
				_bullets.erase(_bullets.begin() + i);
				i--;
			}
		}
	}

	// ALIVE
	if (_actualMovementState != ST_DEAD)
	{
		// MOVEMENT STATE
		if (actualDir != DIR_NONE)
		{
			_actualMovementState = ST_MOVING;

			// MOVE TO LAST SAVED DIRECTION
			switch (actualDir)
			{
			// RIGHT
			case DIR_RIGHT:
				if (getPrevDirection() != DIR_LEFT)
				{
					_dst.x += _speed;
				}
				break;

			// LEFT
			case DIR_LEFT:
				if (getPrevDirection() != DIR_RIGHT)
				{
					_dst.x -= _speed;
				}
				break;

			// DOWN
			case DIR_DOWN:
				if (getPrevDirection() != DIR_UP)
				{
					_dst.y += _speed;
				}
				break;

			// UP
			case DIR_UP:
				if (getPrevDirection() != DIR_DOWN)
				{
					_dst.y -= _speed;
				}
				break;
			default:
				break;
			}

			// STILL IF OPPOSITE DIRECTION IS PRESSED

			// RIGHT - LEFT
			if (getCurrentDirection() == DIR_RIGHT)
			{
				if (getPrevDirection() == DIR_LEFT)
				{
					_actualMovementState = ST_STILL;
					actualDir = DIR_LEFT;
				}
			}

			// LEFT - RIGHT
			else if (getCurrentDirection() == DIR_LEFT)
			{
				if (getPrevDirection() == DIR_RIGHT)
				{
					_actualMovementState = ST_STILL;
					actualDir = DIR_RIGHT;
				}
			}

			// UP - DOWN
			else if (getCurrentDirection() == DIR_UP)
			{
				if (getPrevDirection() == DIR_DOWN)
				{
					_actualMovementState = ST_STILL;
					actualDir = DIR_DOWN;
				}
			}

			// DOWN - UP
			else if (getCurrentDirection() == DIR_DOWN)
			{
				if (getPrevDirection() == DIR_UP)
				{
					_actualMovementState = ST_STILL;
					actualDir = DIR_UP;
				}
			}
		}

		// NOT MOVING
		else
		{
			_actualMovementState = ST_STILL;
		}

		// SHOOTING
		if (space)
		{
			_actualAttackingState = ST_ATTACKING;

			// SPAWN BULLET
			if (_shootingCooldown >= 25)
			{
				Bullet* bullet = new Bullet();
				bullet->init();
				_bullets.push_back(bullet);
				AUDIO->playAudio(-1, _audioGun, 0);
				_shootingCooldown = 0;
			}

			// BULLET DIRECTION
			for (auto& bullet : _bullets)
			{
				if (getCurrentDirection() != DIR_NONE)
				{
					bullet->isShoting(getCurrentDirection(), _dst.x, _dst.y);
				}
				else
				{
					bullet->isShoting(getLastDir(), _dst.x, _dst.y);
				}
			}
		}
		else
		{
			_actualAttackingState = ST_NOT_ATTACKING;
		}
	}
	
	// SHOOTING COOLDOWN
	_shootingCooldown++;

	// DEAD
	if (_lifes == -1)
	{
		_actualMovementState = ST_DEAD;
		_nextSpriteCount = 0;
		_lifes--;
	}

	// SPRITES CONTROL

	// NOT DEAD
	if (_actualMovementState != ST_DEAD)
	{
		// NO DIR
		if (actualDir == DIR_NONE)
		{
			switch (getLastDir())
			{
			// LEFT
			case DIR_LEFT:
				_src.y = _src.h * 2;

				// NOT ATTACKING
				if (_actualAttackingState == ST_NOT_ATTACKING)
				{
					_src.x = 0;
				}

				// ATTACKING
				else if (_actualAttackingState == ST_ATTACKING)
				{
					_src.x = _src.w;
				}

				break;

			// RIGHT
			case DIR_RIGHT:
				_src.y = _src.h * 3;

				// NOT ATTACKING
				if (_actualAttackingState == ST_NOT_ATTACKING)
				{
					_src.x = 0;
				}

				// ATTACKING
				else if (_actualAttackingState == ST_ATTACKING)
				{
					_src.x = _src.w;
				}

				break;

			// UP
			case DIR_UP:
				_src.y = 0;

				// NOT ATTACKING
				if (_actualAttackingState == ST_NOT_ATTACKING)
				{
					_src.x = 0;
				}

				// ATTACKING
				else if (_actualAttackingState == ST_ATTACKING)
				{
					_src.x = _src.w;
				}

				break;

			// DOWN
			case DIR_DOWN:
				_src.y = _src.h;

				// NOT ATTACKING
				if (_actualAttackingState == ST_NOT_ATTACKING)
				{
					_src.x = 0;
				}

				// ATTACKING
				else if (_actualAttackingState == ST_ATTACKING)
				{
					_src.x = _src.w;
				}

				break;
			default:
				break;
			}
		}

		// UP
		else if (actualDir == DIR_UP)
		{
			_src.y = 0;

			// STILL
			if (_actualMovementState == ST_STILL)
			{
				if (_actualAttackingState == ST_NOT_ATTACKING)
				{
					_src.x = 0;
				}
				else if (_actualAttackingState == ST_ATTACKING)
				{
					_src.x = _src.w;
				}
			}

			// MOVING
			else if (_actualMovementState == ST_MOVING)
			{
				// NOT ATTACKING
				if (_actualAttackingState == ST_NOT_ATTACKING)
				{
					if (_nextSpriteCount >= _spriteMaxTime)
					{
						switch (_currSprite)
						{
						case 0:
							_src.x = _src.w * 3;
							_currSprite = 1;
							break;
						case 1:
							_src.x = _src.w * 5;
							_currSprite = 2;
							break;
						case 2:
							_src.x = _src.w * 4;
							_currSprite = 3;
							break;
						case 3:
							_src.x = _src.w * 2;
							_currSprite = 0;
							break;
						default:
							break;
						}

						_nextSpriteCount = 0;
					}
				}

				// ATTACKING
				else if (_actualAttackingState == ST_ATTACKING)
				{
					if (_nextSpriteCount >= _spriteMaxTime)
					{
						switch (_currSprite)
						{
						case 0:
							_src.x = _src.w * 7;
							_currSprite = 1;
							break;
						case 1:
							_src.x = _src.w * 8;
							_currSprite = 2;
							break;
						case 2:
							_src.x = _src.w * 9;
							_currSprite = 3;
							break;
						case 3:
							_src.x = _src.w * 6;
							_currSprite = 0;
							break;
						default:
							break;
						}

						_nextSpriteCount = 0;
					}
				}
			}
		}

		// DOWN
		else if (actualDir == DIR_DOWN)
		{
			_src.y = _src.h;

			// STILL
			if (_actualMovementState == ST_STILL)
			{
				if (_actualAttackingState == ST_NOT_ATTACKING)
				{
					_src.x = 0;					
				}
				else if (_actualAttackingState == ST_ATTACKING)
				{
					_src.x = _src.w;
				}
			}

			// MOVING
			else if (_actualMovementState == ST_MOVING)
			{
				// NOT ATTACKING
				if (_actualAttackingState == ST_NOT_ATTACKING)
				{
					if (_nextSpriteCount >= _spriteMaxTime)
					{
						switch (_currSprite)
						{
						case 0:
							_src.x = _src.w * 3;
							_currSprite = 1;
							break;
						case 1:
							_src.x = _src.w * 4;
							_currSprite = 2;
							break;
						case 2:
							_src.x = _src.w * 5;
							_currSprite = 3;
							break;
						case 3:
							_src.x = _src.w * 2;
							_currSprite = 0;
							break;
						default:
							break;
						}

						_nextSpriteCount = 0;
					}
				}

				// ATTACKING
				else if (_actualAttackingState == ST_ATTACKING)
				{
					if (_nextSpriteCount >= _spriteMaxTime)
					{
						switch (_currSprite)
						{
						case 0:
							_src.x = _src.w * 7;
							_currSprite = 1;
							break;
						case 1:
							_src.x = _src.w * 8;
							_currSprite = 2;
							break;
						case 2:
							_src.x = _src.w * 9;
							_currSprite = 3;
							break;
						case 3:
							_src.x = _src.w * 6;
							_currSprite = 0;
							break;
						default:
							break;
						}

						_nextSpriteCount = 0;
					}
				}
			}
		}

		// LEFT
		else if (actualDir == DIR_LEFT)
		{
			_src.y = _src.h * 2;

			// STILL
			if (_actualMovementState == ST_STILL)
			{
				if (_actualAttackingState == ST_NOT_ATTACKING)
				{
					_src.x = 0;
				}
				else if (_actualAttackingState == ST_ATTACKING)
				{
					_src.x = _src.w;
				}
			}

			// MOVING
			else if (_actualMovementState == ST_MOVING)
			{
				// NOT ATTACKING
				if (_actualAttackingState == ST_NOT_ATTACKING)
				{
					if (_nextSpriteCount >= _spriteMaxTime)
					{
						switch (_currSprite)
						{
						case 0:
							_src.x = _src.w * 4;
							_currSprite = 1;
							break;
						case 1:
							_src.x = _src.w * 6;
							_currSprite = 2;
							break;
						case 2:
							_src.x = _src.w * 8;
							_currSprite = 3;
							break;
						case 3:
							_src.x = _src.w * 2;
							_currSprite = 0;
							break;
						default:
							break;
						}

						_nextSpriteCount = 0;
					}
				}

				// ATTACKING
				else if (_actualAttackingState == ST_ATTACKING)
				{
					if (_nextSpriteCount >= _spriteMaxTime)
					{
						switch (_currSprite)
						{
						case 0:
							_src.x = _src.w * 11;
							_currSprite = 1;
							break;
						case 1:
							_src.x = _src.w * 13;
							_currSprite = 2;
							break;
						case 2:
							_src.x = _src.w * 15;
							_currSprite = 3;
							break;
						case 3:
							_src.x = _src.w * 9;
							_currSprite = 0;
							break;
						default:
							break;
						}

						_nextSpriteCount = 0;
					}
				}
			}
		}

		// RIGHT
		else if (actualDir == DIR_RIGHT)
		{
			_src.y = _src.h * 3;

			// STILL
			if (_actualMovementState == ST_STILL)
			{
				if (_actualAttackingState == ST_NOT_ATTACKING)
				{
					_src.x = 0;
				}
				else if (_actualAttackingState == ST_ATTACKING)
				{
					_src.x = _src.w;
				}
			}

			// MOVING
			else if (_actualMovementState == ST_MOVING)
			{
				if (_actualAttackingState == ST_NOT_ATTACKING)
				{
					if (_nextSpriteCount >= _spriteMaxTime)
					{
						switch (_currSprite)
						{
						case 0:
							_src.x = _src.w * 4;
							_currSprite = 1;
							break;
						case 1:
							_src.x = _src.w * 6;
							_currSprite = 2;
							break;
						case 2:
							_src.x = _src.w * 8;
							_currSprite = 3;
							break;
						case 3:
							_src.x = _src.w * 2;
							_currSprite = 0;
							break;
						default:
							break;
						}

						_nextSpriteCount = 0;
					}
				}
				else if (_actualAttackingState == ST_ATTACKING)
				{
					if (_nextSpriteCount >= _spriteMaxTime)
					{
						switch (_currSprite)
						{
						case 0:
							_src.x = _src.w * 11;
							_currSprite = 1;
							break;
						case 1:
							_src.x = _src.w * 13;
							_currSprite = 2;
							break;
						case 2:
							_src.x = _src.w * 15;
							_currSprite = 3;
							break;
						case 3:
							_src.x = _src.w * 9;
							_currSprite = 0;
							break;
						default:
							break;
						}

						_nextSpriteCount = 0;
					}
				}
			}
		}
	}

	// DEAD
	else
	{
		_src.y = _src.h * 4;

		if (_nextSpriteCount >= _spriteMaxTime)
		{
			_src.x += _src.w;
			_nextSpriteCount = 0;
		}

		if (_src.x == RESOURCE_MANAGER->getGraphicWidth(_img) + _src.w)
		{
			_endAnim = true;
		}
	}

	_nextSpriteCount += 10;

	checkMapLimits();
}

void Player::render()
{
	VIDEO->renderGraphic(_img, _src, _dst);
	
	if (_bullets.size() > 0)
	{
		for (auto& bullet : _bullets)
		{
			bullet->render();
		}
	}
}

void Player::checkMapLimits()
{
	// X
	if (_dst.x < 10)
	{
		_dst.x = 10;
	}
	else if (_dst.x >= (SCREEN_WIDTH - _dst.w - 10))
	{
		_dst.x = SCREEN_WIDTH - _dst.w - 10;
	}

	// Y
	if (_dst.y < 10)
	{
		_dst.y = 10;
	}
	else if (_dst.y >= (SCREEN_HEIGHT - _dst.h - 30))
	{
		_dst.y = SCREEN_HEIGHT - _dst.h - 30;
	}
}

Player::DIRECTION Player::getCurrentDirection()
{
	if (!_directionStack.empty())
	{
		return _directionStack.back();
	}

	return DIR_NONE;
}

Player::DIRECTION Player::getLastDir()
{
	return _lastDir;
}

Player::DIRECTION Player::getPrevDirection()
{
	if (!_directionStack.empty())
	{
		if (_directionStack.size() > 2)
		{
			return _directionStack[_directionStack.size() - 2];
		}
		else
		{
			return _directionStack[0];
		}
	}

	return DIR_NONE;
}

void Player::updateDirectionStack()
{
	std::vector<std::pair<DIRECTION, SDL_Scancode>> keyMap = {
		{DIR_UP, SDL_SCANCODE_UP},
		{DIR_DOWN, SDL_SCANCODE_DOWN},
		{DIR_LEFT, SDL_SCANCODE_LEFT},
		{DIR_RIGHT, SDL_SCANCODE_RIGHT}
	};

	for (const auto& pair : keyMap)
	{
		Player::DIRECTION dir = pair.first;
		SDL_Scancode key = pair.second;

		if (INPUT_MANAGER->getKeyState(key))
		{
			if (std::find(_directionStack.begin(), _directionStack.end(), dir) == _directionStack.end())
				_directionStack.push_back(dir);
		}
	}

	for (auto it = _directionStack.begin(); it != _directionStack.end();)
	{
		SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

		switch (*it)
		{
		case DIR_UP: 
			scancode = SDL_SCANCODE_UP;
			break;
		case DIR_DOWN:
			scancode = SDL_SCANCODE_DOWN;
			break;
		case DIR_LEFT:
			scancode = SDL_SCANCODE_LEFT;
			break;
		case DIR_RIGHT:
			scancode = SDL_SCANCODE_RIGHT;
			break;
		default:
			break;
		}

		if (!INPUT_MANAGER->getKeyState(scancode))
			it = _directionStack.erase(it);
		else
			++it;
	}

	if (!_directionStack.empty())
		_lastDir = _directionStack.back();
}
