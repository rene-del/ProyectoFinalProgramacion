#include "Menu.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/InputManager.h"
#include "../Game/SceneDirector.h"

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;
extern SceneDirector* SCENE_DIRECTOR;

Menu::Menu()
{
	_src.x = 0;
	_src.y = 0;
	_src.w = 0;
	_src.h = 0;

	_dst.w = 0;
	_dst.y = 0;
	_dst.x = 0;
	_dst.y = 0;

	_reInit = true;
}

Menu::~Menu()
{
}

void Menu::init()
{
	_texId = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Scenes/menu.png");

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

void Menu::reinit()
{
	_reInit = true;
}

void Menu::update()
{
	// CONTROL KEY
	bool enter = INPUT_MANAGER->getKeyState(SDL_SCANCODE_RETURN);
	bool highScore = INPUT_MANAGER->getKeyState(SDL_SCANCODE_H);

	// START GAME
	if (enter)
	{
		SCENE_DIRECTOR->changeScene(SceneEnum::MAP, true);
	}
	// HIGH SCORE
	if (highScore)
	{
		SCENE_DIRECTOR->changeScene(SceneEnum::HIGHSCORE, true);
	}
}

void Menu::render()
{
	VIDEO->renderGraphic(_texId, _src, _dst);
}
