#include "InputManager.h"
#include "../Game/Player.h"

#include <iostream>

InputManager* InputManager::_pInstance = nullptr;

extern Player* PLAYER;

InputManager::InputManager()
{
	_endGame = false;

	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		_keyStates[i] = false;
	}

	_lastDir = DIR_DOWN;
}

InputManager::~InputManager()
{
}

void InputManager::manageInputs()
{
	while (SDL_PollEvent(&_testEvent))
	{
		switch (_testEvent.type)
		{
		case SDL_KEYDOWN:
			if (_testEvent.key.repeat == 0)
			{
				switch (_testEvent.key.keysym.sym)
				{
				case SDLK_w:
					pushDirection(DIR_UP);
					break;
				case SDLK_s:
					pushDirection(DIR_DOWN);
					break;
				case SDLK_a:
					pushDirection(DIR_LEFT);
					break;
				case SDLK_d:
					pushDirection(DIR_RIGHT);
					break;
				default:
					break;
				}

				PLAYER->setCurrSprite(3);
				PLAYER->setNextSpriteCount(PLAYER->getSpriteMaxTime());
			}

			switch (_testEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				_endGame = true;
			default:
				break;
			}

			_keyStates[_testEvent.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			switch (_testEvent.key.keysym.sym)
			{
			case SDLK_w:
				popDirection(DIR_UP);
				break;
			case SDLK_s:
				popDirection(DIR_DOWN);
				break;
			case SDLK_a:
				popDirection(DIR_LEFT);
				break;
			case SDLK_d:
				popDirection(DIR_RIGHT);
				break;
			default:
				break;
			}

			_keyStates[_testEvent.key.keysym.scancode] = false;
			break;
		case SDL_QUIT:
			_endGame = true;
			break;
		default:
			break;
		}
	}
}

void InputManager::pushDirection(DIRECTION dir)
{
	if (std::find(_directionStack.begin(), _directionStack.end(), dir) == _directionStack.end())
	{
		_directionStack.push_back(dir);
	}
}

void InputManager::popDirection(DIRECTION dir)
{
	auto it = std::find(_directionStack.begin(), _directionStack.end(), dir);

	if (it != _directionStack.end())
	{
		if (_directionStack.size() == 1)
		{
			_lastDir = _directionStack[0];
		}

		_directionStack.erase(it);
	}
}

InputManager* InputManager::getInstance()
{
	if (_pInstance == nullptr)
		_pInstance = new InputManager();

	return _pInstance;
}

InputManager::DIRECTION InputManager::getCurrentDirection()
{
	if (!_directionStack.empty())
	{
		return _directionStack.back();
	}

	return DIR_NONE;
}

InputManager::DIRECTION InputManager::getPrevDirection()
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
