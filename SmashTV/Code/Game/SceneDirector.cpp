#include "SceneDirector.h"

#include "Map.h"
#include "Menu.h"

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
}

void SceneDirector::init()
{
	mVectorScenes.resize(NUM_SCENES);

	Menu* menu = new Menu();
	Map* map = new Map();

	mVectorScenes[MENU] = menu;
	mVectorScenes[MAP] = map;

	menu->init();
	map->init();

	mCurrScene = MAP;
}

void SceneDirector::changeScene(SceneEnum next_scene, bool reinit)
{
	mVectorScenes[next_scene]->setReInit(reinit);
	mCurrScene = next_scene;
}
