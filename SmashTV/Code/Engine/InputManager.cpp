#include "InputManager.h"
#include "../Game/SceneDirector.h"

InputManager* InputManager::_pInstance = nullptr;

extern SceneDirector* SCENE_DIRECTOR;

InputManager::InputManager()
{
	_endGame = false;

	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		_keyStates[i] = false;
	}
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
			if (_testEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				_endGame = true;
			}
			else if (_testEvent.key.keysym.sym == SDLK_RETURN)
			{
				if (_testEvent.key.repeat == 0)
				{
					_keyStates[_testEvent.key.keysym.scancode] = true;
				}
				else
				{
					_keyStates[_testEvent.key.keysym.scancode] = false;
				}
			}
			else
			{
				_keyStates[_testEvent.key.keysym.scancode] = true;
			}

			break;
		case SDL_KEYUP:
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

InputManager* InputManager::getInstance()
{
	if (_pInstance == nullptr)
		_pInstance = new InputManager();

	return _pInstance;
}
