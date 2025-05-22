#include "TimeManager.h"


TimeManager* TimeManager::_pInstance = nullptr;

TimeManager::TimeManager()
{
	_fps = 60;
	_lastTime = 0;
	_currentTime = 0;
	_deltaTime = 0;
	_msFrame = 1 / (_fps / 1000.0f);
}

TimeManager::~TimeManager()
{
}

void TimeManager::waitTime(int ms)
{
	SDL_Delay(ms);
}

void TimeManager::timeControl()
{
	_currentTime = SDL_GetTicks();
	_deltaTime = _currentTime - _lastTime;

	if (_deltaTime < (int)_msFrame)
	{
		SDL_Delay((int)_msFrame - _deltaTime);
	}

	_lastTime = _currentTime;
}

TimeManager* TimeManager::getInstance()
{
	if (_pInstance == nullptr)
		_pInstance = new TimeManager();

	return _pInstance;
}
