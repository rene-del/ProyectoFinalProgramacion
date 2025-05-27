#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>

class GameState
{
private:
	static GameState* _pInstance;

	int _points;
	std::string _name;

protected:
	GameState();

public:
	~GameState();

	int getPoints() { return _points; };
	void setPoints(int val) { _points = val; };

	std::string getName() { return _name; };
	void setName(std::string val) { _name = val; };

	static GameState* getInstance();
};

#endif

