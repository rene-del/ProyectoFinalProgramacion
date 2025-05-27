#include "Map.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/Audio.h"
#include "SceneDirector.h"
#include "GameState.h"

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern Audio* AUDIO;
extern SceneDirector* SCENE_DIRECTOR;
extern GameState* GAME_STATE;

Map::Map()
{
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

    _music = 0;
    _channel = 0;

    for (size_t i = 0; i < NUM_CAPAS; i++)
    {
        Layers[i].resize(0);
    }

    _reInit = true;

    _player = nullptr;
}

Map::~Map()
{
    for (int i = 0; i < _enemies.size(); i++)
    {
        delete _enemies[i];
        _enemies.erase(_enemies.begin() + i);
        i--;
    }

    delete _player;
}

void Map::init()
{
    // LOAD MAP
    loadMap("Assets/Map/Map.tmx");

    _music = RESOURCE_MANAGER->loadAndGetAudioID("Assets/Audios/song.wav");

    _channel = AUDIO->playAudio(-1, _music, -1);

    _enemyCooldown = 500;

    // PLAYER
    _player = new Player();
    _player->init();

    _reInit = false;
}

void Map::reinit()
{
    for (int i = 0; i < _enemies.size(); i++)
    {
        delete _enemies[i];
        _enemies.erase(_enemies.begin() + i);
        i--;
    }

    delete _player;

    init();
}

void Map::update()
{
    // PLAYER
    _player->update();

    for (int i = 0; i < _enemies.size(); i++)
    {
        if ((_player->getLifes() > -1) || (_enemies[i]->getIsDead()))
        {
            _enemies[i]->update(_player);
        }
    }

    if (_player->getLifes() > -1)
    {
        std::vector<Bullet*> playerBullets;
        playerBullets = _player->getBullets();

        for (auto& enemy : _enemies)
        {
            // CHECK IF ENEMY NEEDS TO BE DELETED
            for (int i = 0; i < _enemies.size(); i++)
            {
                if (_enemies[i]->getAnimFinished())
                {
                    delete _enemies[i];
                    _enemies.erase(_enemies.begin() + i);
                    i--;
                }
            }
        }

        // ENEMIES
        if (_enemies.size() < 10)
        {
            if (_enemyCooldown > 150)
            {
                _enemyCooldown = 0;

                int randNum = rand() % 4;

                float x = 0.0f;
                float y = 0.0f;

                switch (randNum)
                {
                    // TOP
                case 0:
                    x = static_cast<float>(SCREEN_WIDTH / 2.0f);
                    y = 40.0f;

                    break;

                    // BOTTOM
                case 1:
                    x = static_cast<float>(SCREEN_WIDTH / 2.0f);
                    y = static_cast<float>(SCREEN_HEIGHT - 40.0f);

                    break;

                    // LEFT
                case 2:
                    x = 40.0f;
                    y = static_cast<float>(SCREEN_HEIGHT / 2.0f);

                    break;

                    // RIGHT
                case 3:
                    x = static_cast<float>(SCREEN_WIDTH - 40.0f);
                    y = static_cast<float>(SCREEN_HEIGHT / 2.0f);

                    break;
                default:
                    break;
                }

                randNum = rand() % 3;

                if (randNum == 0)
                {
                    Blob* blob = new Blob(x, y);
                    blob->init();
                    _enemies.push_back(blob);
                }
                else if (randNum == 1)
                {
                    Grunt* grunt = new Grunt(x, y);
                    grunt->init();
                    _enemies.push_back(grunt);
                }
                else
                {
                    Mine* mine = new Mine(x, y);
                    mine->init();
                    _enemies.push_back(mine);
                }
            }
        }

        // ENEMIES COLLISION WITH PLAYER

        bool collide = false;

        for (auto& enemy : _enemies)
        {
            collide = enemy->checkCollision(_player->getPlayerRect());

            if (collide)
            {
                if (!enemy->getIsDead())
                {
                    AUDIO->playAudio(-1, enemy->getAudioDead(), 0);
                    enemy->setIsDead(true);
                    _player->setLifes(_player->getLifes() - 1);
                    AUDIO->playAudio(-1, _player->getAudioHurt(), 0);
                    break;
                }
            }
        }

        // ENEMIES COLLISION WITH PLAYER BULLETS

        for (int i = 0; i < playerBullets.size(); i++)
        {
            for (auto& enemy : _enemies)
            {
                collide = enemy->checkCollision(playerBullets[i]->getRect());

                if (collide)
                {
                    if (!enemy->getIsDead())
                    {
                        enemy->setIsDead(true);
                        AUDIO->playAudio(-1, enemy->getAudioDead(), 0);
                        delete playerBullets[i];
                        playerBullets.erase(playerBullets.begin() + i);
                        _player->setBulletsVector(playerBullets);

                        //SCORE
                        GAME_STATE->setPoints(GAME_STATE->getPoints() + 10);

                        break;
                    }
                }
            }
        }

        _enemyCooldown++;
    }

    if (_player->getEndAnim())
    {
        SCENE_DIRECTOR->changeScene(SceneEnum::GAMEOVER, true);
    }
}

void Map::render()
{
    for (size_t n = 0; n < NUM_CAPAS; n++)
    {
        for (int i = 0; i < _height; i++)
        {
            for (int j = 0; j < _width; j++)
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

    _player->render();

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
