#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/Audio.h"
#include "../Engine/InputManager.h"
#include "../Engine/TimeManager.h"
#include "../Game/GameState.h"
#include "../Game/SceneDirector.h"

#include <stdlib.h>
#include <time.h>

ResourceManager* RESOURCE_MANAGER;
Video* VIDEO;
Audio* AUDIO;
InputManager* INPUT_MANAGER;
TimeManager* TIME_MANAGER;
GameState* GAME_STATE;
SceneDirector* SCENE_DIRECTOR;

int main(int argc, char* args[])
{
	srand(time(NULL));

	// INIT
	RESOURCE_MANAGER = ResourceManager::getInstance();
	VIDEO = Video::getInstance();
	AUDIO = Audio::getInstance();
	INPUT_MANAGER = InputManager::getInstance();
	TIME_MANAGER = TimeManager::getInstance();
	GAME_STATE = GameState::getInstance();
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

	delete RESOURCE_MANAGER;
	delete VIDEO;
	delete AUDIO;
	delete INPUT_MANAGER;
	delete TIME_MANAGER;
	delete SCENE_DIRECTOR;

	return 0;
}
