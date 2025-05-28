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

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		std::cout << "Couldn't init image: " << IMG_GetError() << std::endl;
	}

	_gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	_gRenderer = SDL_CreateRenderer(_gWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(_gRenderer, 0x00, 0x00, 0x00, 0x00);

	//FONT

	if (TTF_Init() == -1)
	{
		std::cout << "Couldn't init SDL_ttf: " << TTF_GetError() << std::endl;
	}

	_font = TTF_OpenFont("Assets/Fonts/Minecraft.ttf", 24);
	if (!_font)
	{
		std::cout << "Couldn't load font: " << TTF_GetError() << std::endl;
	}


}

Video::~Video()
{
	SDL_DestroyWindow(_gWindow);
	_gWindow = nullptr;

	if (_font)
	{
		TTF_CloseFont(_font);
		_font = nullptr;
	}
	TTF_Quit();

	SDL_DestroyWindow(_gWindow);


	SDL_Quit();



}

void Video::renderGraphic(int img, SDL_Rect src, SDL_Rect dst)
{
	SDL_Texture* tex = RESOURCE_MANAGER->getGraphicByID(img);

	if (SDL_RenderCopy(_gRenderer, tex, &src, &dst) < 0)
	{
		std::cout << "Couldn't render the texture: " << SDL_GetError();
	}
}

void Video::renderGraphicSmooth(int img, SDL_Rect src, SDL_FRect dst)
{
	SDL_Texture* tex = RESOURCE_MANAGER->getGraphicByID(img);

	if (SDL_RenderCopyF(_gRenderer, tex, &src, &dst) < 0)
	{
		std::cout << "Couldn't render the texture: " << SDL_GetError();
	}
}

void Video::renderGraphicRotated(int img, SDL_Rect src, SDL_Rect dst, double rotation)
{
	SDL_Texture* tex = RESOURCE_MANAGER->getGraphicByID(img);

	if (SDL_RenderCopyEx(_gRenderer, tex, &src, &dst, rotation, nullptr, SDL_FLIP_NONE) < 0)
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

void Video::renderText(const std::string& text, int x, int y, SDL_Color color, int fontSize)
{
	if (text.empty()) return;

	TTF_Font* fontToUse = _font;

	if (fontSize != 24)
	{
		fontToUse = TTF_OpenFont("Assets/Fonts/Minecraft.ttf", fontSize);
		if (!fontToUse) {
			std::cout << "Error cargando fuente con tamaño " << fontSize << ": " << TTF_GetError() << std::endl;
			return;
		}
	}

	SDL_Surface* surface = TTF_RenderText_Solid(fontToUse, text.c_str(), color);
	if (!surface) {
		std::cout << "Error renderizando texto: " << TTF_GetError() << std::endl;
		if (fontToUse != _font) TTF_CloseFont(fontToUse);
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(_gRenderer, surface);
	SDL_Rect dstRect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(_gRenderer, texture, NULL, &dstRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

	if (fontToUse != _font) {
		TTF_CloseFont(fontToUse);
	}
}


