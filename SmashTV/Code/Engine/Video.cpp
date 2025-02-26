#include "Video.h"
#include "ResourceManager.h"

Video* Video::_pInstance = nullptr;

extern ResourceManager* RESOURCE_MANAGER;

Video::Video()
{
	_gWindow = nullptr;
	_gRenderer = nullptr;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Couldn't init video: " << SDL_GetError() << std::endl;
	}

	_gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	_gRenderer = SDL_CreateRenderer(_gWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(_gRenderer, 0x00, 0x00, 0x00, 0x00);
}

Video::~Video()
{
}

void Video::renderGraphic(int img, int posXStart, int posYStart, int posX, int posY, int width, int height)
{
	SDL_Rect src, dst;

	src.w = width;
	src.h = height;
	src.x = posXStart;
	src.y = posYStart;

	dst.w = width;
	dst.h = height;
	dst.x = posX;
	dst.y = posY;

	SDL_Texture* tex = RESOURCE_MANAGER->getGraphicByID(img);

	if (SDL_RenderCopy(_gRenderer, tex, &src, &dst) < 0)
	{
		std::cout << "Couldn't render the texture: " << SDL_GetError();
	}
}

void Video::clearScreen()
{
	SDL_RenderClear(_gRenderer);
}

void Video::updateScreen()
{
	SDL_RenderPresent(_gRenderer);
}

void Video::close()
{
	SDL_Quit();
}

Video* Video::getInstance()
{
	if (_pInstance == nullptr)
		_pInstance = new Video();

	return _pInstance;
}
