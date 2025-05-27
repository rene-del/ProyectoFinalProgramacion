#include "Scene.h"

Scene::Scene()
{
	_reInit = true;
	_music = 0;
	_channel = 0;
}

Scene::~Scene()
{
}

void Scene::init()
{
	_reInit = false;
}

void Scene::reinit()
{
	_reInit = true;
}
