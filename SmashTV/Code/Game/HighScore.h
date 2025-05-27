#pragma once
#include "../../Code/Game/Scene.h"

#include <vector>
#include <fstream>
#include <string>
#include <SDL.h>

struct PlayerRanking {
	std::string _name;
	int _points;
};

class HighScore : public Scene
{
private:

	int _score;
	std::string _name;
	std::string _path;
	char _endstr;
	std::vector<int> _top10P;
	std::vector<std::string> _top10N;
	bool _hasExecuted;
	int _texId;

	SDL_Rect _src;
	SDL_Rect _dst;
	std::vector<PlayerRanking> _playerRanking;


public:
	HighScore();
	~HighScore();


	void init() override;
	void reinit() override;
	void update() override;
	void render() override;

	void setPath(std::string path) { _path = path; };
	void setScore(int value) { _score = value; };
	void setName(std::string value) { _name = _name; };

	int getScore() { return _score; };
	std::string getName() { return _name; };

	void registerName(std::string name);
	void registerScore(int score);
	void topRanking();
	void writeFile();
	void readFile();




};

