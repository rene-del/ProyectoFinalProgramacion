#ifndef SCENE_H
#define SCENE_H

//! Scene class
/*!
	Handles the Scenes for all the game.
*/
class Scene
{
public:
	//! Constructor of an empty Scene.
	Scene();

	//! Destructor
	virtual ~Scene();

	//! Initializes the Scene.
	virtual void init();

	//! Function to withdraw anything owned by the class and to call init
	virtual void reinit();

	//! Handles the drawing of the scene
	virtual void render() {};

	//! Handles the updating of the scene
	virtual void update() {};

	void setReInit(bool loaded = true) { _reInit = loaded; };
	bool mustReInit() { return _reInit; };

protected:
	bool _reInit; /*!<  Reload when returning to scene*/
};

#endif
