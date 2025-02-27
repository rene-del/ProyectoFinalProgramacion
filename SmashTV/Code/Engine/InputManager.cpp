#include "InputManager.h"

InputManager* InputManager::_pInstance = nullptr;

InputManager::InputManager()
{
	_endGame = false;

	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		keyStates[i] = false;
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
			keyStates[_testEvent.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			keyStates[_testEvent.key.keysym.scancode] = false;
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
