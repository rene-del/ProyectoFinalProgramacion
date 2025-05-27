#include "GameState.h"

GameState* GameState::_pInstance = nullptr;

GameState::GameState()
{
	_points = 0;
	_name = "PLAYER";
}

GameState::~GameState()
{
}

GameState* GameState::getInstance()
{
	if (_pInstance == nullptr)
		_pInstance = new GameState();

	return _pInstance;
}
