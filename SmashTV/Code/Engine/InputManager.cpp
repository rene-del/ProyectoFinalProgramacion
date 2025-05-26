#include "InputManager.h"
#include "../Game/SceneDirector.h"
#include "../Game/Player.h"

InputManager* InputManager::_pInstance = nullptr;

extern SceneDirector* SCENE_DIRECTOR;
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
				case SDLK_UP:
					pushDirection(DIR_UP);
					break;
				case SDLK_DOWN:
					pushDirection(DIR_DOWN);
					break;
				case SDLK_LEFT:
					pushDirection(DIR_LEFT);
					break;
				case SDLK_RIGHT:
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
			case SDLK_UP:
				popDirection(DIR_UP);
				break;
			case SDLK_DOWN:
				popDirection(DIR_DOWN);
				break;
			case SDLK_LEFT:
				popDirection(DIR_LEFT);
				break;
			case SDLK_RIGHT:
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
	if (SCENE_DIRECTOR->getCurrSceneEnum() == SceneEnum::MAP)
	{
		if (std::find(_directionStack.begin(), _directionStack.end(), dir) == _directionStack.end())
		{
			_directionStack.push_back(dir);
		}
	}
}

void InputManager::popDirection(DIRECTION dir)
{
	if (SCENE_DIRECTOR->getCurrSceneEnum() == SceneEnum::MAP)
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
