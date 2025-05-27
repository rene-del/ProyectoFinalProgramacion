#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include "SDL.h"

class InputManager
{
public:
	~InputManager();

	void manageInputs();

	bool getEndGame() { return _endGame; };
	bool getKeyState(SDL_Scancode key) { return _keyStates[key]; };

	static InputManager* getInstance();

	SDL_Event _testEvent;

private:
	static InputManager* _pInstance;

	InputManager();

	bool _keyStates[SDL_NUM_SCANCODES];
	bool _endGame;
};

#endif

