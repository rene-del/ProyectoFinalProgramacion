#pragma once
#include "../../Code/Game/Scene.h"

#include <vector>
#include <fstream>
#include <string>
#include <SDL.h>
class HighScore : public Scene
{
private:

	int _score;
	std::string _name;
	char _endstr;

	std::vector<int> _top10;


	int _texId;

	SDL_Rect _src;
	SDL_Rect _dst;


public:
	HighScore();
	~HighScore();


	void init() override;
	void reinit() override;
	void update() override;
	void render() override;


	void registerName(std::string name);
	void registerScore(int score);
	void topRanking();
	void writeFile(std::string path);
	void readFile(std::string path);




};

