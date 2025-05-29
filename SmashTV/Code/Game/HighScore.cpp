#include "HighScore.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"
#include "SceneDirector.h"
#include "GameState.h"

#include <iostream>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;
extern SceneDirector* SCENE_DIRECTOR;
extern GameState* GAME_STATE;

HighScore::HighScore()
{
	_texId = 0;
	_name = "";
	_score = 0;
	_top10P.resize(0);
	_top10N.resize(0);
	_playerRanking.resize(0);
	_endstr = ' ';
	_reInit = true;
	_hasExecuted = false;
	
	_src.x = 0;
	_src.y = 0;
	_src.w = 0;
	_src.h = 0;

	_dst.x = 0;
	_dst.y = 0;
	_dst.w = 0;
	_dst.h = 0;
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
	init();
}

void HighScore::update()
{
	bool r = INPUT_MANAGER->getKeyState(SDL_SCANCODE_R);
	

	if (!_hasExecuted)
	{
		setPath("Assets/Highscore.bin");
		writeFile();
		readFile();
		topRanking();
		_hasExecuted = true; 
	}

	//RETURN MENU
	if (r)
	{
		_hasExecuted = false;
		SCENE_DIRECTOR->changeScene(SceneEnum::MENU, true);
	}	
}

void HighScore::render()
{
	
	
	SDL_Color textColor = { 255, 255, 255, 255 };

	int startX = SCREEN_HEIGHT / 2 - 80;  
	int startY = 100;  
	int spacingY = 40; 
	int textSize = 24;

	int entries = _playerRanking.size();

	if (entries < 6)
	{
		for (size_t i = 0; i < entries; i++)
		{
			std::string line = std::to_string(i + 1) + ". " + _playerRanking[i]._name + "  " + std::to_string(_playerRanking[i]._points);
			if (i == 0)
			{
				textColor = { 255, 255, 0, 255 };
				textSize = 50;
				startX -= 50;
				spacingY += 20;
			}
			if (i == 1)
			{
				textColor = { 138, 149, 151, 255 };
				textSize = 40;
				startX -= 40;
				spacingY += 20;
			}
			if (i == 2)
			{

				textColor = { 205, 127, 50, 255 };
				textSize = 30;
				startX -= 30;
				spacingY += 20;
			}
			if (i > 2)
			{

				textColor = { 255, 255, 255, 255 };
				textSize = 20;
				startY = 150;
			}
			VIDEO->renderText(line, startX, startY + i * spacingY, textColor, textSize);
			startX = SCREEN_HEIGHT / 2 - 80;
			spacingY = 40;
		}
	}
	else
	{
		for (size_t i = 0; i < 6; i++)
		{
			std::string line = std::to_string(i + 1) + ". " + _playerRanking[i]._name + "  " + std::to_string(_playerRanking[i]._points);
			if (i == 0)
			{
				textColor = { 255, 255, 0, 255 };
				textSize = 50;
				startX -= 50;
				spacingY += 20;
			}
			if (i == 1)
			{
				textColor = { 138, 149, 151, 255 };
				textSize = 40;
				startX -= 40;
				spacingY += 20;
			}
			if (i == 2)
			{

				textColor = { 205, 127, 50, 255 };
				textSize = 30;
				startX -= 30;
				spacingY += 20;
			}
			if (i > 2)
			{

				textColor = { 255, 255, 255, 255 };
				textSize = 20;
				startY = 150;
			}
			VIDEO->renderText(line, startX, startY + i * spacingY, textColor, textSize);
			startX = SCREEN_HEIGHT / 2 - 80;
			spacingY = 40;
		}
	}

	std::string line = "PRESS \"\R\" TO RETURN TO THE MENU";
	VIDEO->renderText(line, SCREEN_WIDTH / 2 - 360, SCREEN_WIDTH / 2 + 100, textColor, 38);
	VIDEO->updateScreen();
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
	
}

void HighScore::writeFile()
{

	_score = GAME_STATE->getPoints();
	_name = GAME_STATE->getName();

	if (_score != 0 || _name != "")
	{
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
