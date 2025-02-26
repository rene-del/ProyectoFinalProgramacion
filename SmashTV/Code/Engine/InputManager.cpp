#include "InputManager.h"
#include "Charger.h"

extern Charger PLAYER;

InputManager* InputManager::_pInstance = nullptr;

InputManager::InputManager()
{
	_endGame = false;
	_mKey = false;
	_spaceKey = false;
	_enterKey = false;
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
			switch (_testEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				_endGame = true;
				break;
			case SDLK_m:
				if (PLAYER.getState() == ST_ATTACK)
				{
					_mKey = true;
				}

				break;
			case SDLK_SPACE:
				if ((PLAYER.getState() == ST_PATROL_RIGHT) || (PLAYER.getState() == ST_PATROL_LEFT))
				{
					_spaceKey = true;
				}

				break;
			case SDLK_RETURN:
				if (PLAYER.getState() == ST_ATTACK)
				{
					_enterKey = true;
				}

				break;
			default:
				break;
			}

			break;
		case SDL_QUIT:
			_endGame = true;
			break;
		default:
			break;
		}
	}
}

InputManager* InputManager::getInstance()
{
	if (_pInstance == nullptr)
		_pInstance = new InputManager();

	return _pInstance;
}
