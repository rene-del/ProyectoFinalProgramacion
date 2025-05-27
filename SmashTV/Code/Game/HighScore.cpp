#include "HighScore.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"
#include "../Game/SceneDirector.h"

#include "Player.h"

#include <iostream>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;
extern SceneDirector* SCENE_DIRECTOR;

extern Player* PLAYER;

HighScore::HighScore()
{
	_name = "";
	_score = 0;
	_top10P.resize(0);
	_top10N.resize(0);
	_playerRanking.resize(0);
	_endstr = ' ';
	_reInit = true;
	_hasExecuted = false;
	
}

HighScore::~HighScore()
{
}

void HighScore::init()
{
	_endstr = '\0';
	_reInit = false;

	_score = 0;

}

void HighScore::reinit()
{
	_reInit = true;
}

void HighScore::update()
{
	bool enter = INPUT_MANAGER->getKeyState(SDL_SCANCODE_RETURN);
	bool w = INPUT_MANAGER->getKeyState(SDL_SCANCODE_W);
	bool r = INPUT_MANAGER->getKeyState(SDL_SCANCODE_R);


	if (!_hasExecuted)
	{
		setPath("Highscore.bin");
		writeFile();
		readFile();
		topRanking();
		_hasExecuted = true; 
	}

	//RETURN MENU
	if (enter)
	{
		SCENE_DIRECTOR->changeScene(SceneEnum::MENU, false);
	}
	

	//CHARACTER LIMIT 5
	
}

void HighScore::render()
{
}

void HighScore::registerName(std::string name)
{
	_name = name;
}

void HighScore::registerScore(int score)
{
	_score = score;
}

void HighScore::topRanking()
{
	//bubble sort
}

void HighScore::writeFile()
{

	_score = PLAYER->getPoints();
	_name = PLAYER->getName();

	if (_name.length() > 5)
	{
		//LIMIT NAME IS 5
		_name = _name.substr(0, 5);
	}
	//NAME MUST BE 5
	_name.resize(5, ' ');
	std::streampos size;
	std::fstream file(_path, std::ios::out | std::ios::app | std::ios::binary);

	file.write(_name.c_str(), 5);
	file.write(&_endstr, sizeof(_endstr));	
	file.write(reinterpret_cast<const char*>(&_score), sizeof(_score));
	file.close();
}

void HighScore::readFile()
{
	std::streampos size;
	char readNom[6]; // 6 bytes
	int readPoints;  // 4 bytes

	std::fstream file(_path, std::ios::in | std::ios::binary);
	file.seekg(0, std::ios::end);
	size = file.tellg();
	file.seekg(0, std::ios::beg);

	int totalEntries = size / 10;
	_playerRanking.resize(totalEntries);


	for (int i = 0; i < totalEntries; ++i) {
		file.read(readNom, 6);
		file.read(reinterpret_cast<char*>(&readPoints), sizeof(readPoints));

		//PUSHING VALUES TO THE VECTOR


		char nameBuffer[7] = {};
		std::memcpy(nameBuffer, readNom, 6);

		_playerRanking.at(i)._name = nameBuffer;
		_playerRanking.at(i)._points = readPoints;
		

	//	std::cout << nameBuffer << " - " << readPoints << "\n";
	}

	file.close();

	//BUBBLE SORT
	bool swapped;
	for (int i = 0; i < _playerRanking.size() - 1; i++) {
		swapped = false;
		for (int j = 0; j < _playerRanking.size() - i - 1; j++) {
			if (_playerRanking[j]._points < _playerRanking[j + 1]._points)
			{

				std::swap(_playerRanking[j], _playerRanking[j + 1]);
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	};

	for (size_t i = 0; i < totalEntries; i++)
	{
		std::cout << "NAME: " << _playerRanking[i]._name << "POINTS: " << _playerRanking[i]._points << "\n";
	}


}
