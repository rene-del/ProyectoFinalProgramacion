#include "GameOver.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"
#include "../Game/SceneDirector.h"

#include "Player.h"

#include <string>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;
extern SceneDirector* SCENE_DIRECTOR;

extern Player* PLAYER;

GameOver::GameOver()
{
	_texId = 0;

	_src.x = 0;
	_src.y = 0;
	_src.w = 0;
	_src.h = 0;

	_dst.w = 0;
	_dst.y = 0;
	_dst.x = 0;
	_dst.y = 0;

	_nameSet = false;

	_reInit = true;
}

GameOver::~GameOver()
{
}

void GameOver::init()
{
	_texId = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Scenes/gameOver.png");

	_src.x = 0;
	_src.y = 0;
	_src.w = 832;
	_src.h = 832;

	_dst.x = 0;
	_dst.y = 0;
	_dst.w = 832;
	_dst.h = 832;

	_reInit = false;
}

void GameOver::reinit()
{
	_reInit = true;
}

void GameOver::update()
{
	if (!_nameSet) {
		std::string name;
		std::cout << "INSERT NAME \n";
		std::getline(std::cin, name);
		PLAYER->setName(name);
		_nameSet = true;
	}

	// CONTROL KEY
	bool enter = INPUT_MANAGER->getKeyState(SDL_SCANCODE_RETURN);
	bool highScore = INPUT_MANAGER->getKeyState(SDL_SCANCODE_H);

	// GO MENU
	if (enter)
	{
		SCENE_DIRECTOR->changeScene(SceneEnum::MENU, false);
	}
	// HIGH SCORE
	if (highScore)
	{
		SCENE_DIRECTOR->changeScene(SceneEnum::HIGHSCORE, true);
	}
}

void GameOver::render()
{
	VIDEO->renderGraphic(_texId, _src, _dst);
}
