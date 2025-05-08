#include "Player.h"
#include "Bullet.h"

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
	_speed = 0;

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

	_numberBullets = 0;
	_bullets.clear();
}

Player::~Player()
{
}

void Player::init()
{
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Player/PlayerTileset.png");
	_speed = 2;

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
	

	_bullet1.init();

}

void Player::update()
{
	// CURRENT DIRECTION
	InputManager::DIRECTION actualDir = INPUT_MANAGER->getCurrentDirection();

	// CONTROL KEYS
	bool space = INPUT_MANAGER->getKeyState(SDL_SCANCODE_SPACE);
	bool enter = INPUT_MANAGER->getKeyState(SDL_SCANCODE_RETURN);


	_numberBullets++;
	_bullet1.update();
	

	// ALIVE
	if (_actualMovementState != ST_DEAD)
	{
		// MOVEMENT STATE
		if (actualDir != InputManager::DIR_NONE)
		{
			_actualMovementState = ST_MOVING;

			// MOVE TO LAST SAVED DIRECTION
			switch (actualDir)
			{
			// RIGHT
			case InputManager::DIR_RIGHT:
				if (INPUT_MANAGER->getPrevDirection() != InputManager::DIR_LEFT)
				{
					_dst.x += _speed;
				}
				break;

			// LEFT
			case InputManager::DIR_LEFT:
				if (INPUT_MANAGER->getPrevDirection() != InputManager::DIR_RIGHT)
				{
					_dst.x -= _speed;
				}
				break;

			// DOWN
			case InputManager::DIR_DOWN:
				if (INPUT_MANAGER->getPrevDirection() != InputManager::DIR_UP)
				{
					_dst.y += _speed;
				}
				break;

			// UP
			case InputManager::DIR_UP:
				if (INPUT_MANAGER->getPrevDirection() != InputManager::DIR_DOWN)
				{
					_dst.y -= _speed;
				}
				break;
			default:
				break;
			}

			// STILL IF OPPOSITE DIRECTION IS PRESSED

			// RIGHT - LEFT
			if (INPUT_MANAGER->getCurrentDirection() == InputManager::DIR_RIGHT)
			{
				if (INPUT_MANAGER->getPrevDirection() == InputManager::DIR_LEFT)
				{
					_actualMovementState = ST_STILL;
					actualDir = InputManager::DIR_LEFT;
				}
			}

			// LEFT - RIGHT
			else if (INPUT_MANAGER->getCurrentDirection() == InputManager::DIR_LEFT)
			{
				if (INPUT_MANAGER->getPrevDirection() == InputManager::DIR_RIGHT)
				{
					_actualMovementState = ST_STILL;
					actualDir = InputManager::DIR_RIGHT;
				}
			}

			// UP - DOWN
			else if (INPUT_MANAGER->getCurrentDirection() == InputManager::DIR_UP)
			{
				if (INPUT_MANAGER->getPrevDirection() == InputManager::DIR_DOWN)
				{
					_actualMovementState = ST_STILL;
					actualDir = InputManager::DIR_DOWN;
				}
			}

			// DOWN - UP
			else if (INPUT_MANAGER->getCurrentDirection() == InputManager::DIR_DOWN)
			{
				if (INPUT_MANAGER->getPrevDirection() == InputManager::DIR_UP)
				{
					_actualMovementState = ST_STILL;
					actualDir = InputManager::DIR_UP;
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
			//metodo para detectar que se ha disparado una bala
			//looking for witch direction is currently looking at
			//1 derecha
			//2 izquierda
			//3 abajo
			//4 arriba
			_bullet1.isShoting(INPUT_MANAGER->getCurrentDirection());

		}
			
			


			//std::cout << "bullets: " << _numberBullets << "\n";
		}
		else
		{
			_actualAttackingState = ST_NOT_ATTACKING;
		}
	

	// DEAD (TESTING)
	if (enter)
	{
		_actualMovementState = ST_DEAD;
		_nextSpriteCount = 0;
	}

	// SPRITES CONTROL

	// NOT DEAD
	if (_actualMovementState != ST_DEAD)
	{
		// NO DIR
		if (actualDir == InputManager::DIR_NONE)
		{
			switch (INPUT_MANAGER->getLastDir())
			{
			// LEFT
			case InputManager::DIR_LEFT:
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
			case InputManager::DIR_RIGHT:
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
			case InputManager::DIR_UP:
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
			case InputManager::DIR_DOWN:
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
		else if (actualDir == InputManager::DIR_UP)
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
		else if (actualDir == InputManager::DIR_DOWN)
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
		else if (actualDir == InputManager::DIR_LEFT)
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
		else if (actualDir == InputManager::DIR_RIGHT)
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
	_bullet1.render();
	//_bullet2.render();

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
