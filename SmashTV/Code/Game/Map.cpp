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

    _width = 0;
    _height = 0;

    _tileWidth = 0;
    _tileHeight = 0;

    _mapWidth = 0;
    _mapHeight = 0;

    _mapId = 0;
    _firstGId = 0;

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
}

void Map::init()
{
    loadMap("Assets/Map/Map.tmx");

    PLAYER.init();

    _blob = new Blob();
    _blob->init();

    _grunt = new Grunt();
    _grunt->init();

    _mine = new Mine();
    _mine->init();

    _reInit = false;
}

void Map::reinit()
{
    delete _blob;
    delete _grunt;
    delete _mine;

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
