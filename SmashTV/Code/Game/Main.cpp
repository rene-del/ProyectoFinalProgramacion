#include "ResourceManager.h"
#include "Video.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Charger.h"

ResourceManager* RESOURCE_MANAGER = ResourceManager::getInstance();
Video* VIDEO = Video::getInstance();
InputManager* INPUT_MANAGER = InputManager::getInstance();
TimeManager* TIME_MANAGER = TimeManager::getInstance();
Charger PLAYER;

int main(int argc, char* args[])
{
	PLAYER.init();

	int charger = RESOURCE_MANAGER->loadAndGetGraphicID("charger.png");
	PLAYER.setImg(charger);

	while (!INPUT_MANAGER->getEndGame())
	{
		INPUT_MANAGER->manageInputs();

		VIDEO->clearScreen();

		PLAYER.update();
		PLAYER.render();

		VIDEO->updateScreen();

		TIME_MANAGER->timeControl();
	}

	return 0;
}
