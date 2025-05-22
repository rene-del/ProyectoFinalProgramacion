#include "HighScore.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"
#include "../Game/SceneDirector.h"

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;
extern SceneDirector* SCENE_DIRECTOR;


HighScore::HighScore()
{
	_name = "";
	_score = 0;
	_top10.resize(0);
	_endstr = ' ';

	_reInit = true;
	
}

HighScore::~HighScore()
{
}

void HighScore::init()
{
	_endstr = '\0';
	_name = "Nombre1";
	_score = 20;

	_reInit = false;

	

}

void HighScore::reinit()
{
	_reInit = true;
}

void HighScore::update()
{
	bool enter = INPUT_MANAGER->getKeyState(SDL_SCANCODE_RETURN);
	//RETURN MENU
	if (enter)
	{
		SCENE_DIRECTOR->changeScene(SceneEnum::MENU, false);
	}
	writeFile("prueba");

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
	_top10.push_back(score);
}

void HighScore::topRanking()
{
	//bubble sort
}

void HighScore::writeFile(std::string path)
{
	std::streampos size;
	//el tamaño maximo del nombre o string será 5
	//se insertan los datos
	std::fstream file1("Highscore.bin", std::ios::out | std::ios::binary);
	//escribo nombre
	file1.write(_name.c_str(), sizeof(_name));
	//escribo puntuacion
	file1.write(reinterpret_cast<const char*>(_score), sizeof(_score));
	file1.write(&_endstr, sizeof(_endstr));
	file1.close();

}

void HighScore::readFile(std::string path)
{
}
