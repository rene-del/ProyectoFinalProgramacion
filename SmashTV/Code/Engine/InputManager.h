#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include "SDL.h"

class InputManager
{
public:
	enum DIRECTION { DIR_NONE, DIR_RIGHT, DIR_LEFT, DIR_DOWN, DIR_UP };

	~InputManager();

	void manageInputs();

	bool getEndGame() { return _endGame; };
	bool getKeyState(SDL_Scancode key) { return _keyStates[key]; };

	DIRECTION getLastDir() { return _lastDir; };

	static InputManager* getInstance();

	SDL_Event _testEvent;

	DIRECTION getCurrentDirection();
	DIRECTION getPrevDirection();

private:
	static InputManager* _pInstance;

	InputManager();

	bool _keyStates[SDL_NUM_SCANCODES];
	bool _endGame;

	DIRECTION _lastDir;

	std::vector<DIRECTION> _directionStack;

	void pushDirection(DIRECTION dir);
	void popDirection(DIRECTION dir);
};

#endif

