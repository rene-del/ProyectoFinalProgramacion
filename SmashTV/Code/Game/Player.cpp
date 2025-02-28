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
	_currSprite = 0;

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
}

void Player::update()
{
	// CONTROL KEYS
	bool up = INPUT_MANAGER->getKeyState(SDL_SCANCODE_UP);
	bool down = INPUT_MANAGER->getKeyState(SDL_SCANCODE_DOWN);
	bool left = INPUT_MANAGER->getKeyState(SDL_SCANCODE_LEFT);
	bool right = INPUT_MANAGER->getKeyState(SDL_SCANCODE_RIGHT);
	bool space = INPUT_MANAGER->getKeyState(SDL_SCANCODE_SPACE);
	bool enter = INPUT_MANAGER->getKeyState(SDL_SCANCODE_RETURN);

	// ALIVE
	if (_actualMovementState != ST_DEAD)
	{
		// UP
		if (up && !down)
		{
			if (_actualMovementState != ST_MOVING)
			{
				_actualMovementState = ST_MOVING;
				_actualDir = DIR_UP;
				_nextSpriteCount = _spriteMaxTime;
				_currSprite = 3;
			}

			_dst.y -= 2;
		}

		// DOWN
		else if (down && !up)
		{
			if (_actualMovementState != ST_MOVING)
			{
				_actualMovementState = ST_MOVING;
				_actualDir = DIR_DOWN;
				_nextSpriteCount = _spriteMaxTime;
				_currSprite = 3;
			}

			_dst.y += 2;
		}

		// LEFT
		else if (left && !right)
		{
			if (_actualMovementState != ST_MOVING)
			{
				_actualMovementState = ST_MOVING;
				_actualDir = DIR_LEFT;
				_nextSpriteCount = _spriteMaxTime;
				_currSprite = 3;
			}

			_dst.x -= 2;
		}

		// RIGHT
		else if (right && !left)
		{
			if (_actualMovementState != ST_MOVING)
			{
				_actualMovementState = ST_MOVING;
				_actualDir = DIR_RIGHT;
				_nextSpriteCount = _spriteMaxTime;
				_currSprite = 3;
			}

			_dst.x += 2;
		}

		// STILL
		else
		{
			_actualMovementState = ST_STILL;
		}

		// STILL
		if (!up && !down && !left && !right)
		{
			_actualMovementState = ST_STILL;
		}

		// SHOOTING
		if (space)
		{
			_actualAttackingState = ST_ATTACKING;
		}
		else
		{
			_actualAttackingState = ST_NOT_ATTACKING;
		}
	}

	// DEAD (PRUEBAS)
	if (enter)
	{
		_actualMovementState = ST_DEAD;
		_nextSpriteCount = 0;
	}

	// CONTROL SPRITES

	// NOT DEAD
	if (_actualMovementState != ST_DEAD)
	{
		// UP
		if (_actualDir == DIR_UP)
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
		else if (_actualDir == DIR_DOWN)
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
		else if (_actualDir == DIR_LEFT)
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
		else if (_actualDir == DIR_RIGHT)
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
	}

	checkMapLimits();
}

void Player::render()
{
	VIDEO->renderGraphic(_img, _src, _dst);
}

void Player::checkMapLimits()
{
	// X
	if (_dst.x < 0)
	{
		_dst.x = 0;
	}
	else if ((_dst.x + _dst.w) >= SCREEN_WIDTH)
	{
		_dst.x = SCREEN_WIDTH - _dst.w;
	}

	// Y
	if (_dst.y < 10)
	{
		_dst.y = 10;
	}
	else if ((_dst.y + _dst.h) >= SCREEN_HEIGHT)
	{
		_dst.y = SCREEN_HEIGHT - _dst.h;
	}
}
