#include "TimeManager.h"

TimeManager* TimeManager::_pInstance = nullptr;

TimeManager::TimeManager()
{
	_fps = 60;
	_lastTime = 0;
	_currentTime = 0;
	_deltaTime = 0;
	_msFrame = 1 / (_fps / 1000.0f);
	_elapsedTime = 0;
	_spriteChangeTime = 0;
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

	_elapsedTime += 10;
	_spriteChangeTime += 10;

	std::cout << _elapsedTime << std::endl;
}

TimeManager* TimeManager::getInstance()
{
	if (_pInstance == nullptr)
		_pInstance = new TimeManager();

	return _pInstance;
}
