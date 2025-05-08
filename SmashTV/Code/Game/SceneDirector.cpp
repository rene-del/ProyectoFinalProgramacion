#include "SceneDirector.h"

#include "Menu.h"
#include "Map.h"
#include "GameOver.h"

SceneDirector* SceneDirector::pInstance = NULL;

SceneDirector* SceneDirector::getInstance()
{
	if (!pInstance)
	{
		pInstance = new SceneDirector();
	}

	return pInstance;
}

SceneDirector::SceneDirector()
{
	init();
}

SceneDirector::~SceneDirector()
{
	delete mVectorScenes[MENU];
	delete mVectorScenes[MAP];
	delete mVectorScenes[GAMEOVER];
}

void SceneDirector::init()
{
	mVectorScenes.resize(NUM_SCENES);

	Menu* menu = new Menu();
	Map* map = new Map();
	GameOver* gameOver = new GameOver();

	mVectorScenes[MENU] = menu;
	mVectorScenes[MAP] = map;
	mVectorScenes[GAMEOVER] = gameOver;

	menu->init();
	gameOver->init();

	mCurrScene = MENU;
}

void SceneDirector::changeScene(SceneEnum next_scene, bool reinit)
{
	mVectorScenes[next_scene]->setReInit(reinit);
	mCurrScene = next_scene;
}
