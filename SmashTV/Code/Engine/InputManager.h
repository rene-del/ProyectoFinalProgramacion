#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "SDL.h"

class InputManager
{
private:
	static InputManager* _pInstance;

	bool keyStates[SDL_NUM_SCANCODES];
	bool _endGame;

protected:
	InputManager();

public:
	~InputManager();

	void manageInputs();

	bool getEndGame() { return _endGame; };
	bool getKeyState(SDL_Scancode key) { return keyStates[key]; };

	static InputManager* getInstance();

	SDL_Event _testEvent;
};

#endif

