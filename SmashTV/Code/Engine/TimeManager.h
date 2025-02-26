#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <iostream>

#include "SDL.h"

class TimeManager
{
private:
	int _fps;
	unsigned int _lastTime, _currentTime, _deltaTime;
	float _msFrame;
	Uint32 _elapsedTime;
	Uint32 _spriteChangeTime;

	static TimeManager* _pInstance;

protected:
	TimeManager();

public:
	~TimeManager();

	void waitTime(int ms);
	void timeControl();

	void setElapsedTime(Uint32 time) { _elapsedTime = time; };
	void setSpriteChangeTime(Uint32 time) { _spriteChangeTime = time; };

	Uint32 getElapsedTime() { return _elapsedTime; };
	Uint32 getSpriteChangeTime() { return _spriteChangeTime; };

	static TimeManager* getInstance();
};

#endif

