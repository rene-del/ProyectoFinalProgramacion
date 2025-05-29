#ifndef MAP_H
#define MAP_H

#define NUM_CAPAS 3

using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Scene.h"
#include "Enemy.h"

#include "Bullet.h"
#include "BlobBullet.h"

#include "Blob.h"
#include "Grunt.h"
#include "Mine.h"

#include "HighScore.h"

#include "tinyxml2.h"

class Map : public Scene
{
private:
	Player* _player;
	std::vector<Enemy*> _enemies;
	HighScore _scoreTrack;
	int _width;
	int _height;

	int _tileWidth;
	int _tileHeight;

	int _mapWidth;
	int _mapHeight;

	int _mapId;
	int _firstGId;

	int _playTime;
	int _maxCooldown;
	int _enemyCooldown;

	vector<int> Layers[NUM_CAPAS];

public:
	Map();
	~Map() override;

	void init() override;
	void reinit() override;
	void update() override;
	void render() override;

	int loadMap(const char* filename);
	int getMapId() { return _mapId; };

	int getTileWidth() { return _tileWidth; };
	int getTileHeight() { return _tileHeight; };
	int getMapWidth() { return _mapWidth; };
	int getMapHeight() { return _mapHeight; };
};

#endif

