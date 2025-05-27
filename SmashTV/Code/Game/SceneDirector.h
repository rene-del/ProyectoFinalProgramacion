#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <vector>
#include "Scene.h"

//! Enum Scenes.
/*! All the Scenes in the game. */
enum SceneEnum {
		MENU, MAP, GAMEOVER, HIGHSCORE, /*SAVE_LOAD,*/
		_LASTSCENE};

#define NUM_SCENES _LASTSCENE

class SceneDirector
{
public:
	~SceneDirector();

	void init();
		
	void changeScene(SceneEnum next_scene, bool reinit = true);

	void pauseCurrentSceneAudio();

	SceneEnum getCurrSceneEnum() { return mCurrScene; };

	Scene* getCurrentScene() { return mVectorScenes[mCurrScene]; };
		
	//! Gets pointer to instance
	static SceneDirector* getInstance();

protected:
	SceneDirector();
	static SceneDirector* pInstance; /*!<  pointer instance*/

	std::vector<Scene*>	mVectorScenes;
	SceneEnum mCurrScene;
};

#endif
