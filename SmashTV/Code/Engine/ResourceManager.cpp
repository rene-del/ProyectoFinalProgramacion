#include "ResourceManager.h"
#include "Video.h"

ResourceManager* ResourceManager::_pInstance = nullptr;

extern Video* VIDEO;

ResourceManager::~ResourceManager()
{
}

void ResourceManager::removeGraphic(const char* file)
{
	std::map<std::string, Sint32>::iterator it = _idGraphicsMap.find(file);

	if (it != _idGraphicsMap.end())
	{
		SDL_DestroyTexture(_graphicsVector[it->second]);
		_graphicsVector[it->second] = nullptr;
		_idGraphicsMap.erase(it);
	}
}

void ResourceManager::removeAudio(const char* file)
{
	std::map<std::string, Sint32>::iterator it = _idAudiosMap.find(file);

	if (it != _idAudiosMap.end())
	{
		Mix_FreeChunk(_audiosVector[it->second]);
		_audiosVector[it->second] = nullptr;
		_idAudiosMap.erase(it);
	}
}

Sint32 ResourceManager::loadAndGetGraphicID(const char* file)
{
	std::map<std::string, Sint32>::iterator it = _idGraphicsMap.find(file);

	if (it == _idGraphicsMap.end())
	{
		int val = addGraphic(file);

		if (val != -1)
		{
			_idGraphicsMap.insert(std::pair<std::string, Sint32>(file, val));
		}

		return val;
	}
	else
	{
		return it->second;
	}
}

int ResourceManager::loadAndGetAudioID(const char* file)
{
	std::map<std::string, Sint32>::iterator it = _idAudiosMap.find(file);

	if (it == _idAudiosMap.end())
	{
		int val = addAudio(file);

		if (val != -1)
		{
			_idAudiosMap.insert(std::pair<std::string, Sint32>(file, val));
		}

		return val;
	}
}

std::string ResourceManager::getGraphicPathByID(Sint32 ID)
{
	for (auto it = _idGraphicsMap.begin(); it != _idGraphicsMap.end(); ++it)
	{
		if (it->second == ID)
		{
			return it->first;
		}
	}

	return "NULL";
}

void ResourceManager::getGraphicSize(Sint32 img, int& width, int& height)
{
	if ((img > -1) && (img < _graphicsVector.size()))
	{
		SDL_QueryTexture(_graphicsVector[img], NULL, NULL, &width, &height);
	}
}

Uint16 ResourceManager::getGraphicWidth(Sint32 img)
{
	if ((img > -1) && (img < _graphicsVector.size()))
	{
		int w;
		SDL_QueryTexture(_graphicsVector[img], NULL, NULL, &w, NULL);
		return w;
	}

	return -1;
}

Uint16 ResourceManager::getGraphicHeight(Sint32 img)
{
	if ((img > -1) && (img < _graphicsVector.size()))
	{
		int h;
		SDL_QueryTexture(_graphicsVector[img], NULL, NULL, NULL, &h);
		return h;
	}

	return -1;
}

SDL_Texture* ResourceManager::getGraphicByID(Sint32 ID)
{
	if ((ID > -1) && (ID < _graphicsVector.size()))
	{
		return _graphicsVector[ID];
	}

	return NULL;
}

Mix_Chunk* ResourceManager::getAudioByID(Sint32 ID)
{
	if ((ID > -1) && (ID < _audiosVector.size()))
	{
		return _audiosVector[ID];
	}

	return NULL;
}

int ResourceManager::getAudiosvectorSize()
{
	return _audiosVector.size();
}

void ResourceManager::setAlphaGraphic(Sint32 ID, Uint8 alpha_value)
{
	SDL_SetTextureAlphaMod(_graphicsVector[ID], alpha_value);
}

void ResourceManager::printLoadedGraphics()
{
	for (auto it = _idGraphicsMap.begin(); it != _idGraphicsMap.end(); ++it)
	{
		std::cout << it->first << std::endl;
	}
}

Sint32 ResourceManager::createGraphic(const char* name, Uint16 width, Uint16 height)
{
	return Sint32();
}

ResourceManager* ResourceManager::getInstance()
{
	if (_pInstance == nullptr)
		_pInstance = new ResourceManager();

	return _pInstance;
}

ResourceManager::ResourceManager()
{
}

Sint32 ResourceManager::addGraphic(const char* file)
{
	SDL_Surface* image = IMG_Load(file);

	if (image == NULL)
	{
		std::cout << "Couldn't load image: " << SDL_GetError();
		return -1;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(VIDEO->_gRenderer, image);

	SDL_FreeSurface(image);

	if (tex == NULL)
	{
		std::cout << "Couldn't load texture: " << SDL_GetError();
		return -1;
	}
	else
	{
		Sint32 max = updateFirstFreeSlotGraphic();

		if (max != _graphicsVector.size())
		{
			_graphicsVector[max] = tex;
			return max;
		}
		else
		{
			_graphicsVector.push_back(tex);
			return _graphicsVector.size() - 1;
		}

		_graphicsVector.push_back(tex);
		return _graphicsVector.size() - 1;
	}
}

int ResourceManager::addAudio(const char* file)
{
	Mix_Chunk* sound = Mix_LoadWAV(file);

	if (sound == NULL)
	{
		std::cout << "Couldn't load audio: " << Mix_GetError();
		return -1;
	}
	else
	{
		Sint32 max = updateFirstFreeSlotAudio();

		if (max != _audiosVector.size())
		{
			_audiosVector[max] = sound;
			return max;
		}
		else
		{
			_audiosVector.push_back(sound);
			return _audiosVector.size() - 1;
		}

		_audiosVector.push_back(sound);
		return _audiosVector.size() - 1;
	}
}

Uint32 ResourceManager::updateFirstFreeSlotGraphic()
{
	int max = 0;

	if (_graphicsVector.size() >= 1)
	{
		do
		{
			if (_graphicsVector[max] == nullptr)
			{
				break;
			}
			else
			{
				max++;
			}
		} while (max != _graphicsVector.size());
	}

	_firstFreeGraphicsSlot = max;

	return _firstFreeGraphicsSlot;
}

Uint32 ResourceManager::updateFirstFreeSlotAudio()
{
	int max = 0;

	if (_audiosVector.size() >= 1)
	{
		do
		{
			if (_audiosVector[max] == nullptr)
			{
				break;
			}
			else
			{
				max++;
			}
		} while (max != _audiosVector.size());
	}

	_firstFreeAudiossSlot = max;

	return _firstFreeAudiossSlot;
}
