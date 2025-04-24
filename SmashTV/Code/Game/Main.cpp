#include "../../Code/Engine/ResourceManager.h"
#include "../../Code/Engine/Video.h"
#include "../../Code/Engine/InputManager.h"
#include "../../Code/Engine/TimeManager.h"

#include "../../Code/Game/Player.h"
#include "../../Code/Game/Map.h"
#include "../../Code/Game/Bullet.h"

ResourceManager* RESOURCE_MANAGER = ResourceManager::getInstance();
Video* VIDEO = Video::getInstance();
InputManager* INPUT_MANAGER = InputManager::getInstance();
TimeManager* TIME_MANAGER = TimeManager::getInstance();

Player* PLAYER = new Player();
Map* MAP = new Map();
Bullet* BULLET = new Bullet();


int main(int argc, char* args[])
{
	PLAYER->init();
	MAP->init();
	BULLET->init();

	while (!INPUT_MANAGER->getEndGame())
	{
		INPUT_MANAGER->manageInputs();

		VIDEO->clearScreen();
		//UPDATE
		PLAYER->update();
		BULLET->update();

		//RENDER
		MAP->render();
		PLAYER->render();
		BULLET->render();
		VIDEO->updateScreen();

		TIME_MANAGER->timeControl();
	}

	return 0;
}
