#include "Map.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"

#include "Player.h"

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;

extern Player PLAYER;

Map::Map()
{
    _blob = nullptr;
    _grunt = nullptr;
    _mine = nullptr;

    _enemies.resize(0);

    _width = 0;
    _height = 0;

    _tileWidth = 0;
    _tileHeight = 0;

    _mapWidth = 0;
    _mapHeight = 0;

    _mapId = 0;
    _firstGId = 0;

    _enemyCooldown = 0;

    for (size_t i = 0; i < NUM_CAPAS; i++)
    {
        Layers[i].resize(0);
    }

    _reInit = true;
}

Map::~Map()
{
    delete _blob;
    delete _grunt;
    delete _mine;

    for (int i = 0; i < _enemies.size(); i++)
    {
        delete _enemies[i];
        _enemies.erase(_enemies.begin() + i);
        i--;
    }
}

void Map::init()
{
    // LOAD MAP
    loadMap("Assets/Map/Map.tmx");

    _enemyCooldown = 500;

    // PLAYER
    PLAYER.init();

    // ---

    _blob = new Blob(0, 0);
    _blob->init();

    _grunt = new Grunt(0, 0);
    _grunt->init();

    _mine = new Mine(0, 0);
    _mine->init();

    // ---

    _reInit = false;
}

void Map::reinit()
{
    delete _blob;
    delete _grunt;
    delete _mine;

    for (int i = 0; i < _enemies.size(); i++)
    {
        delete _enemies[i];
        _enemies.erase(_enemies.begin() + i);
        i--;
    }

    init();
}

void Map::update()
{    
    PLAYER.update();

    std::vector<Bullet*> playerBullets;
    playerBullets = PLAYER.getBullets();

    _blob->update();

    _mine->update();
    
    _grunt->update();

    // ENEMIES
    if (_enemies.size() < 10)
    {
        if (_enemyCooldown > 500)
        {
            _enemyCooldown = 0;

            int randNum = rand() % 4;
            int dir = randNum;

            int x = 0;
            int y = 0;

            switch (randNum)
            {
            // TOP
            case 0:
                x = SCREEN_WIDTH / 2;
                y = 40;

                break;

            // BOTTOM
            case 1:
                x = SCREEN_WIDTH / 2;
                y = SCREEN_HEIGHT - 40;

                break;

            // LEFT
            case 2:
                x = 40;
                y = SCREEN_HEIGHT / 2;

                break;

            // RIGHT
            case 3:
                x = SCREEN_WIDTH - 40;
                y = SCREEN_HEIGHT / 2;

                break;
            default:
                break;
            }

            randNum = rand() % 3;

            if (randNum == 0)
            {
                Blob* blob = new Blob(x, y, dir);
                blob->init();
                _enemies.push_back(blob);
            }
            else if (randNum == 1)
            {
                Grunt* grunt = new Grunt(x, y, dir);
                grunt->init();
                _enemies.push_back(grunt);
            }
            else
            {
                Mine* mine = new Mine(x, y, dir);
                mine->init();
                _enemies.push_back(mine);
            }
        }
    }

    for (int i = 0; i < _enemies.size(); i++)
    {
        _enemies[i]->update();
    }

    // PLAYER COLLISION WITH BLOB BULLETS
    bool collide = false;
    std::vector<BlobBullet*> blobBullets;
    blobBullets = _blob->getBullets();

    for (int i = 0; i < blobBullets.size(); i++)
    {
        collide = PLAYER.checkCollision(blobBullets[i]->getRect());

        if (collide)
        {
            delete blobBullets[i];
            blobBullets.erase(blobBullets.begin() + i);
            _blob->setBulletsVector(blobBullets);
            i--;
        }
    }

    // ENEMIES COLLISION WITH PLAYER

    // BLOB
    collide = _blob->checkCollision(PLAYER.getPlayerRect());

    if (collide)
    {
        if (!_blob->getIsDead())
        {
            _blob->setIsDead(true);
            PLAYER.setLifes(PLAYER.getLifes() - 1);
        }
    }

    // GRUNT
    collide = _grunt->checkCollision(PLAYER.getPlayerRect());

    if (collide)
    {
        if (!_grunt->getIsDead())
        {
            _grunt->setIsDead(true);
            PLAYER.setLifes(PLAYER.getLifes() - 1);
        }
    }

    // MINE
    collide = _mine->checkCollision(PLAYER.getPlayerRect());

    if (collide)
    {
        if (!_mine->getIsTouched())
        {
            _mine->setIsTouched(true);
            PLAYER.setLifes(PLAYER.getLifes() - 1);
        }
    }    

    // ENEMIES COLLISION WITH PLAYER BULLETS

    // BLOB
    for (int i = 0; i < playerBullets.size(); i++)
    {
        collide = _blob->checkCollision(playerBullets[i]->getRect());

        if (collide)
        {
            delete playerBullets[i];
            playerBullets.erase(playerBullets.begin() + i);
            PLAYER.setBulletsVector(playerBullets);
            i--;
        }        
    }

    // GRUNT
    for (int i = 0; i < playerBullets.size(); i++)
    {
        collide = _grunt->checkCollision(playerBullets[i]->getRect());

        if (collide)
        {
            delete playerBullets[i];
            playerBullets.erase(playerBullets.begin() + i);
            PLAYER.setBulletsVector(playerBullets);
            i--;
        }
    }

    // MINE
    for (int i = 0; i < playerBullets.size(); i++)
    {
        if (!_mine->getIsTouched())
        {
            collide = _mine->checkCollision(playerBullets[i]->getRect());

            if (collide)
            {
                delete playerBullets[i];
                playerBullets.erase(playerBullets.begin() + i);
                PLAYER.setBulletsVector(playerBullets);
                i--;
            }
        }
    }

    _enemyCooldown++;
}

void Map::render()
{
    for (size_t n = 0; n < NUM_CAPAS; n++)
    {
        for (size_t i = 0; i < _height; i++)
        {
            for (size_t j = 0; j < _width; j++)
            {
                SDL_Rect source;
                SDL_Rect dest;

                dest.x = j * _tileWidth;
                dest.y = i * _tileHeight;
                dest.w = _tileWidth;
                dest.h = _tileHeight;

                int id = Layers[n][i * _width + j] - 1;

                if (id >= 0)
                {
                    int cellX = id % 11;
                    int cellY = id / 11;

                    source.x = cellX * _tileWidth;
                    source.y = cellY * _tileHeight;
                    source.w = _tileWidth;
                    source.h = _tileHeight;

                    VIDEO->renderGraphic(_mapId, source, dest);
                }
            }
        }
    }

    PLAYER.render();

    _blob->render();
    _grunt->render();
    _mine->render();

    for (int i = 0; i < _enemies.size(); i++)
    {
        _enemies[i]->render();
    }
}

int Map::loadMap(const char* filename)
{
    using namespace tinyxml2;

    XMLDocument doc;

    if (doc.LoadFile(filename) != XML_SUCCESS)
    {
        cout << "Error XML: " << doc.ErrorStr();
        return 1;
    }

    XMLElement* map = doc.FirstChildElement();

    _width = stoi(map->Attribute("width"));
    _height = stoi(map->Attribute("height"));
    _tileWidth = stoi(map->Attribute("tilewidth"));
    _tileHeight = stoi(map->Attribute("tileheight"));

    _mapWidth = _width * _tileWidth;
    _mapHeight = _height * _tileHeight;

    XMLElement* tileset = map->FirstChildElement("tileset");

    _mapId = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Map/MapTileset.png");
    _firstGId = stoi(tileset->Attribute("firstgid"));

    XMLElement* layer = map->FirstChildElement("layer");

    for (size_t i = 0; i < NUM_CAPAS; i++)
    {
        string layerTXT;
        layerTXT = layer->FirstChildElement("data")->GetText();

        size_t pos = 0;
        size_t nextPos = 0;

        while (nextPos != string::npos)
        {
            nextPos = layerTXT.find(',', pos);

            if (nextPos != string::npos)
            {
                int value = stoi(layerTXT.substr(pos, nextPos - pos));
                Layers[i].push_back(value);
                pos = nextPos + 1;
            }
            else
            {
                int value = stoi(layerTXT.substr(pos, layerTXT.size() - pos));
                Layers[i].push_back(value);
            }
        }

        layer = layer->NextSiblingElement("layer");
    }
}
