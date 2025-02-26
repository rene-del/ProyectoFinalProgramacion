#include "InputManager.h"

#include "../Game/Player.h"

extern Player PLAYER;

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
