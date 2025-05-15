#include "../../Code/Engine/ResourceManager.h"
#include "../../Code/Engine/Video.h"
#include "../../Code/Engine/InputManager.h"
#include "../../Code/Engine/TimeManager.h"
#include "../../Code/Game/SceneDirector.h"

#include "../../Code/Game/Player.h"

#include "../../Code/Game/Blob.h"
#include "../../Code/Game/Grunt.h"
#include "../../Code/Game/Mummy.h"
#include "../../Code/Game/tinyGrunt.h"
#include "../../Code/Game/Mine.h"


ResourceManager* RESOURCE_MANAGER;
Video* VIDEO;
InputManager* INPUT_MANAGER;
TimeManager* TIME_MANAGER;
SceneDirector* SCENE_DIRECTOR;

Player PLAYER;

Blob* BLOB = new Blob();
Grunt* GRUNT = new Grunt();
Mummy* MUMMY = new Mummy();
tinyGrunt* TINNYGRUNT = new tinyGrunt();
Mine* MINE = new Mine();

int main(int argc, char* args[])
{
	// INIT
	RESOURCE_MANAGER = ResourceManager::getInstance();
	VIDEO = Video::getInstance();
	INPUT_MANAGER = InputManager::getInstance();
	TIME_MANAGER = TimeManager::getInstance();
	SCENE_DIRECTOR = SceneDirector::getInstance();

	
	while (!INPUT_MANAGER->getEndGame())
	{
		// CHECK IF SCENE NEEDS REINIT
		if (SCENE_DIRECTOR->getCurrentScene()->mustReInit())
		{
			SCENE_DIRECTOR->getCurrentScene()->reinit();
		}

		// INPUTS
		INPUT_MANAGER->manageInputs();

		// CLEAR SCREEN
		VIDEO->clearScreen();
		
		// UPDATE
		SCENE_DIRECTOR->getCurrentScene()->update();

		
		// RENDER
		if (!SCENE_DIRECTOR->getCurrentScene()->mustReInit())
		{
			SCENE_DIRECTOR->getCurrentScene()->render();
		}
		
		VIDEO->updateScreen();

		// UPDATE TIME
		TIME_MANAGER->timeControl();
	}

	return 0;
}
