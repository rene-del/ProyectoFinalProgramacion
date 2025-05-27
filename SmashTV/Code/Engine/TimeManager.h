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

	static TimeManager* _pInstance;

protected:
	TimeManager();

public:
	~TimeManager();

	void waitTime(int ms);
	void timeControl();

	unsigned int getDeltaTime() { return _deltaTime; };

	static TimeManager* getInstance();
};

#endif

