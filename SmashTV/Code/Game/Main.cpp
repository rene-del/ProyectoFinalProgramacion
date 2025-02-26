#include "../../Code/Engine/ResourceManager.h"
#include "../../Code/Engine/Video.h"
#include "../../Code/Engine/InputManager.h"
#include "../../Code/Engine/TimeManager.h"

#include "../../Code/Game/Player.h"

ResourceManager* RESOURCE_MANAGER = ResourceManager::getInstance();
Video* VIDEO = Video::getInstance();
InputManager* INPUT_MANAGER = InputManager::getInstance();
TimeManager* TIME_MANAGER = TimeManager::getInstance();

Player* PLAYER = new Player();

int main(int argc, char* args[])
{
	PLAYER->init();

	while (!INPUT_MANAGER->getEndGame())
	{
		INPUT_MANAGER->manageInputs();

		VIDEO->clearScreen();

		PLAYER->update();
		PLAYER->render();

		VIDEO->updateScreen();

		TIME_MANAGER->timeControl();
	}

	return 0;
}
