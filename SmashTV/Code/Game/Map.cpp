#include "Map.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;

Map::Map()
{
    _width = 0;
    _height = 0;

    _tileWidth = 0;
    _tileHeight = 0;
    _tileSpace = 0;

    _mapWidth = 0;
    _mapHeight = 0;

    _mapId = 0;
    _firstGId = 0;

    for (size_t i = 0; i < NUM_CAPAS; i++)
    {
        Layers[i].resize(0);
    }
}

Map::~Map()
{
}

void Map::init()
{
    loadMap("Assets/Map.tmx");
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
                    int cellX = id % 15;
                    int cellY = id / 15;

                    source.x = cellX * _tileWidth + _tileSpace * cellX;
                    source.y = cellY * _tileHeight + _tileSpace * cellY;
                    source.w = _tileWidth;
                    source.h = _tileHeight;

                    VIDEO->renderGraphic(_mapId, source, dest);
                }
            }
        }
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
    _tileSpace = 1;

    _mapWidth = _width * _tileWidth;
    _mapHeight = _height * _tileHeight;

    XMLElement* tileset = map->FirstChildElement("tileset");

    _mapId = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/mapTileset.png");
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
