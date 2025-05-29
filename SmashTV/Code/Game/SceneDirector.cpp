#include "SceneDirector.h"

#include "../Engine/Audio.h"

#include "Menu.h"
#include "Map.h"
#include "GameOver.h"
#include "HighScore.h"

SceneDirector* SceneDirector::pInstance = NULL;

extern Audio* AUDIO;

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
	delete mVectorScenes[HIGHSCORE];
}

void SceneDirector::init()
{
	_channel = 0;

	mVectorScenes.resize(NUM_SCENES);

	Menu* menu = new Menu();
	Map* map = new Map();
	GameOver* gameOver = new GameOver();
	HighScore* highscore = new HighScore();

	mVectorScenes[MENU] = menu;
	mVectorScenes[MAP] = map;
	mVectorScenes[GAMEOVER] = gameOver;
	mVectorScenes[HIGHSCORE] = highscore;

	mCurrScene = MENU;
	mVectorScenes[mCurrScene]->init();
}

void SceneDirector::changeScene(SceneEnum next_scene, bool reinit)
{
	pauseCurrentSceneAudio();

	mVectorScenes[next_scene]->setReInit(reinit);
	mCurrScene = next_scene;
}

void SceneDirector::changeSceneC(SceneEnum next_scene, bool reinit, int channel)
{
	mVectorScenes[next_scene]->setReInit(reinit);
	mCurrScene = next_scene;

	_channel = channel;
}

void SceneDirector::pauseCurrentSceneAudio()
{
	Scene* currentScene = mVectorScenes[mCurrScene];

	if (mCurrScene == HIGHSCORE)
	{
		AUDIO->stopAudio(_channel);
	}
	else
	{
		AUDIO->stopAudio(currentScene->getMusicID());
	}
}
