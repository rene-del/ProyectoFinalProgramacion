#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "SDL.h"

class InputManager
{
private:
	static InputManager* _pInstance;

	bool _endGame;
	bool _mKey;
	bool _spaceKey;
	bool _enterKey;

protected:
	InputManager();

public:
	~InputManager();

	void manageInputs();

	bool getEndGame() { return _endGame; };
	bool getMKey() { return _mKey; };
	bool getSpaceKey() { return _spaceKey; };
	bool getEnterKey() { return _enterKey; };

	void setMKey(bool m) { _mKey = m; };
	void setSpaceKey(bool space) { _spaceKey = space; };
	void setEnterKey(bool enter) { _enterKey = enter; };

	static InputManager* getInstance();

	SDL_Event _testEvent;
};

#endif

