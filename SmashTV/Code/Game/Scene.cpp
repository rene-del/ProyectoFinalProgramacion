#include "Scene.h"

Scene::Scene()
{
	_reInit = true;
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
