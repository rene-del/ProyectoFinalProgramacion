#include "../../Code/Engine/ResourceManager.h"
#include "../../Code/Engine/Video.h"
#include "../../Code/Engine/InputManager.h"
#include "../../Code/Engine/TimeManager.h"

#include "../../Code/Game/Player.h"
#include "../../Code/Game/Map.h"
#include "../../Code/Game/Bullet.h"
#include "../../Code/Game/Blob.h"



ResourceManager* RESOURCE_MANAGER = ResourceManager::getInstance();
Video* VIDEO = Video::getInstance();
InputManager* INPUT_MANAGER = InputManager::getInstance();
TimeManager* TIME_MANAGER = TimeManager::getInstance();

Player* PLAYER = new Player();
Map* MAP = new Map();
Blob* BLOB = new Blob();;




int main(int argc, char* args[])
{
	PLAYER->init();
	MAP->init();
	BLOB->init();


	while (!INPUT_MANAGER->getEndGame())
	{
		INPUT_MANAGER->manageInputs();

		VIDEO->clearScreen();
		//UPDATE
		PLAYER->update();
		BLOB->update();

		//RENDER
		MAP->render();
		PLAYER->render();
		BLOB->render();
		VIDEO->updateScreen();

		TIME_MANAGER->timeControl();
	}

	return 0;
}
